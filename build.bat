@echo off
echo Compiling Personal Expense Tracker...
g++ -std=c++17 -Wall -Wextra main.cpp Transaction.cpp Income.cpp Expense.cpp ExpenseTracker.cpp FileManager.cpp -o ExpenseTracker.exe
if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Build completed successfully!
    echo Run the application with: .\ExpenseTracker.exe
) else (
    echo [ERROR] Compilation failed.
)
pause
