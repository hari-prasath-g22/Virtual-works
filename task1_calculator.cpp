// Task 1: Menu-driven basic calculator
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic task1_calculator.cpp -o calculator
// Run:     ./calculator   (Windows: calculator.exe)

#include <iostream>
#include <limits>

// Read a number while recovering cleanly from invalid input.
double readNumber(const char* prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) return value;
        std::cout << "Please enter a valid number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    std::cout << "=== Basic Calculator ===\n";
    while (true) {
        std::cout << "\nChoose an operation:\n"
                  << "1. Addition (+)\n2. Subtraction (-)\n"
                  << "3. Multiplication (*)\n4. Division (/)\n0. Exit\n";

        int choice;
        std::cout << "Selection: ";
        if (!(std::cin >> choice)) {
            std::cout << "Please enter a whole-number menu selection.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (choice == 0) {
            std::cout << "Goodbye.\n";
            break;
        }
        if (choice < 1 || choice > 4) {
            std::cout << "Invalid selection. Choose 0 through 4.\n";
            continue;
        }

        const double first = readNumber("First number: ");
        const double second = readNumber("Second number: ");
        double result = 0.0;

        switch (choice) {
            case 1: result = first + second; break;
            case 2: result = first - second; break;
            case 3: result = first * second; break;
            case 4:
                if (second == 0.0) {
                    std::cout << "Error: division by zero is undefined.\n";
                    continue;
                }
                result = first / second;
                break;
        }
        std::cout << "Result: " << result << '\n';
    }
    return 0;
}
