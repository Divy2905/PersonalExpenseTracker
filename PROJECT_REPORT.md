# INNOVATIVE ASSIGNMENT
## Report on
# “PERSONAL EXPENSE TRACKER”
### For Course: 2CS502CC26 / 2CS502CC25
## OBJECT ORIENTED PROGRAMMING
### B. Tech. Semester III

**Report Prepared By:**  
Divy Vekariya (Roll / Registration: `Divy2905`)

**Report Submitted To:**  
Prof. (Course Instructor)

---

### NIRMA UNIVERSITY
**School of Technology, Institute of Technology**  
*NAAC ACCREDITED ‘A+’ GRADE*  
Ahmedabad – 382481, Gujarat, India

---

## 1. Abstract on the Project

Personal financial tracking is a vital daily habit that enables individuals to manage cash flows, control impulsive spending, and plan savings. **Personal Expense Tracker** is a modular, console-based financial management system built using C++ Object-Oriented Programming (OOP). 

The software enables users to record multiple streams of income and expenditure, view clear tabular transaction histories, perform fast lookups by ID and category, compute real-time account balances, evaluate monthly financial summaries, and break down spending category-wise. Built strictly according to university academic standards, the project demonstrates core OOP principles without reliance on high-level third-party libraries.

---

## 2. Introduction

Personal Expense Tracker models a real-world personal ledger system. Operating entirely in the console with formatted tables and robust input validation, the program presents a clean, menu-driven interface.

Users can add income sources (e.g., Salary, Freelance) or expense items (e.g., Food, Travel, Rent, Education). Each entry is validated, stamped with an auto-incrementing unique identifier, and immediately persisted to disk via a plain-text storage engine (`transactions.txt`). The application features runtime polymorphic method dispatch, native array storage, dynamic heap management via `new` and `delete`, and automatic data restoration upon launch.

---

## 3. Objectives

1. **Practical OOP Implementation:** Apply fundamental and advanced OOP concepts in an end-to-end, working C++ software project.
2. **Data Modeling & Encapsulation:** Model financial records with strict access control and data hiding.
3. **Inheritance & Abstraction:** Implement an abstract base class (`Transaction`) with specialized derived classes (`Income` and `Expense`).
4. **Runtime Polymorphism:** Utilize base-class pointers and virtual method dispatch to process transactions dynamically at runtime.
5. **Memory Management & Object Lifecycles:** Practice dynamic allocation (`new`) and safe deallocation (`delete`) inside class destructors to avoid memory leaks.
6. **Data Persistence:** Implement safe, delimited file I/O operations using standard C++ file streams (`ifstream` and `ofstream`).

---

## 4. Main Features

- **Standard C++ Compatibility:** Built using standard C++ (compatible with GCC / MinGW `g++`).
- **Menu-Driven Interface:** 9 distinct operations accessible through an interactive numeric menu.
- **Add Income:** Prompts for amount, category, description, and date; automatically assigns unique IDs.
- **Add Expense:** Records expenditure with category classification and immediate disk persistence.
- **Tabular History Display:** Uses `<iomanip>` manipulators (`setw`, `left`, `right`, `fixed`, `setprecision`) to output an aligned table.
- **Search Capabilities:** Search by unique Transaction ID or case-insensitive category substring matching.
- **Real-Time Account Balance:** Computes `Total Income`, `Total Expenses`, and `Net Balance = Income - Expenses`.
- **Monthly Summary Reports:** Filters records by month and year (`YYYY-MM`) to evaluate net monthly savings.
- **Category-Wise Expense Breakdown:** Aggregates total expenditure per category using native arrays and computes percentage shares.
- **Deletion with Confirmation:** Deletes specific records, shifts array elements, and synchronizes changes to disk.
- **Crash-Proof Input Validation:** Employs buffer flushing (`cin.clear()`, `cin.ignore()`) to prevent infinite loops on non-numeric inputs.
- **Automated Data Persistence:** Loads existing transactions from `transactions.txt` at startup and auto-saves on mutation.

---

## 5. Class Hierarchy

```
                    ┌────────────────────────────┐
                    │        Transaction         │ ◄─── Abstract Base Class
                    │   (pure virtual methods)   │
                    └──────────────┬─────────────┘
                                   │
                    ┌──────────────┴─────────────┐
                    │ (Public Inheritance: IS-A) │
                    ▼                            ▼
         ┌─────────────────────┐      ┌─────────────────────┐
         │       Income        │      │       Expense       │
         │   (Derived Class)   │      │   (Derived Class)   │
         └──────────┬──────────┘      └──────────┬──────────┘
                    │                            │
                    └──────────────┬─────────────┘
                                   │
                                   ▼ (Pointers stored in array)
                    ┌────────────────────────────┐
                    │       ExpenseTracker       │ ◄─── Manager Class (Composition)
                    └──────────────┬─────────────┘
                                   │
                                   ▼ (Object passed by reference)
                    ┌────────────────────────────┐
                    │        FileManager         │ ◄─── File I/O Engine
                    └────────────────────────────┘
```

---

## 6. Class Descriptions

### 1. `Transaction` (Abstract Base Class)
- **Role:** Common parent class for all financial entries.
- **Attributes:** `int id`, `double amount`, `string category`, `string description`, `string date`.
- **Static Member:** `static int totalTransactionCount;` tracks live objects in memory.
- **Member Functions:** Parameterized constructor using the `this->` pointer, virtual destructor (`virtual ~Transaction()`), public getters (`getId()`, `getAmount()`, etc.), and `static int getTotalTransactionCount()`.
- **Pure Virtual Functions:**
  - `virtual string getType() const = 0;`
  - `virtual void displayRow() const = 0;`
  - `virtual string toFileString() const = 0;`

### 2. `Income` (Derived Class)
- **Role:** Represents money earned (Salary, Freelance, Investment).
- **Inheritance:** Publicly inherits from `Transaction`.
- **Constructor Delegation:** Passes arguments to `: Transaction(...)`.
- **Function Overrides:** Returns `"Income"`, renders green-formatted table rows, and serializes records as `INCOME|...`.

### 3. `Expense` (Derived Class)
- **Role:** Represents money spent (Food, Travel, Rent, Education).
- **Inheritance:** Publicly inherits from `Transaction`.
- **Constructor Delegation:** Passes arguments to `: Transaction(...)`.
- **Function Overrides:** Returns `"Expense"`, renders table rows, and serializes records as `EXPENSE|...`.

### 4. `ExpenseTracker` (Manager Class)
- **Role:** Manages in-memory records and business logic.
- **Composition:** Contains an array of base-class pointers: `Transaction* transactions[MAX_TRANSACTIONS];` and `int transactionCount;`.
- **Destructor:** `~ExpenseTracker()` iterates through active pointers and releases heap memory via `delete`.
- **Core Operations:** `addTransaction()`, `deleteTransaction()`, `viewAllTransactions()` (polymorphic loop), `displayBalance()`, `displayMonthlySummary()`, and `displayCategoryWiseExpenses()` (pure array aggregation).

### 5. `FileManager` (File Handler)
- **Role:** Handles text persistence to decouple file streams from domain logic.
- **Methods:**
  - `saveToFile(filename, const ExpenseTracker& tracker)`: Writes records using `ofstream`.
  - `loadFromFile(filename, ExpenseTracker& tracker)`: Reads lines using `ifstream`, parses tokens with `stringstream`, and dynamically instantiates `new Income(...)` or `new Expense(...)`.

---

## 7. OOP Concepts Used

| OOP Pillar / Concept | Implementation in Project |
| :--- | :--- |
| **Encapsulation** | All entity fields (`id`, `amount`, `category`, etc.) are declared `private` in `Transaction.h`. Modification from outside is prohibited; access is granted only via public getters. |
| **Data Abstraction** | `Transaction` declares pure virtual functions (`= 0`), hiding implementation details and prohibiting direct instantiation (`Transaction t;` is illegal). |
| **Inheritance** | Hierarchical inheritance (`Income : public Transaction` and `Expense : public Transaction`) reuses base attributes and establishes an "IS-A" hierarchy. |
| **Function Overriding** | Derived classes override `getType()`, `displayRow()`, and `toFileString()` using the `override` specifier. |
| **Runtime Polymorphism** | In `ExpenseTracker.cpp`, calling `transactions[i]->displayRow()` dynamically resolves to `Income::displayRow()` or `Expense::displayRow()` at runtime via the `vtable`. |
| **The `this` Pointer** | Explicitly used in `Transaction::Transaction` (`this->id = id;`) to resolve parameter-member ambiguity. |
| **Static Members** | `static int totalTransactionCount` and static function `getTotalTransactionCount()` manage global active instance counts. |
| **Constructors & Destructors**| Base and derived parameterized constructors manage state initialization; virtual destructors and manager destructors free dynamic heap memory via `delete`. |
| **Composition** | `ExpenseTracker` **has-a** collection of `Transaction*` pointers and coordinates with `FileManager`. |
| **Formatted Manipulators** | `<iomanip>` manipulators (`setw`, `left`, `right`, `fixed`, `setprecision`) ensure professional aligned text presentation. |

---

## 8. Running the Project on Your System

### 1. Project Directory
Ensure the source and header files are in the same folder:
```
PersonalExpenseTracker/
├── main.cpp
├── Transaction.h / Transaction.cpp
├── Income.h / Income.cpp
├── Expense.h / Expense.cpp
├── ExpenseTracker.h / ExpenseTracker.cpp
├── FileManager.h / FileManager.cpp
└── build.bat
```

### 2. Compilation via Terminal
Open terminal / PowerShell in the project directory:
```bash
g++ -std=c++17 -Wall -Wextra main.cpp Transaction.cpp Income.cpp Expense.cpp ExpenseTracker.cpp FileManager.cpp -o ExpenseTracker.exe
```

### 3. Execution
```powershell
.\ExpenseTracker.exe
```
*(Alternatively, simply double-click `build.bat` on Windows to compile and run automatically).*

---

## 9. Output Snippets

### Main Menu
```text
========================================================
 Welcome to the Personal Expense Tracker System (C++ OOP)
========================================================
[System] Initializing data storage...
[Info] Successfully loaded 7 transaction(s) from transactions.txt.

========================================
       PERSONAL EXPENSE TRACKER         
========================================
 1. Add Income
 2. Add Expense
 3. View All Transactions
 4. Search Transactions
 5. View Account Balance
 6. Monthly Summary
 7. Category-wise Expenses
 8. Delete Transaction
 9. Exit
========================================
Enter your choice (1-9): 
```

---

### Adding Income (Choice 1)
```text
--- ADD NEW INCOME ---
Enter income amount (INR): 50000
Enter category (e.g., Salary, Freelance): Salary
Enter description: Monthly Tech Salary
Enter date (YYYY-MM-DD): 2026-11-01

[Success] Income transaction #1 added and saved!
```

---

### Adding Expense (Choice 2)
```text
--- ADD NEW EXPENSE ---
Enter expense amount (INR): 2000
Enter category (e.g., Food, Travel, Rent): Food
Enter description: Groceries and snacks
Enter date (YYYY-MM-DD): 2026-11-03

[Success] Expense transaction #3 added and saved!
```

---

### Viewing All Transactions in Tabular Format (Choice 3)
```text
================================ TRANSACTION HISTORY ================================
+-------+----------+---------------+----------------+---------------------------+--------------+
| ID    | Type     | Amount (INR)  | Category       | Description               | Date         |
+-------+----------+---------------+----------------+---------------------------+--------------+
| 1     | Income   |     50000.00 | Salary         | Monthly Tech Salary      | 2026-11-01  |
| 2     | Income   |     15000.00 | Freelance      | Web Development Gig      | 2026-11-10  |
| 3     | Expense  |      2000.00 | Food           | Groceries and snacks     | 2026-11-03  |
| 5     | Expense  |      3000.00 | Shopping       | Winter clothing          | 2026-11-12  |
| 6     | Expense  |      2000.00 | Education      | C++ Programming Books    | 2026-11-15  |
| 7     | Expense  |       800.00 | Food           | Snacks and Coffee        | 2026-11-20  |
| 8     | Income   |      1000.00 | Salary         | Part-time stipend        | 2026-11-23  |
+-------+----------+---------------+----------------+---------------------------+--------------+
Total Transactions: 7
Active Objects in Memory: 7
```

---

### Viewing Real-Time Account Balance (Choice 5)
```text
==================== ACCOUNT BALANCE ====================
  Total Income   : INR     66000.00
  Total Expenses : INR      7800.00
---------------------------------------------------------
  Current Balance: INR     58200.00
=========================================================
```

---

### Monthly Summary Report (Choice 6)
```text
--- MONTHLY SUMMARY ---
Enter Month (1 - 12): 11
Enter Year (e.g., 2026): 2026

================= MONTHLY SUMMARY (11/2026) =================
  Total Income   : INR     66000.00
  Total Expenses : INR      7800.00
---------------------------------------------------------
  Net Savings    : INR     58200.00
  Transactions   : 7
=========================================================
```

---

### Category-Wise Expense Distribution (Choice 7)
```text
================ CATEGORY-WISE EXPENSES ================
+----------------------+---------------+------------+
| Category             | Amount (INR)  | % of Total |
+----------------------+---------------+------------+
| Food                 |       2800.00 |      35.9% |
| Shopping             |       3000.00 |      38.5% |
| Education            |       2000.00 |      25.6% |
+----------------------+---------------+------------+
| Total Expenses       |       7800.00 |   100.0%   |
+----------------------+---------------+------------+
```

---

### Deleting a Transaction with Confirmation (Choice 8)
```text
--- DELETE TRANSACTION ---
Enter Transaction ID to delete: 4

--- Search Result for ID: 4 ---
+-------+----------+---------------+----------------+---------------------------+--------------+
| ID    | Type     | Amount (INR)  | Category       | Description               | Date         |
+-------+----------+---------------+----------------+---------------------------+--------------+
| 4     | Expense  |      1500.00 | Travel         | Metro and Uber cab       | 2026-11-05  |
+-------+----------+---------------+----------------+---------------------------+--------------+
Are you sure you want to delete this transaction? (y/n): y
[Success] Transaction #4 deleted successfully!
```

---

## 10. Conclusion

The **Personal Expense Tracker** project provides a comprehensive, practical demonstration of Object-Oriented Programming in C++. By combining abstract base interfaces, derived classes, dynamic memory management (`new`/`delete`), runtime polymorphic dispatch, static class tracking, and plain-text file persistence, the project translates core classroom concepts into a clean, functional real-world utility.
