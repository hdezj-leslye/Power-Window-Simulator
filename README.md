# Automotive Power Window System Simulator (FSM)

## 📋 Project Overview
This repository contains a professional-grade functional simulator of an **Automotive Power Window Control System** developed in **C**. The system is built upon a **Finite State Machine (FSM)** architecture, ensuring robust state transitions and high reliability in safety-critical operations.

This implementation features an **Anti-Pinch System**, a mandatory safety standard (FMVSS 118) designed to prevent injuries by detecting motor resistance and triggering an immediate safety reverse.



## 🚀 Key Features
* **Finite State Machine (FSM) Architecture:** Precise management of mutually exclusive states: `IDLE`, `RAISING`, `LOWERING`, and `SAFETY_REVERSE`.
* **Anti-Pinch Protocol (Safety-Critical):** Automatic obstacle detection during the closing phase, triggering a safety reverse to prevent entrapment.
* **Security Override (Child Lock):** Logic-level lockout that disables movement commands, simulating real-world passenger safety controls.
* **Diagnostic Event Logging:** Real-time generation of a `system_logs.txt` file. Includes timestamps for every system event, facilitating post-operation analysis.
* **Boundary Validation:** Prevents logical over-travel by validating physical window limits (0% to 100% calibration).
* **Optimized UX:** Cross-platform terminal handling and auditory feedback (`Beep`) for critical alerts.

## 🛠️ Technical Stack & Implementation
* **Language:** C (ISO C99/C11)
* **Concepts:**
    * **Hardware Abstraction:** Using `structs` to represent the door module.
    * **State Control:** `Enums` for definitive and safe state management.
    * **Memory Efficiency:** Low-overhead procedural logic suitable for embedded environments.
    * **I/O Stream:** File handling for persistent diagnostic logging.

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

