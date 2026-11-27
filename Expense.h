#ifndef EXPENSE_H
#define EXPENSE_H

#include "Transaction.h"
#include <string>

class Expense : public Transaction {
public:
    Expense(int id, double amount, const std::string& category,
            const std::string& description, const std::string& date);

    std::string getType() const override;
    void displayRow() const override;
    std::string toFileString() const override;
};

#endif
