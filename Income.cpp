#include "Income.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Income::Income(int id, double amount, const string& category,
               const string& description, const string& date)
    : Transaction(id, amount, category, description, date) {
}

string Income::getType() const {
    return "Income";
}

void Income::displayRow() const {
    cout << "| " << setw(6)  << left  << getId()
         << "| " << setw(9)  << left  << getType()
         << "| " << setw(12) << right << fixed << setprecision(2) << getAmount()
         << " | " << setw(15) << left  << getCategory()
         << "| " << setw(25) << left  << getDescription()
         << "| " << setw(12) << left  << getDate()
         << "|\n";
}

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
