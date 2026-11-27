#ifndef INCOME_H
#define INCOME_H

#include "Transaction.h"

class Income : public Transaction {
public:
    Income(int id, double amount, const std::string& category,
           const std::string& description, const std::string& date);

    std::string getType() const override;
    void displayRow() const override;
    std::string toFileString() const override;
};

#endif
