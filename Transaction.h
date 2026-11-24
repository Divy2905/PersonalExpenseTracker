#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// ============================================================================
// Class: Transaction (Abstract Base Class)
//
// Aligns 100% with Nirma University Course 2CS502CC25:
// - Unit-II: Scope Resolution Operator (::), Manipulators
// - Unit-III: Classes and Objects, Private Members, Static Data Member,
//             Static Member Function
// - Unit-IV: Parameterized Constructor, Destructor
// - Unit-V:  Abstract Class
// - Unit-VI: Virtual Functions, Pure Virtual Functions, this Pointer
// ============================================================================

class Transaction {
private:
    int id;
    double amount;
    std::string category;
    std::string description;
    std::string date; // Format: YYYY-MM-DD

    // Unit-III: Static Data Member (tracks total active transactions)
    static int totalTransactionCount;

public:
    // Unit-IV: Parameterized Constructor
    Transaction(int id, double amount, const std::string& category,
                const std::string& description, const std::string& date);

    // Unit-IV & Unit-VI: Virtual Destructor (Crucial for base class with virtual methods)
    virtual ~Transaction();

    // Public Getters (Unit-I & Unit-III: Encapsulation)
    int getId() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDescription() const;
    std::string getDate() const;

    // Unit-III: Static Member Function
    static int getTotalTransactionCount();

    // Unit-V & Unit-VI: Pure Virtual Functions (Makes Transaction an Abstract Class)
    virtual std::string getType() const = 0;
    virtual void displayRow() const = 0;
    virtual std::string toFileString() const = 0;
};

#endif // TRANSACTION_H
