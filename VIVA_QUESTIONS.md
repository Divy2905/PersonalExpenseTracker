# Viva Voce Examination Questions & Answers
### Nirma University — Course 2CS502CC25 (Object Oriented Programming)

This document contains 25 targeted questions and answers prepared specifically for the **Nirma University BTech CSE OOP Practical Examination**, directly referencing the implementation in the **Personal Expense Tracker** project.

---

### Unit-II: Tokens, Expressions, Control Structures & Functions

#### Q1. Where are the Memory Management Operators (`new` and `delete`) used in your project?
**Answer:**
- In `main.cpp` and `FileManager.cpp`, we dynamically allocate memory for new transactions using `new`:
  ```cpp
  Transaction* newIncome = new Income(id, amount, category, description, date);
  ```
- In `ExpenseTracker.cpp`, we free dynamically allocated heap memory using `delete`:
  - When deleting a specific transaction in `deleteTransaction(int id)`: `delete transactions[foundIndex];`
  - In `clear()` and the destructor `~ExpenseTracker()`:
    ```cpp
    for (int i = 0; i < transactionCount; i++) {
        delete transactions[i];
    }
    ```

#### Q2. What Manipulators did you use, and why?
**Answer:**
We used manipulators from `<iomanip>`:
- `setw(width)`: Sets column field width for table alignment.
- `left` / `right`: Specifies left alignment for text and right alignment for numeric currency.
- `fixed` and `setprecision(2)`: Enforces currency values to be printed with exactly two decimal places (e.g., `50000.00`).

#### Q3. Where is Call by Reference used in your project?
**Answer:**
In `FileManager.cpp`:
```cpp
bool FileManager::loadFromFile(const string& filename, ExpenseTracker& tracker)
```
Passing `tracker` by reference (`&`) ensures that changes made while populating transactions directly modify the caller's `tracker` object without making an unnecessary, expensive copy.

---

### Unit-III: Classes and Objects

#### Q4. How did you implement "Arrays within a Class"?
**Answer:**
In `ExpenseTracker.h`:
```cpp
Transaction* transactions[MAX_TRANSACTIONS];
int transactionCount;
```
`ExpenseTracker` holds an array of base-class pointers inside the class to manage multiple transaction objects, directly demonstrating **Arrays within a Class** and **Arrays of Objects**.

#### Q5. Where did you use a Static Data Member and a Static Member Function?
**Answer:**
- In `Transaction.h`:
  ```cpp
  private:
      static int totalTransactionCount; // Static data member
  public:
      static int getTotalTransactionCount(); // Static member function
  ```
- In `Transaction.cpp`, it is defined outside the class:
  ```cpp
  int Transaction::totalTransactionCount = 0;
  ```
- Every time a `Transaction` constructor runs, `totalTransactionCount++`. When its destructor runs, `totalTransactionCount--`.
- Calling `Transaction::getTotalTransactionCount()` displays the active number of objects in memory.

---

### Unit-IV: Constructors and Destructors

#### Q6. What is the role of the Destructor in `ExpenseTracker`?
**Answer:**
In `ExpenseTracker.cpp`:
```cpp
ExpenseTracker::~ExpenseTracker() {
    clear();
}
```
When `ExpenseTracker tracker;` goes out of scope at the end of `main()`, the destructor is invoked automatically. It loops through the `transactions` array and issues `delete` on each allocated pointer, ensuring zero memory leaks.

#### Q7. Why is the destructor in `Transaction` declared as `virtual`?
**Answer:**
```cpp
virtual ~Transaction();
```
When deleting a derived object (`Income` or `Expense`) through a base-class pointer (`Transaction*`), declaring the base destructor `virtual` guarantees that the derived destructor is executed first, followed by the base destructor. Without `virtual`, only the base destructor would execute, leading to undefined behavior.

---

### Unit-V: Inheritance

#### Q8. What type of inheritance is used in this project?
**Answer:**
**Hierarchical Inheritance**:
- Base Class: `Transaction`
- Derived Classes: `Income : public Transaction` and `Expense : public Transaction`.
Both derived classes inherit common attributes (`id`, `amount`, `category`, `description`, `date`) from `Transaction`.

#### Q9. How do constructors work in your derived classes?
**Answer:**
In `Income.cpp` and `Expense.cpp`:
```cpp
Income::Income(int id, double amount, const string& category,
               const string& description, const string& date)
    : Transaction(id, amount, category, description, date) {
}
```
The derived class constructor uses base-class constructor delegation (`: Transaction(...)`) to pass parameter values to the parent constructor for initialization.

#### Q10. What makes `Transaction` an Abstract Class?
**Answer:**
A class containing at least one **pure virtual function** (`= 0`) is an Abstract Class.
In `Transaction.h`:
```cpp
virtual string getType() const = 0;
virtual void displayRow() const = 0;
virtual string toFileString() const = 0;
```
Because of `= 0`, direct instantiation like `Transaction t;` is blocked by the compiler. It forces `Income` and `Expense` to provide concrete implementations.

---

### Unit-VI: Pointers, Virtual Functions and Polymorphism

#### Q11. Where did you demonstrate the `this` pointer?
**Answer:**
In `Transaction.cpp`:
```cpp
Transaction::Transaction(int id, double amount, const string& category,
                         const string& description, const string& date) {
    this->id = id;
    this->amount = amount;
    this->category = category;
    this->description = description;
    this->date = date;
}
```
The `this` pointer is an implicit pointer passed to every non-static member function. It points to the calling object, resolving naming conflicts between parameter names and class member variables.

#### Q12. Where is "Pointer to Derived Class" used in your project?
**Answer:**
In `ExpenseTracker.h`, the array holds base-class pointers:
```cpp
Transaction* transactions[MAX_TRANSACTIONS];
```
When an `Income` or `Expense` object is allocated with `new`, its address is stored in this `Transaction*` base pointer:
```cpp
Transaction* newIncome = new Income(...);
tracker.addTransaction(newIncome);
```
A base-class pointer can point to any object of its publicly derived classes.

#### Q13. How is Runtime Polymorphism demonstrated in your project?
**Answer:**
In `ExpenseTracker.cpp`:
```cpp
for (int i = 0; i < transactionCount; i++) {
    transactions[i]->displayRow(); // Runtime Polymorphism
}
```
At runtime, C++ uses the **virtual table (`vtable`)** and **virtual pointer (`vptr`)** of the pointed-to object to determine whether `Income::displayRow()` or `Expense::displayRow()` should be called.

---

### General Architecture & File Handling

#### Q14. How did you implement category-wise expenses without using STL containers?
**Answer:**
In `ExpenseTracker::displayCategoryWiseExpenses()`, we used two parallel arrays:
```cpp
string categories[MAX_TRANSACTIONS];
double totals[MAX_TRANSACTIONS];
int categoryCount = 0;
```
We iterate through the transactions array. For each expense, we perform a linear search to check if the category already exists in `categories[]`. If found, we add to `totals[foundIndex]`. If not found, we insert the new category into the array. This adheres 100% to basic C++ array handling.

#### Q15. How does `FileManager` distinguish Income from Expense when loading records?
**Answer:**
Each line in `transactions.txt` begins with an identifier: `INCOME|...` or `EXPENSE|...`.
`FileManager::loadFromFile()` parses the first token:
- If `"INCOME"`, it calls `new Income(...)`.
- If `"EXPENSE"`, it calls `new Expense(...)`.
These pointers are passed to `tracker.addTransaction()`.
