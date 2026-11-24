#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

// Unit-III: Forward declaration of ExpenseTracker to avoid circular includes
class ExpenseTracker;

// ============================================================================
// Class: FileManager
//
// Aligns 100% with Nirma University Course 2CS502CC25:
// - Unit-II:  Functions, Call by Reference (ExpenseTracker& tracker)
// - Unit-III: Objects as Function Arguments
// - Standard File Handling using basic C++ file streams (ifstream, ofstream)
// ============================================================================

class FileManager {
public:
    // Saves all transactions from tracker to file
    static bool saveToFile(const std::string& filename,
                           const ExpenseTracker& tracker);

    // Loads transactions from file into tracker (Unit-II: Pass by Reference)
    static bool loadFromFile(const std::string& filename,
                             ExpenseTracker& tracker);
};

#endif // FILE_MANAGER_H
