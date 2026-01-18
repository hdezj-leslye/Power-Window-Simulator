# Simulador de Sistema de Elevalunas Eléctrico Automotriz (FSM)

## 📋 Descripción General del Proyecto
Este repositorio contiene un simulador funcional de nivel profesional de un **Sistema de Control de Ventanas Eléctricas** automotrices desarrollado en **C**. El sistema está diseñado bajo una arquitectura de **Máquina de Estados Finitos (FSM)**, lo que garantiza transiciones de estado robustas y una alta confiabilidad en operaciones críticas para la seguridad.

Esta implementación incluye un **Sistema Anti-Pinzamiento (Anti-Pinch)**, cumpliendo con los estándares de seguridad industrial (como la normativa FMVSS 118), diseñado para detectar resistencia y activar una reversión de seguridad inmediata para prevenir lesiones.

---

## 🚀 Características Principales

* **Arquitectura de Máquina de Estados Finitos (FSM):** Gestión precisa de estados mutuamente excluyentes: `IDLE`, `RAISING`, `LOWERING`, y `SAFETY_REVERSE`.
* **Protocolo Anti-Pinch (Safety-Critical):** Detección automática de obstáculos durante la fase de cierre, activando una reversa de seguridad inmediata.
* **Anulación de Seguridad (Child Lock):** Bloqueo de nivel lógico que deshabilita los comandos de movimiento, simulando los controles de seguridad para pasajeros.
* **Registro de Eventos de Diagnóstico (Logging):** Generación de un archivo `system_logs.txt` en tiempo real con marcas de tiempo, facilitando el análisis post-operación y depuración.
* **Validación de Límites:** Evita el sobre-desplazamiento lógico mediante la validación de límites físicos (calibración del 0% al 100%).
* **UX Optimizada:** Manejo de terminal multiplataforma y retroalimentación auditiva para alertas críticas.

---

## 🔄 Diagrama de la Máquina de Estados (FSM)

El siguiente diagrama representa la lógica de control del sistema, asegurando que cada transición sea validada antes de ejecutarse:

```mermaid
stateDiagram-v2
    [*] --> IDLE
    IDLE --> RAISING: Tecla 1 (UP)
    IDLE --> LOWERING: Tecla 2 (DOWN)
    
    RAISING --> IDLE: Límite 100% alcanzado
    RAISING --> SAFETY_REVERSE: Tecla 3 (OBSTACLE)
    RAISING --> IDLE: Tecla 0 (SHUTDOWN)
    
    LOWERING --> IDLE: Límite 0% alcanzado
    LOWERING --> IDLE: Tecla 0 (SHUTDOWN)
    
    SAFETY_REVERSE --> LOWERING: Secuencia Automática de Reversa
    
    note right of RAISING: Anti-Pinch Activo

## 📂 Installation & Execution

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/hdezj-leslye/power-window-simulator.git](https://github.com/hdezj-leslye/power-window-simulator.git)
   
2. **Compile the source code:**
   ```bash
   gcc main.c -o window_sim.exe

3. **Run the simulator:**
   ```bash
   ./window_sim.exe

## 🎮 Controller Interface

The simulator accepts the following hardware-simulated interrupts to control the window system and safety features:

| Key | Action | Description |
| :---: | :--- | :--- |
| **1** | **UP** | Initiates window closing sequence. |
| **2** | **DOWN** | Initiates window opening sequence. |
| **3** | **OBSTACLE** | Triggers Anti-Pinch safety reverse. |
| **4** | **CHILD LOCK** | Toggles security lockout mode. |
| **0** | **SHUTDOWN** | Safely terminates the system and closes logs. |

---
