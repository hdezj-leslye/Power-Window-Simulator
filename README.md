# Power Window Simulator 🚙💻

## Executive Summary

The **Power Window Simulator** is a software engineering project designed to virtually model the behavior of an automotive Body Control Module (BCM) managing a smart window system. Before deploying code to physical microcontrollers and motors, simulation is a critical step in automotive engineering to validate logic, edge cases, and safety protocols.

This application provides a graphical **Human-Machine Interface (HMI)** to interact with the underlying state machine. It accurately simulates physical constraints—such as window position limits, motor actuation delays, and continuous/auto-roll modes—within a fully digital, event-driven environment.

### System Demonstration

[![Simulator Demonstration](./assets/demo.gif)](#)
*(Note: Replace with a GIF showing your simulator running)*

## Technical Specifications

* **Core Language:** [Insert Language, e.g., Java / C# / Python / JavaScript]
* **GUI Framework / HMI:** [Insert Framework, e.g., JavaFX / Windows Forms / Tkinter / React]
* **Architecture:** Event-driven logic utilizing a Finite State Machine (FSM) to simulate hardware states and physical time constraints.

---

## Simulation Architecture & Logic

Unlike a physical hardware project, this simulator relies entirely on mathematical and logical boundaries to represent physical components:

1. **Virtual Input Layer (HMI):** Graphical buttons and toggles capture user intent, distinguishing between short pulses (Auto-mode) and long holds (Manual-mode) via timestamp evaluation.
2. **State Machine Core:** A deterministic logic block that evaluates the current virtual window position (0% to 100% open) against the incoming HMI requests.
3. **Virtual Actuation & Timing:** Simulates the DC motor's physical travel time utilizing asynchronous delays or timer ticks, updating the GUI dynamically to reflect the window's physical location.

---

## Simulated State Matrix

The core simulation validates the following behavioral matrix to mimic real-world automotive standards:

| Virtual Event | FSM State | Simulated Output (GUI) |
| :--- | :--- | :--- |
| **Short Click (Up/Down)** | Auto-Roll | Window position updates continuously until limits (0% or 100%) are reached. |
| **Button Hold** | Manual Roll | Window position updates only while the simulated button state is active. |
| **Opposite Command** | Interrupt | Active timer/loop is canceled; window stops immediately. |
| **Limit Switch Reached** | Idle / Lock | Motor logic is disabled in the specific direction; prevents out-of-bounds errors. |

---

## How to Run the Simulator

1. Clone the repository to your local machine:
   ```bash
   git clone [https://github.com/HJLeslye/Power-Window-Simulator.git](https://github.com/HJLeslye/Power-Window-Simulator.git)
   ```
2. **Environment Setup:** Ensure you have the appropriate runtime installed (e.g., [Insert requirement, e.g., Java Runtime Environment (JRE) / Python 3.x / Node.js]).
3. **Execution:**
   [Insert specific instruction, e.g., Run the executable `.jar` / Execute `python main.py` / Open `index.html` in a browser].

---

## Contact Details

> **Leslye Hernández Jiménez**
> *Engineering in Information and Communication Technologies*
>
> **LinkedIn**: [View Profile](https://www.linkedin.com/in/leslye-hernandez-jimenez/)
> **Email**: [hdezj.leslye@gmail.com](mailto:hdezj.leslye@gmail.com)

---
*Developed as a software-in-the-loop (SITL) prototype for automotive logic validation.*
