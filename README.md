# Real-Time Avionics Sensor Simulation ✈️

A C++ based prototype simulating a **real-time avionics sensor monitoring system**. This project demonstrates the handling of critical flight data (altitude, engine temperature) using Object-Oriented Programming (OOP) principles, dynamic memory management, and sensor fusion logic.

## 🚀 Project Overview

The primary goal of this simulation is to model the architecture of an embedded software system used in aerospace vehicles. It continuously monitors sensor inputs, processes data streams, and triggers automated warnings when safety thresholds are breached.

### Key Technical Features
* **Runtime Polymorphism:** Utilizes an abstract base class (`Sensor`) and derived classes (`Altimeter`, `Thermometer`) to manage diverse hardware interfaces through a unified pointer system.
* **Dynamic Memory Management:** Demonstrates manual memory control using raw pointers, dynamic allocation (`new`), and proper deallocation (`delete`) strategies to prevent memory leaks during system shutdown.
* **Real-Time Simulation Loop:** Implements a continuous monitoring loop (`while(true)`) with `std::this_thread::sleep_for` to simulate sensor sampling rates and processing latency.
* **Fault Detection:** Includes logic for immediate threshold checking (e.g., Low Altitude Warning, Engine Overheat) to simulate critical safety alerts.

## 📂 System Architecture

The project follows a modular OOP design:

1.  **`Sensor` (Abstract Base Class):**
    * Defines the interface for all sensors.
    * Contains pure virtual functions: `read_data()` and `check_warning()`.
    * Ensures strict contract adherence for any new sensor type added to the system.

2.  **`Altimeter` (Derived Class):**
    * Simulates altitude data acquisition.
    * **Safety Logic:** Triggers a warning if the aircraft drops below the safe altitude threshold (1010 units).

3.  **`Thermometer` (Derived Class):**
    * Simulates engine temperature monitoring.
    * **Safety Logic:** Triggers a warning if engine temperature exceeds the critical limit (28°C).
