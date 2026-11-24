#include "Transaction.h"

using namespace std;

// Unit-III: Defining and initializing the static data member outside the class
int Transaction::totalTransactionCount = 0;

// Unit-IV: Parameterized Constructor
// Unit-VI: Demonstrates the 'this' pointer to resolve ambiguity between parameters and members
Transaction::Transaction(int id, double amount, const string& category,
                         const string& description, const string& date) {
    this->id = id;
    this->amount = amount;
    this->category = category;
    this->description = description;
    this->date = date;

    // Increment static counter whenever a transaction object is created
    totalTransactionCount++;
}

// Unit-IV & Unit-VI: Virtual Destructor
Transaction::~Transaction() {
    // Decrement static counter whenever a transaction object is destroyed
    totalTransactionCount--;
}

// Getter for Transaction ID
int Transaction::getId() const {
    return id;
}

// Getter for Amount
double Transaction::getAmount() const {
    return amount;
}

// Getter for Category
string Transaction::getCategory() const {
    return category;
}

// Getter for Description
string Transaction::getDescription() const {
    return description;
}

// Getter for Date
string Transaction::getDate() const {
    return date;
}

// Unit-III: Static Member Function to access the static counter
int Transaction::getTotalTransactionCount() {
    return totalTransactionCount;
}
