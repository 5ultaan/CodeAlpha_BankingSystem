# 🏦 Smart Banking System — CodeAlpha Internship

### C++ Programming Internship — Task 3

A **console-based Smart Banking System** developed in **C++** as part of the **CodeAlpha C++ Programming Internship**.

The application demonstrates Object-Oriented Programming concepts by managing customers, bank accounts, transactions, balances, deposits, withdrawals, fund transfers, and transaction history through a menu-driven banking interface.

---

## 📌 Project Overview

The **Smart Banking System** is a C++ console application designed to simulate basic banking operations.

The system allows users to:

* Create customers
* Create bank accounts
* Deposit money
* Withdraw money
* Transfer funds between accounts
* View account information
* View recent transaction history

The project uses separate classes for **Customer**, **Account**, and **Transaction**, while the **Bank** class manages customers and accounts.

---

## 🎯 Internship Task

This project was completed as **Task 3: Banking System** for the **CodeAlpha C++ Programming Internship**.

### Task Requirements

The internship task required the application to:

* Design classes for `Customer`, `Account`, and `Transaction`.
* Implement functions to create and manage customers and accounts.
* Include deposits, withdrawals, and fund transfers.
* Store transaction history.
* Allow users to view recent transactions.
* Display account information, balances, and transaction details.

The implementation fulfills these requirements using Object-Oriented Programming, dynamic memory allocation, transaction tracking, input validation, and a structured console interface.

---

## ✨ Features

### 👤 Customer Management

The system allows a new customer to be created using:

* Customer ID
* Full name
* CNIC
* Phone number

Each customer receives an automatically generated customer ID.

Example:

```text
Customer ID: CUS1001
```

The system also checks whether a customer with the same CNIC already exists.

---

### 🏦 Account Management

Accounts can be created for existing customers.

Each account contains:

* Account number
* Customer CNIC
* Account type
* Current balance
* Transaction history

The system automatically generates account numbers.

Example:

```text
Account Number: 500001
```

Supported account types include:

```text
Saving
Current
```

---

### 💰 Deposit Money

Users can deposit money into an existing account.

The system:

1. Finds the account.
2. Validates the deposit amount.
3. Adds the amount to the balance.
4. Creates a transaction record.
5. Displays the updated balance.

Example:

```text
Deposit completed successfully.
New Balance: 50000.00
```

---

### 💸 Withdraw Money

Users can withdraw money from an existing account.

Before completing the withdrawal, the system checks whether the account has sufficient funds.

If the balance is insufficient:

```text
Error: Insufficient balance.
```

If successful, the amount is deducted and a withdrawal transaction is recorded.

---

### 🔄 Fund Transfer

The system supports transferring money between two accounts.

The transfer process:

1. Takes the sender account number.
2. Takes the receiver account number.
3. Checks whether both accounts exist.
4. Prevents transfers to the same account.
5. Checks the sender's balance.
6. Deducts the amount from the sender.
7. Adds the amount to the receiver.
8. Records transactions for both accounts.

Example:

```text
Fund transfer completed successfully.
Sender Balance: 35000.00
```

---

### 📋 Transaction History

Every successful deposit, withdrawal, and transfer creates a transaction record.

Each transaction stores:

* Transaction type
* Amount
* Description
* Date and time

The system allows users to view the **recent transaction history** of an account.

The transaction display includes:

```text
Type            Amount        Description              Date and Time
----------------------------------------------------------------------
Deposit         50000.00      Cash Deposit             24-09-2026 10:30 AM
Withdrawal      5000.00       Cash Withdrawal          24-09-2026 10:35 AM
Transfer        10000.00      Transfer to 500002       24-09-2026 10:40 AM
```

The application displays up to the **10 most recent transactions** for an account.

---

### 📊 Account Information

Users can view account details including:

* Account number
* Account holder
* Account type
* Current balance

Example:

```text
========================================================
                  ACCOUNT INFORMATION
========================================================

Account Number : 500001
Account Holder : Sultan
Account Type   : Saving
Current Balance: 45000.00
```

---

### 🛡️ Input Validation

The application validates several types of input.

Validation includes:

* Empty text fields
* Positive transaction amounts
* Digit-only account numbers
* Existing customer verification
* Existing account verification
* Duplicate customer CNIC detection
* Insufficient balance checking
* Same sender/receiver account prevention
* Invalid menu selections

---

### 🎨 Colored Console Interface

The application uses the Windows console API to provide a visually organized interface.

Different colors are used for:

* Titles
* Borders
* Labels
* Input prompts
* Success messages
* Error messages
* Menu options

---

# 🏗️ Object-Oriented Design

The project is structured around four main classes:

```text
                 ┌───────────────────┐
                 │       Bank        │
                 └─────────┬─────────┘
                           │
             ┌─────────────┴─────────────┐
             │                           │
             ▼                           ▼
      ┌──────────────┐            ┌──────────────┐
      │   Customer   │            │   Account    │
      └──────────────┘            └──────┬───────┘
                                         │
                                         ▼
                                  ┌──────────────┐
                                  │ Transaction  │
                                  └──────────────┘
```

---

## 👤 Customer Class

The `Customer` class represents a bank customer.

### Attributes

```cpp
string customerID;
string fullName;
string cnic;
string phoneNumber;
```

### Main Responsibilities

* Store customer information.
* Provide customer ID.
* Provide CNIC.
* Provide customer name.
* Display customer information.

---

## 🏦 Account Class

The `Account` class represents a customer's bank account.

### Attributes

```cpp
string accountNumber;
string customerCNIC;
string accountType;
double balance;
```

It also maintains a dynamic array of transactions.

### Main Responsibilities

* Store account information.
* Maintain account balance.
* Deposit money.
* Withdraw money.
* Add transaction records.
* Display account information.
* Display recent transactions.

---

## 💳 Transaction Class

The `Transaction` class represents an individual banking transaction.

### Attributes

```cpp
string type;
double amount;
string description;
string dateTime;
```

Each transaction automatically records the current date and time when it is created.

Transaction types include:

```text
Deposit
Withdrawal
Transfer
```

---

## 🏛️ Bank Class

The `Bank` class acts as the main management class for the banking system.

It maintains collections of:

```cpp
Customer**
Account**
```

### Main Responsibilities

* Create customers.
* Create accounts.
* Find customers.
* Find accounts.
* Process deposits.
* Process withdrawals.
* Process transfers.
* Display account information.
* Display transaction history.

---

# 🧠 C++ Concepts Demonstrated

This project provides practical experience with several important C++ concepts.

## Object-Oriented Programming

The application uses classes and objects to model real-world banking entities.

The main classes are:

```text
Customer
Account
Transaction
Bank
```

---

## Encapsulation

Class attributes are kept private and accessed through public member functions.

For example:

```cpp
private:
    string accountNumber;
    double balance;
```

Public functions are then used to interact with the account.

---

## Constructors & Destructors

The project uses constructors to initialize objects.

The `Account` class also includes a destructor to release dynamically allocated transaction memory.

The `Bank` class similarly releases dynamically allocated customers and accounts when the program ends.

---

## Dynamic Memory Allocation

The project uses dynamic arrays instead of fixed-size collections.

For example:

```cpp
Transaction* transactions;
Customer** customers;
Account** accounts;
```

Memory is dynamically expanded when the current capacity is reached.

---

## Dynamic Capacity Expansion

The system automatically increases storage capacity when required.

For transactions:

```text
Initial Capacity
       ↓
       5
       ↓
Capacity Full
       ↓
Double Capacity
       ↓
       10
       ↓ 
Capacity Full
       ↓
       20
       ↓
     ...
```

Similar capacity management is used for customers and accounts.

---

## File-Independent Runtime Data

Unlike the previous CodeAlpha Login & Registration project, this banking system currently keeps its customer, account, and transaction data **in memory while the program is running**.

The program does not currently save banking records to a permanent database or external data file.

---

## Date & Time Handling

Transactions automatically record their creation date and time.

The program uses:

```cpp
time_t
tm
localtime_s()
strftime()
```

The displayed format is:

```text
DD-MM-YYYY HH:MM AM/PM
```

---

# 🔄 System Workflow

```text
                   ┌──────────────────────┐
                   │    Start Program     │
                   └──────────┬───────────┘
                              │
                              ▼
                   ┌──────────────────────┐
                   │   Smart Banking      │
                   │       System         │
                   └──────────┬───────────┘
                              │
             ┌────────────────┼─────────────────┐
             │                │                 │
             ▼                ▼                 ▼
      Create Customer   Create Account    Banking Operations
             │                │                 │
             │                │        ┌────────┼────────┐
             │                │        │        │        │
             │                │        ▼        ▼        ▼
             │                │     Deposit  Withdraw Transfer
             │                │
             └────────────────┼─────────────────┘
                              │
                              ▼
                   ┌──────────────────────┐
                   │ View Account         │
                   │ Information          │
                   └──────────┬───────────┘
                              │
                              ▼
                   ┌──────────────────────┐
                   │ View Transaction     │
                   │ History              │
                   └──────────┬───────────┘
                              │
                              ▼
                   ┌──────────────────────┐
                   │        Exit          │
                   └──────────────────────┘
```

---

# 🖥️ Main Menu

When the program starts, users see the following menu:

```text
========================================================================
                         SMART BANKING SYSTEM
========================================================================

  [1] Create Customer
  [2] Create Account
  [3] Deposit Money
  [4] Withdraw Money
  [5] Transfer Funds
  [6] View Account Information
  [7] View Transaction History
  [8] Exit System

Enter your choice:
```

---

# 🧪 Example Usage

## 1. Create Customer

```text
========================================================================
                       CREATE NEW CUSTOMER
========================================================================

Enter full name: Sultan
Enter CNIC: 35202-1234567-1
Enter phone number: 03001234567

Customer created successfully.
Customer ID: CUS1001
```

---

## 2. Create Account

```text
========================================================================
                       CREATE BANK ACCOUNT
========================================================================

Enter existing customer CNIC: 35202-1234567-1
Enter account type (Saving/Current): Saving

Account created successfully.
Account Number: 500001
```

---

## 3. Deposit Money

```text
========================================================================
                         DEPOSIT MONEY
========================================================================

Enter account number: 500001
Enter deposit amount: 50000

Deposit completed successfully.
New Balance: 50000.00
```

---

## 4. Withdraw Money

```text
========================================================================
                        WITHDRAW MONEY
========================================================================

Enter account number: 500001
Enter withdrawal amount: 5000

Withdrawal completed successfully.
Remaining Balance: 45000.00
```

---

## 5. Transfer Funds

```text
========================================================================
                         FUND TRANSFER
========================================================================

Enter sender account number: 500001
Enter receiver account number: 500002
Enter transfer amount: 10000

Fund transfer completed successfully.
Sender Balance: 35000.00
```

---

# 📊 Account Information

The account information screen displays:

```text
========================================================================
                      ACCOUNT INFORMATION
========================================================================

Account Number : 500001
Account Holder : Sultan
Account Type   : Saving
Current Balance: 35000.00
```

---

# 📜 Transaction History

The transaction history screen displays recent transactions in a structured table:

```text
========================================================================
                   RECENT TRANSACTION HISTORY
========================================================================

Type            Amount        Description              Date and Time
------------------------------------------------------------------------
Deposit         50000.00      Cash Deposit             24-09-2026 10:30 AM
Withdrawal       5000.00      Cash Withdrawal          24-09-2026 10:35 AM
Transfer        10000.00      Transfer to 500002       24-09-2026 10:40 AM
```

The system keeps transaction records in memory and displays the latest 10 transactions when more than 10 transactions exist.

---

# ⚠️ Important Project Limitation

This is an **educational console-based banking simulation**, not a real banking application.

The current implementation does not include:

* Permanent database storage
* User authentication
* Password protection
* Encryption
* Real banking APIs
* Interest calculations
* ATM/card management
* Multi-user concurrent access
* Real-world banking security controls

Customer, account, and transaction information exists only during the current program execution.

---

# 📂 Project Structure

```text
CodeAlpha_BankingSystem/
│── 1. Screenshot.jpg
│── 2. Screenshot.jpg
│── 3. Screenshot.jpg
│── 4. Screenshot.jpg
│── 5. Screenshot.jpg
│── 6. Screenshot.jpg
│── 7. Screenshot.jpg
│── 8. Screenshot.jpg
│── 9. Screenshot.jpg
├── README.md
└── main.cpp
```

The complete banking system implementation is currently contained in `main.cpp`.

---

# ⚙️ Requirements

To compile and run this project, you need:

* Windows operating system
* C++ compiler
* Visual Studio or another compatible C++ IDE/compiler
* Support for:

  * `windows.h`
  * Standard C++ libraries

The application is designed primarily for **Windows** because it uses the Windows Console API.

---

# 🚀 How to Run

### 1. Clone the Repository

```bash
git clone https://github.com/5ultaan/CodeAlpha_BankingSystem.git
```

### 2. Open the Project

Open `main.cpp` using:

* Visual Studio
* Code::Blocks
* Another compatible C++ IDE

### 3. Compile

Compile the `main.cpp` file using a compatible C++ compiler.

### 4. Run

Start the application and select an option from the banking menu.

A typical flow is:

```text
Create Customer
       ↓
Create Account
       ↓
Deposit Money
       ↓
Withdraw / Transfer
       ↓
View Account Information
       ↓
View Transaction History
```

---

# 🔮 Future Improvements

Possible improvements for future versions include:

* Database integration using MySQL or SQLite.
* Permanent customer and account storage.
* Login and authentication system.
* Password-protected customer accounts.
* Secure transaction authorization.
* Account deletion and modification.
* Multiple accounts per customer with improved management.
* Interest calculation for savings accounts.
* Monthly statements.
* Transaction search and filtering.
* Improved transaction categorization.
* Administrator dashboard.
* GUI-based banking interface.
* Better validation for CNIC and phone numbers.
* Modern C++ containers such as `vector` instead of manual dynamic arrays.

---

# 🎓 Learning Outcomes

Through this project, practical experience was gained in:

* Object-Oriented Programming
* Classes and objects
* Constructors and destructors
* Encapsulation
* Dynamic memory allocation
* Pointers and pointer-to-pointer structures
* Dynamic arrays
* Memory management
* Function design
* Transaction processing
* Date and time handling
* Input validation
* Exception handling
* Console application development

---

# 🎓 Internship Information

**Internship:** C++ Programming Internship
**Organization:** CodeAlpha
**Task:** Task 3 — Banking System

This project was developed as part of the practical programming tasks assigned during the **CodeAlpha C++ Programming Internship**.

The project focuses on applying C++ Object-Oriented Programming concepts to a practical banking-management scenario.

---

# 👨‍💻 Author

**Sultan Shahzad Awan**

BS Artificial Intelligence Student
University of Central Punjab

### Profiles

* **LinkedIn:** [linkedin.com/in/sultanshahzadawan](https://www.linkedin.com/in/sultanshahzadawan)
* **GitHub:** [github.com/5ultaan](https://github.com/5ultaan)

---

# ⭐ Acknowledgment

Thanks to **CodeAlpha** for providing the internship opportunity and practical project-based learning experience in C++ programming.

---

### 📌 Repository Information

**Repository:** `CodeAlpha_BankingSystem`

**Project:** Smart Banking System
**Language:** C++
**Internship:** CodeAlpha C++ Programming Internship
**Task:** 3
