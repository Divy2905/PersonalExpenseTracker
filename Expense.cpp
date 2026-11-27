#include "Expense.h"
#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

Expense::Expense(int id, double amount, const string& category,
                 const string& description, const string& date)
    : Transaction(id, amount, category, description, date) {
}

string Expense::getType() const {
    return "Expense";
}

void Expense::displayRow() const {
    cout << "| " << setw(6)  << left  << getId()
         << "| " << setw(9)  << left  << getType()
         << "| " << setw(12) << right << fixed << setprecision(2) << getAmount()
         << " | " << setw(15) << left  << getCategory()
         << "| " << setw(25) << left  << getDescription()
         << "| " << setw(12) << left  << getDate()
         << "|\n";
}

string Expense::toFileString() const {
    ostringstream oss;
    oss << "EXPENSE|"
        << getId() << "|"
        << fixed << setprecision(2) << getAmount() << "|"
        << getCategory() << "|"
        << getDescription() << "|"
        << getDate();
    return oss.str();
}
