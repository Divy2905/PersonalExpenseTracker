#ifndef INCOME_H
#define INCOME_H

#include "Transaction.h"

// ============================================================================
// Class: Income (Derived Class)
//
// Aligns with Nirma University Course 2CS502CC25:
// - Unit-V:  Defining Derived Class (public inheritance from Transaction)
// - Unit-V:  Constructors in Derived Classes (delegation to base constructor)
// - Unit-VI: Virtual Functions and Function Overriding
// ============================================================================

class Income : public Transaction {
public:
    // Parameterized Constructor
    Income(int id, double amount, const std::string& category,
           const std::string& description, const std::string& date);

    // Overridden methods (Unit-VI: Polymorphism)
    std::string getType() const override;
    void displayRow() const override;
    std::string toFileString() const override;
};

#endif // INCOME_H
