# 🏦 Bank Management System (V2)

A modular, high-performance C-based administrative tool designed for secure financial record-keeping and data manipulation. This system focuses on **data integrity**, **input validation**, and **persistent storage**, simulating the backend logic of a retail banking environment.

### 🎯 Core Objectives
The primary goal of this project was to engineer a **"zero-crash" environment**. By prioritizing rigorous error handling and memory safety, the system ensures that user data and financial records remain consistent even under malicious or improper usage.

### 🛠 Technical Architecture
The system is built on a modular architecture using **C** for low-level memory management and file I/O operations. 

* **Build Automation:** Uses `GNU Make` to handle multi-file compilation and dependency management.
* **Data Persistence:** Uses a structured CSV-style flat-file database (`accounts.txt`) to maintain state across sessions.
* **Security Layer:** Implements a credential-hashing simulation via `users.txt` to gatekeep administrative functions.
* **Transaction Logging:** Every financial movement triggers an automated update to individual ledger files (e.g., `acc_12345.txt`), ensuring a complete audit trail.
* **Sort & Search Algorithms:** Optimized searching by account number and keyword-based advanced search for efficient data retrieval.

---

### 🚀 Installation & Build Instructions

#### Requirements
* **gcc**: C Compiler
* **make**: Build automation tool (Essential for multi-file projects)

#### 1. Verify Prerequisites
Open a terminal and ensure the tools are installed:
```bash
gcc --version
make --version

🚀 Installation & Build Instructions (Continued)
2. Build the Project
Navigate to the project directory and run:

make
This command compiles all source files within src/ and generates the executable.

3. Run the Program

./bank_system

4. Maintenance
To remove object files and reset the build environment:

make clean
⚡ Key Functionalities
Account Lifecycle: Comprehensive CRUD (Create, Read, Update, Delete) operations integrated with strict business logic constraints.

Financial Engine: Logic-gated transactions (Deposits, Withdrawals, P2P Transfers) featuring daily liquidity limits ($50,000).

Data Analysis: Multi-parameter sorting (Name, Balance, Date) for detailed administrative reporting.

Reliability: Hardened against Buffer Overflows and Data Corruption via atomic-style save operations.

👥 Contributors
The development of this system was a collaborative effort by:

Youssef Wael - @Wael-06

Moataz Ahmed - @Wizza1911

Eyad Tamer - @EyadDodo

Abdalrahamn Khaled - @abdelrhman-khaled13

[!NOTE] This project is optimized for Linux and MinGW environments. The Makefile handles header dependencies automatically, ensuring only modified files are recompiled to optimize build times.
