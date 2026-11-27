#include <iostream>
#include <string>
#include <cctype>
#include "Transaction.h"
#include "Income.h"
#include "Expense.h"
#include "ExpenseTracker.h"
#include "FileManager.h"

using namespace std;

const string DATA_FILE = "transactions.txt";

double getPositiveAmount(const string& prompt) {
    double amount = 0.0;
    while (true) {
        cout << prompt;
        if (cin >> amount) {
            if (amount > 0.0) {
                cin.ignore(1000, '\n');
                return amount;
            } else {
                cout << "[Error] Amount must be greater than zero. Please try again.\n";
            }
        } else {
            cout << "[Error] Invalid input! Please enter a valid number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

int getIntInRange(const string& prompt, int minVal, int maxVal) {
    int value = 0;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                cin.ignore(1000, '\n');
                return value;
            } else {
                cout << "[Error] Please enter a number between " << minVal << " and " << maxVal << ".\n";
            }
        } else {
            cout << "[Error] Invalid input! Please enter a valid integer.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

int getPositiveInt(const string& prompt) {
    int value = 0;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value > 0) {
                cin.ignore(1000, '\n');
                return value;
            } else {
                cout << "[Error] Value must be positive. Please try again.\n";
            }
        } else {
            cout << "[Error] Invalid input! Please enter a valid integer.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

string getNonEmptyString(const string& prompt) {
    string text;
    while (true) {
        cout << prompt;
        getline(cin, text);

        bool allSpaces = true;
        for (size_t i = 0; i < text.length(); i++) {
            if (text[i] != ' ' && text[i] != '\t') {
                allSpaces = false;
                break;
            }
        }

        if (text.empty() || allSpaces) {
            cout << "[Error] Input cannot be blank. Please try again.\n";
            continue;
        }

        if (text.find('|') != string::npos) {
            cout << "[Error] The '|' symbol is reserved for file storage. Please do not use it.\n";
            continue;
        }

        return text;
    }
}

string getValidDate(const string& prompt) {
    while (true) {
        string date = getNonEmptyString(prompt);

        if (date.length() == 10 && date[4] == '-' && date[7] == '-') {
            bool allDigits = true;
            for (int i = 0; i < 10; i++) {
                if (i == 4 || i == 7) continue;
                if (date[i] < '0' || date[i] > '9') {
                    allDigits = false;
                    break;
                }
            }

            if (allDigits) {
                int year = stoi(date.substr(0, 4));
                int month = stoi(date.substr(5, 2));
                int day = stoi(date.substr(8, 2));

                if (year >= 1900 && year <= 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                    return date;
                }
            }
        }

        cout << "[Error] Invalid date! Please use format YYYY-MM-DD (e.g., 2026-11-20).\n";
    }
}

void displayMainMenu() {
    cout << "\n========================================\n";
    cout << "       PERSONAL EXPENSE TRACKER         \n";
    cout << "========================================\n";
    cout << " 1. Add Income\n";
    cout << " 2. Add Expense\n";
    cout << " 3. View All Transactions\n";
    cout << " 4. Search Transactions\n";
    cout << " 5. View Account Balance\n";
    cout << " 6. Monthly Summary\n";
    cout << " 7. Category-wise Expenses\n";
    cout << " 8. Delete Transaction\n";
    cout << " 9. Exit\n";
    cout << "========================================\n";
}

int main() {
    cout << "========================================================\n";
    cout << " Welcome to the Personal Expense Tracker System (C++ OOP)\n";
    cout << "========================================================\n";

    ExpenseTracker tracker;

    cout << "[System] Initializing data storage...\n";
    if (FileManager::loadFromFile(DATA_FILE, tracker)) {
    } else {
        cout << "[Info] No existing database found. Starting with a fresh tracker.\n";
    }

    bool running = true;
    while (running) {
        displayMainMenu();
        int choice = getIntInRange("Enter your choice (1-9): ", 1, 9);

        switch (choice) {
            case 1: {
                cout << "\n--- ADD NEW INCOME ---\n";
                double amount = getPositiveAmount("Enter income amount (INR): ");
                string category = getNonEmptyString("Enter category (e.g., Salary, Freelance): ");
                string description = getNonEmptyString("Enter description: ");
                string date = getValidDate("Enter date (YYYY-MM-DD): ");

                int id = tracker.getNextId();
                Transaction* newIncome = new Income(id, amount, category, description, date);
                if (tracker.addTransaction(newIncome)) {
                    FileManager::saveToFile(DATA_FILE, tracker);
                    cout << "\n[Success] Income transaction #" << id << " added and saved!\n";
                }
                break;
            }

            case 2: {
                cout << "\n--- ADD NEW EXPENSE ---\n";
                double amount = getPositiveAmount("Enter expense amount (INR): ");
                string category = getNonEmptyString("Enter category (e.g., Food, Travel, Rent): ");
                string description = getNonEmptyString("Enter description: ");
                string date = getValidDate("Enter date (YYYY-MM-DD): ");

                int id = tracker.getNextId();
                Transaction* newExpense = new Expense(id, amount, category, description, date);
                if (tracker.addTransaction(newExpense)) {
                    FileManager::saveToFile(DATA_FILE, tracker);
                    cout << "\n[Success] Expense transaction #" << id << " added and saved!\n";
                }
                break;
            }

            case 3: {
                tracker.viewAllTransactions();
                cout << "Active Objects in Memory: " << Transaction::getTotalTransactionCount() << "\n";
                break;
            }

            case 4: {
                cout << "\n--- SEARCH TRANSACTIONS ---\n";
                cout << " 1. Search by Transaction ID\n";
                cout << " 2. Search by Category\n";
                int searchOption = getIntInRange("Enter your choice (1-2): ", 1, 2);

                if (searchOption == 1) {
                    int searchId = getPositiveInt("Enter Transaction ID to search: ");
                    tracker.searchById(searchId);
                } else {
                    string searchCat = getNonEmptyString("Enter Category to search: ");
                    tracker.searchByCategory(searchCat);
                }
                break;
            }

            case 5: {
                tracker.displayBalance();
                break;
            }

            case 6: {
                cout << "\n--- MONTHLY SUMMARY ---\n";
                int month = getIntInRange("Enter Month (1 - 12): ", 1, 12);
                int year = getIntInRange("Enter Year (e.g., 2026): ", 1900, 2100);
                tracker.displayMonthlySummary(month, year);
                break;
            }

            case 7: {
                tracker.displayCategoryWiseExpenses();
                break;
            }

            case 8: {
                cout << "\n--- DELETE TRANSACTION ---\n";
                int deleteId = getPositiveInt("Enter Transaction ID to delete: ");

                if (!tracker.hasTransaction(deleteId)) {
                    cout << "[Error] No transaction found with ID: " << deleteId << "\n";
                    break;
                }

                tracker.searchById(deleteId);

                string confirm = getNonEmptyString("Are you sure you want to delete this transaction? (y/n): ");
                if (confirm == "y" || confirm == "Y") {
                    if (tracker.deleteTransaction(deleteId)) {
                        FileManager::saveToFile(DATA_FILE, tracker);
                        cout << "[Success] Transaction #" << deleteId << " deleted successfully!\n";
                    } else {
                        cout << "[Error] Failed to delete transaction.\n";
                    }
                } else {
                    cout << "[Info] Deletion cancelled by user.\n";
                }
                break;
            }

            case 9: {
                cout << "\n[System] Saving all data before exiting...\n";
                FileManager::saveToFile(DATA_FILE, tracker);
                cout << "========================================================\n";
                cout << " Thank you for using Personal Expense Tracker. Goodbye!\n";
                cout << "========================================================\n";
                running = false;
                break;
            }

            default:
                cout << "[Error] Invalid choice! Please select 1 through 9.\n";
                break;
        }
    }

    return 0;
}
