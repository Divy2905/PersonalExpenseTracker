#include "FileManager.h"
#include "ExpenseTracker.h"
#include "Income.h"
#include "Expense.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Saves all transactions from tracker into the file
bool FileManager::saveToFile(const string& filename,
                             const ExpenseTracker& tracker) {
    ofstream outFile(filename, ios::out | ios::trunc);
    if (!outFile.is_open()) {
        cerr << "[Error] Unable to open file for writing: " << filename << "\n";
        return false;
    }

    int count = tracker.getTransactionCount();
    for (int i = 0; i < count; i++) {
        Transaction* item = tracker.getTransactionAt(i);
        if (item != nullptr) {
            // Unit-VI: Polymorphic call to virtual function toFileString()
            outFile << item->toFileString() << "\n";
        }
    }

    outFile.close();
    return true;
}

// Loads transactions from the file and populates the ExpenseTracker
bool FileManager::loadFromFile(const string& filename,
                               ExpenseTracker& tracker) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        // File does not exist yet (normal on fresh startup)
        return false;
    }

    tracker.clear();
    string line;
    int loadedCount = 0;

    while (getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string typeStr, idStr, amountStr, category, description, date;

        // Parse fields delimited by '|'
        if (getline(ss, typeStr, '|') &&
            getline(ss, idStr, '|') &&
            getline(ss, amountStr, '|') &&
            getline(ss, category, '|') &&
            getline(ss, description, '|') &&
            getline(ss, date)) {

            try {
                int id = stoi(idStr);
                double amount = stod(amountStr);

                // Unit-II: Dynamic object creation with 'new'
                // Unit-VI: Pointer to Derived Class passed to base-pointer method
                if (typeStr == "INCOME") {
                    tracker.addTransaction(new Income(id, amount, category, description, date));
                    loadedCount++;
                } else if (typeStr == "EXPENSE") {
                    tracker.addTransaction(new Expense(id, amount, category, description, date));
                    loadedCount++;
                }
            } catch (...) {
                cerr << "[Warning] Skipping corrupted line in " << filename << ": " << line << "\n";
            }
        }
    }

    inFile.close();
    if (loadedCount > 0) {
        cout << "[Info] Successfully loaded " << loadedCount << " transaction(s) from " << filename << ".\n";
    }
    return true;
}
