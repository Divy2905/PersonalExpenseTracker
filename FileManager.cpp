#include "FileManager.h"
#include "ExpenseTracker.h"
#include "Income.h"
#include "Expense.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

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
            outFile << item->toFileString() << "\n";
        }
    }

    outFile.close();
    return true;
}

bool FileManager::loadFromFile(const string& filename,
                               ExpenseTracker& tracker) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
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

        if (getline(ss, typeStr, '|') &&
            getline(ss, idStr, '|') &&
            getline(ss, amountStr, '|') &&
            getline(ss, category, '|') &&
            getline(ss, description, '|') &&
            getline(ss, date)) {

            try {
                int id = stoi(idStr);
                double amount = stod(amountStr);

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
