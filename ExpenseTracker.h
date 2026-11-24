#ifndef EXPENSE_TRACKER_H
#define EXPENSE_TRACKER_H

#include <string>
#include "Transaction.h"

// Maximum capacity for transactions array (Unit-III: Arrays within a Class)
const int MAX_TRANSACTIONS = 200;

// ============================================================================
// Class: ExpenseTracker
//
// Aligns 100% with Nirma University Course 2CS502CC25:
// - Unit-II:  Memory Management Operators (new and delete)
// - Unit-III: Arrays within a Class, Arrays of Objects/Pointers
// - Unit-IV:  Destructor (frees dynamically allocated heap memory)
// - Unit-VI:  Pointers to Derived Classes, Virtual Functions, Polymorphism
// ============================================================================

class ExpenseTracker {
private:
    // Unit-III & VI: Array of base class pointers to derived objects
    Transaction* transactions[MAX_TRANSACTIONS];
    int transactionCount;

    // Helper methods for formatting
    void printTableHeader() const;
    void printTableFooter() const;

public:
    // Unit-IV: Default Constructor
    ExpenseTracker();

    // Unit-IV: Destructor (Essential for freeing dynamic memory with delete)
    ~ExpenseTracker();

    // Transaction Management
    bool addTransaction(Transaction* transaction);
    bool deleteTransaction(int id);
    int getNextId() const;
    bool hasTransaction(int id) const;

    // Views and Reports (Unit-VI: Demonstrates Runtime Polymorphism)
    void viewAllTransactions() const;
    void searchById(int id) const;
    void searchByCategory(const std::string& category) const;
    void displayBalance() const;
    void displayMonthlySummary(int month, int year) const;
    void displayCategoryWiseExpenses() const;

    // Accessors for FileManager
    Transaction* getTransactionAt(int index) const;
    int getTransactionCount() const;
    void clear();
};

#endif // EXPENSE_TRACKER_H
