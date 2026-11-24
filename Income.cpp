#include "Income.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Unit-V: Constructors in Derived Classes (delegation to base class Transaction)
Income::Income(int id, double amount, const string& category,
               const string& description, const string& date)
    : Transaction(id, amount, category, description, date) {
}

// Unit-VI: Function Overriding
string Income::getType() const {
    return "Income";
}

// Unit-II: Manipulators (setw, left, right, fixed, setprecision)
void Income::displayRow() const {
    cout << "| " << setw(6)  << left  << getId()
         << "| " << setw(9)  << left  << getType()
         << "| " << setw(12) << right << fixed << setprecision(2) << getAmount()
         << " | " << setw(15) << left  << getCategory()
         << "| " << setw(25) << left  << getDescription()
         << "| " << setw(12) << left  << getDate()
         << "|\n";
}

// Serialization format for file storage
string Income::toFileString() const {
    ostringstream oss;
    oss << "INCOME|"
        << getId() << "|"
        << fixed << setprecision(2) << getAmount() << "|"
        << getCategory() << "|"
        << getDescription() << "|"
        << getDate();
    return oss.str();
}
