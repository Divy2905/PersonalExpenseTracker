#ifndef EXPENSE_TRACKER_H
#define EXPENSE_TRACKER_H

#include <string>
#include "Transaction.h"

const int MAX_TRANSACTIONS = 200;

class ExpenseTracker {
private:
    Transaction* transactions[MAX_TRANSACTIONS];
    int transactionCount;

    void printTableHeader() const;
    void printTableFooter() const;

public:
    ExpenseTracker();
    ~ExpenseTracker();

    bool addTransaction(Transaction* transaction);
    bool deleteTransaction(int id);
    int getNextId() const;
    bool hasTransaction(int id) const;

    void viewAllTransactions() const;
    void searchById(int id) const;
    void searchByCategory(const std::string& category) const;
    void displayBalance() const;
    void displayMonthlySummary(int month, int year) const;
    void displayCategoryWiseExpenses() const;

    Transaction* getTransactionAt(int index) const;
    int getTransactionCount() const;
    void clear();
};

#endif
