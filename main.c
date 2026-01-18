/**
 * @file power_window_system.c
 * @brief Simulador de sistema de control de cristales automotriz con Anti-Pinch.
 * @author Leslye Hernandez Jimenez
 * @version 1.8
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h> 

/**
 * @enum SystemStatus
 * @brief Definición de la Máquina de Estados (FSM) para el control del motor.
 */
typedef enum {
    SYSTEM_IDLE,               ///< Estado de reposo: Motor apagado.
    WINDOW_RAISING,            ///< Ascenso: Motor en sentido horario.
    WINDOW_LOWERING,           ///< Descenso: Motor en sentido anti-horario.
    OBSTACLE_DETECTION_ACTIVE  ///< Seguridad: Reversa activa por obstrucción.
} SystemStatus;

/**
 * @struct DoorModule
 * @brief Abstracción del hardware de la puerta.
 */
typedef struct {
    SystemStatus status;  ///< Estado actual del sistema.
    int position;         ///< Posición del cristal (0: Cerrado, 100: Abierto).
    bool childLock;       ///< Inhibidor de seguridad para controles de pasajeros.
} DoorModule;

/**
 * @brief Sistema de Diagnóstico (Logging). Registra eventos con timestamp en archivo físico.
 */
void writeLog(const char* message) {
    FILE *file = fopen("system_logs.txt", "a");
    if (file == NULL) return;
    time_t now = time(NULL);
    char *date = ctime(&now);
    date[24] = '\0'; 
    fprintf(file, "[%s] LOG: %s\n", date, message);
    fclose(file);
}

/**
 * @brief Renderiza la interfaz de usuario en consola.
 * Maneja la portabilidad del comando de limpieza de pantalla.
 */
void renderInterface(DoorModule dm) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("==========================================\n");
    printf("     POWER WINDOW SYSTEM SIMULATOR V1.8   \n");
    printf("==========================================\n");
    
    printf(" MOTOR STATUS: %s\n", (dm.status == SYSTEM_IDLE) ? "IDLE" : 
                                 (dm.status == WINDOW_RAISING) ? "RAISING..." : 
                                 (dm.status == WINDOW_LOWERING) ? "LOWERING..." : "!!! SAFETY REVERSE !!!");
    
    printf(" CHILD LOCK:  %s\n", dm.childLock ? "ON (LOCKED)" : "OFF");
    
    // Lógica de visualización dinámica del estado físico del cristal
    printf(" WINDOW STATE: ");
    if (dm.position <= 0) printf("[0%%] CLOSED\n");
    else if (dm.position >= 100) printf("[100%%] OPEN\n");
    else printf("[%d%%] MOVING...\n", dm.position);
    
    printf("------------------------------------------\n");
}

int main() {
    DoorModule driverDoor = {SYSTEM_IDLE, 100, false};
    int command;

    writeLog("--- System V1.8 initialized ---");

    while(1) {
        renderInterface(driverDoor);
        printf(" COMMANDS: [1] UP | [2] DOWN | [3] OBSTACLE | [4] LOCK | [0] EXIT\n");
        printf(" Selection: ");
        
        if(scanf("%d", &command) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        if(command == 0) break;

        // --- MÓDULO DE SEGURIDAD: CHILD LOCK ---
        if(command == 4) {
            driverDoor.childLock = !driverDoor.childLock;
            writeLog(driverDoor.childLock ? "Child Lock Activated" : "Child Lock Deactivated");
            continue;
        }

        // Validación de permisos de movimiento
        if((command == 1 || command == 2) && driverDoor.childLock) {
            printf("\n ! ACCESS DENIED: Child Lock Active.\n");
            writeLog("WARNING: Unauthorized movement attempt");
            Sleep(1000);
            continue;
        }

        // --- MÓDULO DE CONTROL DE MOVIMIENTO (RAISING) ---
        if(command == 1) {
            if(driverDoor.position <= 0) continue;
            
            driverDoor.status = WINDOW_RAISING;
            GetAsyncKeyState('3'); // Reset de búfer del sensor de obstáculos

            for(int i = 0; i < 10; i++) {
                // SENSOR DE ANTI-PINCH: Detección en tiempo real durante el ciclo de subida
                if (GetAsyncKeyState('3') & 0x8000) { 
                    command = 3; 
                    break; 
                }

                if(driverDoor.position > 0) {
                    driverDoor.position -= 10;
                    renderInterface(driverDoor);
                    Sleep(300); 
                }
            }
        }

        // --- MÓDULO DE SEGURIDAD CRÍTICA: ANTI-PINCH ---
        if(command == 3) {
            driverDoor.status = OBSTACLE_DETECTION_ACTIVE;
            writeLog("CRITICAL: Obstacle detected!");
            renderInterface(driverDoor);
            
            Beep(750, 300); // Feedback auditivo de error de sistema
            Sleep(200);
            
            // Rutina de Reversa Automática (Safety Reverse)
            for(int i = 0; i < 3; i++) { 
                if(driverDoor.position < 100) {
                    driverDoor.position += 10;
                    renderInterface(driverDoor);
                    Sleep(200);
                }
            }
            writeLog("Action: Safety reverse completed");
        }

        // --- MÓDULO DE CONTROL DE MOVIMIENTO (LOWERING) ---
        else if(command == 2) {
            if(driverDoor.position >= 100) continue;

            driverDoor.status = WINDOW_LOWERING;
            for(int i = 0; i < 10; i++) {
                if(driverDoor.position < 100) {
                    driverDoor.position += 10;
                    renderInterface(driverDoor);
                    Sleep(300);
                }
            }
            writeLog("Action: Window fully lowered");
        }

        driverDoor.status = SYSTEM_IDLE; // Regreso automático a estado seguro
    }

    return 0;
}