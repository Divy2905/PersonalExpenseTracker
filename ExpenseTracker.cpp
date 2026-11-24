#include "ExpenseTracker.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// Helper function: Converts string to lowercase using basic character loop (Unit-II)
static string toLowerString(const string& str) {
    string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

// Unit-IV: Default Constructor
ExpenseTracker::ExpenseTracker() {
    transactionCount = 0;
    for (int i = 0; i < MAX_TRANSACTIONS; i++) {
        transactions[i] = nullptr;
    }
}

// Unit-IV & Unit-II: Destructor freeing heap-allocated objects with delete
ExpenseTracker::~ExpenseTracker() {
    clear();
}

// Print formatted header for tabular display (Unit-II: Manipulators)
void ExpenseTracker::printTableHeader() const {
    cout << "+-------+----------+---------------+----------------+---------------------------+--------------+\n";
    cout << "| ID    | Type     | Amount (INR)  | Category       | Description               | Date         |\n";
    cout << "+-------+----------+---------------+----------------+---------------------------+--------------+\n";
}

// Print formatted footer for tabular display
void ExpenseTracker::printTableFooter() const {
    cout << "+-------+----------+---------------+----------------+---------------------------+--------------+\n";
}

// Adds a new transaction pointer (Unit-VI: Pointer to Derived Class stored in base pointer)
bool ExpenseTracker::addTransaction(Transaction* transaction) {
    if (transaction == nullptr) {
        return false;
    }
    if (transactionCount >= MAX_TRANSACTIONS) {
        cout << "[Error] Storage full! Cannot add more transactions.\n";
        delete transaction; // Free memory if storage is full
        return false;
    }

    transactions[transactionCount] = transaction;
    transactionCount++;
    return true;
}

// Determines the next available unique ID
int ExpenseTracker::getNextId() const {
    int maxId = 0;
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i]->getId() > maxId) {
            maxId = transactions[i]->getId();
        }
    }
    return maxId + 1;
}

// Checks if a transaction with the given ID exists
bool ExpenseTracker::hasTransaction(int id) const {
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i]->getId() == id) {
            return true;
        }
    }
    return false;
}

// Unit-II & Unit-III: Deletes transaction and shifts array elements
bool ExpenseTracker::deleteTransaction(int id) {
    int foundIndex = -1;
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i]->getId() == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        return false;
    }

    // Unit-II: Memory Management Operator 'delete'
    delete transactions[foundIndex];

    // Unit-III: Shift remaining array elements left to maintain contiguous order
    for (int i = foundIndex; i < transactionCount - 1; i++) {
        transactions[i] = transactions[i + 1];
    }

    transactions[transactionCount - 1] = nullptr;
    transactionCount--;
    return true;
}

// Unit-VI: Demonstrates Runtime Polymorphism using array of base class pointers
void ExpenseTracker::viewAllTransactions() const {
    if (transactionCount == 0) {
        cout << "\n[Info] No transactions recorded yet.\n";
        return;
    }

    cout << "\n================================ TRANSACTION HISTORY ================================\n";
    printTableHeader();
    // Polymorphic Call: At runtime, transactions[i]->displayRow() dynamically
    // calls either Income::displayRow() or Expense::displayRow() via the vtable
    for (int i = 0; i < transactionCount; i++) {
        transactions[i]->displayRow();
    }
    printTableFooter();
    cout << "Total Transactions: " << transactionCount << "\n";
}

// Searches for a transaction by ID
void ExpenseTracker::searchById(int id) const {
    bool found = false;
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i]->getId() == id) {
            if (!found) {
                cout << "\n--- Search Result for ID: " << id << " ---\n";
                printTableHeader();
                found = true;
            }
            transactions[i]->displayRow();
        }
    }

    if (found) {
        printTableFooter();
    } else {
        cout << "\n[Info] No transaction found with ID: " << id << "\n";
    }
}

// Searches transactions matching a category
void ExpenseTracker::searchByCategory(const string& category) const {
    string target = toLowerString(category);
    bool found = false;

    for (int i = 0; i < transactionCount; i++) {
        string itemCat = toLowerString(transactions[i]->getCategory());
        if (itemCat.find(target) != string::npos) {
            if (!found) {
                cout << "\n--- Search Results for Category: \"" << category << "\" ---\n";
                printTableHeader();
                found = true;
            }
            transactions[i]->displayRow();
        }
    }

    if (found) {
        printTableFooter();
    } else {
        cout << "\n[Info] No transactions found matching category: \"" << category << "\"\n";
    }
}

// Calculates and displays total income, total expenses, and balance
void ExpenseTracker::displayBalance() const {
    double totalIncome = 0.0;
    double totalExpense = 0.0;

    for (int i = 0; i < transactionCount; i++) {
        // Unit-VI: Runtime Polymorphic call to virtual getType()
        if (transactions[i]->getType() == "Income") {
            totalIncome += transactions[i]->getAmount();
        } else if (transactions[i]->getType() == "Expense") {
            totalExpense += transactions[i]->getAmount();
        }
    }

    double currentBalance = totalIncome - totalExpense;

    cout << "\n==================== ACCOUNT BALANCE ====================\n";
    cout << fixed << setprecision(2);
    cout << "  Total Income   : INR " << setw(12) << totalIncome << "\n";
    cout << "  Total Expenses : INR " << setw(12) << totalExpense << "\n";
    cout << "---------------------------------------------------------\n";
    cout << "  Current Balance: INR " << setw(12) << currentBalance << "\n";
    if (currentBalance < 0) {
        cout << "  [Warning] You are operating at a net deficit!\n";
    }
    cout << "=========================================================\n";
}

// Generates a summary for a specific month and year
void ExpenseTracker::displayMonthlySummary(int month, int year) const {
    double monthlyIncome = 0.0;
    double monthlyExpense = 0.0;
    int count = 0;

    for (int i = 0; i < transactionCount; i++) {
        const string& date = transactions[i]->getDate();
        if (date.length() >= 7 && date[4] == '-') {
            try {
                int itemYear = stoi(date.substr(0, 4));
                int itemMonth = stoi(date.substr(5, 2));

                if (itemYear == year && itemMonth == month) {
                    count++;
                    if (transactions[i]->getType() == "Income") {
                        monthlyIncome += transactions[i]->getAmount();
                    } else if (transactions[i]->getType() == "Expense") {
                        monthlyExpense += transactions[i]->getAmount();
                    }
                }
            } catch (...) {
                // Ignore parsing errors for malformed dates
            }
        }
    }

    cout << "\n================= MONTHLY SUMMARY ("
         << (month < 10 ? "0" : "") << month << "/" << year << ") =================\n";
    if (count == 0) {
        cout << "[Info] No transactions recorded for this month.\n";
        return;
    }

    double netSavings = monthlyIncome - monthlyExpense;

    cout << fixed << setprecision(2);
    cout << "  Total Income   : INR " << setw(12) << monthlyIncome << "\n";
    cout << "  Total Expenses : INR " << setw(12) << monthlyExpense << "\n";
    cout << "---------------------------------------------------------\n";
    cout << "  Net Savings    : INR " << setw(12) << netSavings << "\n";
    cout << "  Transactions   : " << count << "\n";
    cout << "=========================================================\n";
}

// Unit-III: Aggregates category spending using standard arrays without any STL containers
void ExpenseTracker::displayCategoryWiseExpenses() const {
    string categories[MAX_TRANSACTIONS];
    double totals[MAX_TRANSACTIONS];
    int categoryCount = 0;
    double grandExpenseTotal = 0.0;

    // Aggregate expenses using basic array lookup
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i]->getType() == "Expense") {
            string cat = transactions[i]->getCategory();
            double amt = transactions[i]->getAmount();

            // Check if category is already recorded
            int foundIndex = -1;
            for (int j = 0; j < categoryCount; j++) {
                if (categories[j] == cat) {
                    foundIndex = j;
                    break;
                }
            }

            if (foundIndex != -1) {
                totals[foundIndex] += amt;
            } else {
                categories[categoryCount] = cat;
                totals[categoryCount] = amt;
                categoryCount++;
            }

            grandExpenseTotal += amt;
        }
    }

    cout << "\n================ CATEGORY-WISE EXPENSES ================\n";
    if (categoryCount == 0) {
        cout << "[Info] No expense records available to summarize.\n";
        return;
    }

    cout << "+----------------------+---------------+------------+\n";
    cout << "| Category             | Amount (INR)  | % of Total |\n";
    cout << "+----------------------+---------------+------------+\n";

    for (int i = 0; i < categoryCount; i++) {
        double percentage = (grandExpenseTotal > 0.0)
                            ? (totals[i] / grandExpenseTotal) * 100.0
                            : 0.0;

        cout << "| " << setw(21) << left  << categories[i]
             << "| " << setw(13) << right << fixed << setprecision(2) << totals[i]
             << " | " << setw(9)  << right << fixed << setprecision(1) << percentage << "% |\n";
    }

    cout << "+----------------------+---------------+------------+\n";
    cout << "| Total Expenses       | " << setw(13) << right << fixed << setprecision(2) << grandExpenseTotal << " |   100.0%   |\n";
    cout << "+----------------------+---------------+------------+\n";
}

// Returns a pointer to the transaction at given index
Transaction* ExpenseTracker::getTransactionAt(int index) const {
    if (index >= 0 && index < transactionCount) {
        return transactions[index];
    }
    return nullptr;
}

// Returns current count of transactions
int ExpenseTracker::getTransactionCount() const {
    return transactionCount;
}

// Unit-II & IV: Clears all transactions and frees memory using 'delete'
void ExpenseTracker::clear() {
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i] != nullptr) {
            delete transactions[i];
            transactions[i] = nullptr;
        }
    }
    transactionCount = 0;
}
