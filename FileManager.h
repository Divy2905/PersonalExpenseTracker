#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

class ExpenseTracker;

class FileManager {
public:
    static bool saveToFile(const std::string& filename,
                           const ExpenseTracker& tracker);

    static bool loadFromFile(const std::string& filename,
                             ExpenseTracker& tracker);
};

#endif
