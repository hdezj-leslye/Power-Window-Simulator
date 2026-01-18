# Automotive Power Window Control System (FSM)

## 📋 Project Overview
This repository contains a professional-grade functional simulator of an **Automotive Power Window Control System** developed in **C**. The system is architected using a **Finite State Machine (FSM)**, ensuring robust state transitions and high reliability for safety-critical operations.

A key highlight is the **Anti-Pinch Safety Protocol**, an industry standard (FMVSS 118 compliant) designed to detect physical resistance and trigger an immediate safety reversal to prevent injury.

---

## 🚀 Key Features

* **Finite State Machine (FSM) Architecture:** Precise management of mutually exclusive states: `IDLE`, `RAISING`, `LOWERING`, and `SAFETY_REVERSE`.
* **Anti-Pinch Protocol (Safety-Critical):** Automatic obstacle detection during the closing phase, triggering a mandatory safety reverse.
* **Child Lock Security:** Logic-level lockout that disables movement commands, simulating real-world passenger safety overrides.
* **Diagnostic Event Logging:** Real-time generation of `system_logs.txt` with timestamps for post-operation analysis and debugging.
* **Boundary Validation:** Prevents logical over-travel by validating physical window limits (0% to 100% calibration).
* **Optimized UX:** Cross-platform terminal handling with auditory feedback for critical system alerts.

---
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

The simulator environment listens for specific hardware-simulated interrupts to control the system:
    [ 1 ] UP: Initiates the window closing sequence.
    [ 2 ] DOWN: Initiates the window opening sequence.
    [ 3 ] OBSTACLE: Triggers the Anti-Pinch safety reverse mechanism.
    [ 4 ] CHILD LOCK: Toggles the security lockout mode (disables inputs).
    [ 0 ] SHUTDOWN: Safely terminates the system and flushes log files.
