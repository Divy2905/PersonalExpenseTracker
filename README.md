# Personal Expense Tracker (C++ OOP)
### Designed for Nirma University — Course 2CS502CC25 (Object Oriented Programming)

An educational, console-based personal finance management system designed strictly according to the syllabus of **Nirma University (Course Code: 2CS502CC25)** based on reference textbooks by *E. Balagurusamy* and *Herbert Schildt*.

---

## 1. Syllabus Mapping (100% Strictly Aligned)

| Syllabus Unit | Topics Covered in This Project | Code Implementation |
| :--- | :--- | :--- |
| **Unit-II: Tokens, Expressions & Control Structures** | • Memory Management Operators (`new` and `delete`)<br>• Manipulators (`setw`, `left`, `right`, `fixed`, `setprecision`)<br>• Scope Resolution Operator (`::`)<br>• Call by Reference (`ExpenseTracker& tracker`) | Dynamically allocating transactions with `new Income(...)` and freeing memory with `delete`. Formatted tabular reports with `<iomanip>`. |
| **Unit-III: Classes and Objects** | • Specifying a Class, Private Members<br>• Arrays within a Class (`Transaction* transactions[MAX]`)<br>• Static Data Members (`static int totalTransactionCount`)<br>• Static Member Functions (`getTotalTransactionCount()`)<br>• Objects as Function Arguments | Encapsulated transaction attributes, static active object counter, and category aggregation using native arrays without any STL containers. |
| **Unit-IV: Constructors and Destructors** | • Parameterized Constructors<br>• Default Constructors<br>• Destructors (`~ExpenseTracker()`, `~Transaction()`) | Base & derived constructors, virtual destructor in base class, and destructor in manager class that loops and deletes heap objects. |
| **Unit-V: Inheritance** | • Defining Derived Classes (`class Income : public Transaction`)<br>• Abstract Classes (`Transaction` with `= 0`)<br>• Constructors in Derived Classes | Single hierarchical inheritance with constructor delegation (`: Transaction(...)`). |
| **Unit-VI: Pointers, Virtual Functions & Polymorphism** | • Pointers to Objects & Derived Classes<br>• The `this` Pointer (`this->id = id;`)<br>• Virtual Functions & Pure Virtual Functions<br>• Runtime Polymorphism via `vtable` | Base class pointer array calling `transactions[i]->displayRow()` dynamically resolving at runtime. |

---

## 2. Project Features

1. **Add Income:** Uses `new Income(...)` to allocate memory dynamically and saves to `transactions.txt`.
2. **Add Expense:** Uses `new Expense(...)` to allocate memory dynamically and saves to `transactions.txt`.
3. **View All Transactions:** Tabular view displaying all records with column formatting and live count of active objects in memory via static function.
4. **Search Transactions:**
   - Search by Unique Transaction ID.
   - Search by Category (case-insensitive search).
5. **View Account Balance:** Computes Total Income, Total Expenses, and Net Balance.
6. **Monthly Summary:** Enter month and year to view financial figures for that month.
7. **Category-wise Expenses:** Aggregates spending by category using **pure arrays and loops** without any STL map.
8. **Delete Transaction:** Frees heap memory using `delete` and shifts array elements.
9. **Persistent Storage:** Reads and writes `transactions.txt` using basic C++ file streams (`ifstream`, `ofstream`).

---

## 3. Class Structure

```
PersonalExpenseTracker/
│
├── main.cpp              # Application entry point, menu loop, and input validation
│
├── Transaction.h         # Abstract base class (Private members, pure virtual functions, static counter)
├── Transaction.cpp       # Base constructor with 'this->' pointer, destructor, getters, static function
│
├── Income.h              # Income derived class declaration
├── Income.cpp            # Income overrides (getType, displayRow, toFileString)
│
├── Expense.h             # Expense derived class declaration
├── Expense.cpp           # Expense overrides (getType, displayRow, toFileString)
│
├── ExpenseTracker.h      # Manager class with array of pointers (Transaction* transactions[200])
├── ExpenseTracker.cpp    # Business logic, calculations, array manipulation, and memory cleanup with delete
│
├── FileManager.h         # File I/O handler declaration
├── FileManager.cpp       # File persistence using basic ifstream and ofstream
│
├── transactions.txt      # Plain-text delimited data storage
├── README.md             # Project documentation
└── VIVA_QUESTIONS.md     # 25 syllabus-aligned viva questions and model answers
```

---

## 4. How to Compile and Run

```bash
cd "c:\Users\admin\Desktop\OOP\PersonalExpenseTracker"
g++ -std=c++17 -Wall -Wextra main.cpp Transaction.cpp Income.cpp Expense.cpp ExpenseTracker.cpp FileManager.cpp -o ExpenseTracker.exe
.\ExpenseTracker.exe
```
