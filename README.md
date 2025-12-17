## 🏦 Bank Management System

[cite_start]A Final Project for the **Programming (1) - CSE126** course at Alexandria University [cite: 8][cite_start], Faculty of Engineering [cite: 3][cite_start], Computer & Communication Program[cite: 5].

---

### ✨ Project Objective

[cite_start]Our objective was not to simply meet the academic requirements[cite: 13, 155], but to address the challenge of building a **complete and robust Bank Management System** using the **C programming language** in a console environment. [cite_start]The core focus was on **code structure**, **data integrity**, and **comprehensive error handling**[cite: 143, 150, 151].

[cite_start]This project models essential bank operations [cite: 13][cite_start], ensuring user security via a file-based login [cite: 15-17] [cite_start]and managing persistent data storage for all accounts and transactions [cite: 23, 59, 95-97].

### 🛠️ Key Implemented Features

[cite_start]The system requires a successful **LOGIN** using credentials from `users.txt` [cite: 15-17] [cite_start]before accessing the full menu[cite: 110, 111].

#### 📂 Data and Account Management
* [cite_start]**LOAD:** Reads and initializes the system with account data from the comma-delimited `accounts.txt` file [cite: 23-25].
* [cite_start]**ADD:** Creates a new account, automatically setting the status to 'active' [cite: 62] [cite_start]and the date opened to the system's current date[cite: 61]. [cite_start]It ensures the account number is unique [cite: 63] [cite_start]and validated (10 digits)[cite: 146, 147].
* [cite_start]**DELETE:** Removes an existing account [cite: 64][cite_start], but only if its current balance is **zero**[cite: 67].
* [cite_start]**MODIFY:** Allows updating the account's name, mobile, and email address[cite: 68, 71].
* [cite_start]**CHANGE\_STATUS:** Toggles the account status between 'active' and 'inactive'[cite: 75].
* [cite_start]**DELETEMULTIPLE (Bonus):** An advanced feature to delete accounts in bulk based on a specific creation date or those inactive for over 90 days with zero balance [cite: 129-131].

#### 💰 Transactions and Queries
* [cite_start]**QUERY / ADVANCED SEARCH:** Standard search by Account Number [cite: 29, 30] [cite_start]and advanced search by keyword in the account holder's name[cite: 40, 41].
* **WITHDRAW / DEPOSIT / TRANSFER:** Financial operations must adhere to specific rules:
    * [cite_start]The account must be **active**[cite: 80, 85, 89].
    * [cite_start]Transactions (Withdraw/Deposit) must be $\le$ \$10,000 per transaction[cite: 83, 87].
    * [cite_start]Withdrawals check against a \$50,000 maximum daily limit[cite: 79, 84].
* [cite_start]**REPORT:** Prints the last 5 transactions [cite: 93] [cite_start]recorded in the account's dedicated history file (e.g., `9124123456.txt`)[cite: 95, 96].

#### 🗃️ Output and Persistence
* [cite_start]**PRINT (SORT):** Displays all account data, sortable by **Name**, **Balance**, or **Date Opened**[cite: 103, 104].
* [cite_start]**SAVE:** Writes the current system data back to `accounts.txt`[cite: 107]. [cite_start]This option is presented after any modification function[cite: 108].
* [cite_start]**QUIT:** Exits the program[cite: 109, 126].

### 💻 Technical Implementation Highlights

* [cite_start]**Modularity:** Strict separation of code into function-specific source (`.c`) and header (`.h`) files[cite: 142]. [cite_start]Every task is a separate function[cite: 152].
* [cite_start]**Data Validation:** Comprehensive checks on Account Number length, digit format [cite: 146, 147][cite_start], email format [cite: 148][cite_start], and general number inputs[cite: 149].
* [cite_start]**Data Structure:** Use of C `struct` to manage account data, including a nested structure for the date opened (month and year)[cite: 14].
* [cite_start]**User Interface:** Maintain a clear and user-friendly menu-driven interface[cite: 140, 153, 154].

### 👥 Group Members

*(List your group members here)*
