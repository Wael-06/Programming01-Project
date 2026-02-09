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

### 🚀 Installation & Build Instructions

**Requirements:**  
* gcc (C Compiler)  
* make (Build automation tool)

**Steps:**  
1. Navigate to the project directory.  
2. Build the project by running `make`. This compiles all source files within `src/` and generates the executable.  
3. Run the program with `./bank_system`.  
4. To remove object files and reset the build environment, run `make clean`.

### 🚀 Key Functionalities

* **Account Lifecycle:** Comprehensive CRUD operations with business logic constraints.  
* **Financial Engine:** Logic-gated transactions (Deposits, Withdrawals, P2P Transfers) with daily liquidity limits ($50,000).  
* **Data Analysis:** Multi-parameter sorting (Name, Balance, Date) for administrative reporting.  
* **Reliability:** Hardened against Buffer Overflows and Data Corruption via atomic-style save operations.  

### 👥 Contributors

The development of this system was a collaborative effort by:

* Youssef Wael - [@Wael-06](https://github.com/Wael-06)  
* Moataz Ahmed - [@Wizza1911](https://github.com/Wizza1911)  
* Eyad Tamer - [@EyadDodo](https://github.com/EyadDodo)  
* Abdalrahamn Khaled - [@abdelrhman-khaled13](https://github.com/abdelrhman-khaled13)  

Note: This project is designed for Linux and MinGW environments. The Makefile handles header dependencies automatically, ensuring only modified files are recompiled.

**Note:** This project is designed for Linux and MinGW environments. The Makefile handles header dependencies automatically, ensuring only modified files are recompiled.
