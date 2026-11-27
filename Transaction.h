#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    int id;
    double amount;
    std::string category;
    std::string description;
    std::string date;

    static int totalTransactionCount;

public:
    Transaction(int id, double amount, const std::string& category,
                const std::string& description, const std::string& date);

    virtual ~Transaction();

    int getId() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDescription() const;
    std::string getDate() const;

    static int getTotalTransactionCount();

    virtual std::string getType() const = 0;
    virtual void displayRow() const = 0;
    virtual std::string toFileString() const = 0;
};

#endif
