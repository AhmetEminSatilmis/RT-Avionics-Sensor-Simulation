# Real-Time Avionics Sensor Simulation

![Language](https://img.shields.io/badge/language-C%2B%2B14-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## 🚀 Overview

This project is a **multi-threaded C++ simulation** designed to model an avionics sensor network. It demonstrates high-performance system programming concepts by simulating real-time data acquisition from aircraft sensors (Altimeters and Thermometers) and processing this data concurrently through a central control unit.

The project serves as a practical implementation of the **Producer-Consumer design pattern**, focusing on thread safety, resource management, and object-oriented architecture without external dependencies.

## 🛠 Technical Highlights & Skills

This repository demonstrates proficiency in the following C++ system programming concepts:

* **Concurrency & Multithreading:** Utilization of `std::thread` to execute sensor readings (Producers) and data processing (Consumer) in parallel.
* **Thread Synchronization:** Implementation of `std::mutex`, `std::unique_lock`, and `std::condition_variable` to prevent race conditions and ensure safe access to shared resources.
* **Modern Memory Management (RAII):** Extensive use of `std::unique_ptr` and `std::make_unique` to ensure automatic resource cleanup and prevent memory leaks.
* **Object-Oriented Design (OOD):** Application of inheritance and runtime polymorphism through a base `Sensor` abstract class.
* **Data Structures:** Usage of `std::queue` for buffering sensor data and `std::vector` for managing sensor objects.

## 📂 System Architecture

The simulation consists of three core components:

1.  **Sensors (Producers):**
    * **Abstract Base Class (`Sensor`):** Defines the interface for all sensors.
    * **`Altimeter`:** Simulates altitude readings with specific warning thresholds (Low Altitude).
    * **`Thermometer`:** Simulates engine/cabin temperature readings with overheating warnings.

2.  **Control Unit (Consumer):**
    * **`SensorControlUnit`:** Acts as the central processing node. It manages a thread-safe queue where sensors push data. It uses a condition variable to sleep when the queue is empty and wake up only when new data arrives, optimizing CPU usage.

3.  **Execution Flow:**
    * The `main` thread initializes the system.
    * A **Display Thread** is spawned to process and log data from the queue.
    * A **Sensor Task Thread** is spawned to simulate the continuous reading of sensors.

## ⚙️ Build & Run

### Prerequisites
* A C++ compiler supporting **C++14** or later (GCC, Clang, MSVC).

### Compilation (Linux / macOS)
```bash
g++ -std=c++14 -pthread main.cpp -o avionics_sim
./avionics_sim
Compilation (Windows with MinGW)
Bash
g++ -std=c++14 main.cpp -o avionics_sim.exe
avionics_sim.exe
📊 Sample Output
Plaintext
---System Initiated----
[WARNING] Engine Thermometer is too high
Sensor: Main Altimeter Value: 1023.5
Sensor: Engine Thermometer Value: 29.1
Sensor: Cabin Thermometer Value: 24.0
...
Main Altimeter is Erased from Memory.
----Sensor Data Stream Terminated-----
----Program Terminated----
🔮 Future Improvements
Implementation of a Circular Buffer (Ring Buffer) to replace std::queue for deterministic latency suitable for embedded systems.

Adding a Logger class to write telemetry data to a file asynchronously.

Unit tests using Google Test (gtest) framework.

📜 License
This project is open-source and available under the MIT License.
