#include "Transaction.h"

using namespace std;

int Transaction::totalTransactionCount = 0;

Transaction::Transaction(int id, double amount, const string& category,
                         const string& description, const string& date) {
    this->id = id;
    this->amount = amount;
    this->category = category;
    this->description = description;
    this->date = date;

    totalTransactionCount++;
}

Transaction::~Transaction() {
    totalTransactionCount--;
}

int Transaction::getId() const {
    return id;
}

double Transaction::getAmount() const {
    return amount;
}

string Transaction::getCategory() const {
    return category;
}

string Transaction::getDescription() const {
    return description;
}

string Transaction::getDate() const {
    return date;
}

int Transaction::getTotalTransactionCount() {
    return totalTransactionCount;
}
