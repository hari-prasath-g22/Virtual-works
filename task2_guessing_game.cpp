// Task 2: Number Guessing Game
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic task2_guessing_game.cpp -o guessing_game
// Run:     ./guessing_game   (Windows: guessing_game.exe)

#include <iostream>
#include <limits>
#include <random>

int main() {
    // Seed once from the system's random-device source and reuse the generator.
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> distribution(1, 100);

    std::cout << "=== Number Guessing Game ===\n"
              << "I have chosen a number from 1 to 100.\n";

    bool playAgain = true;
    while (playAgain) {
        const int answer = distribution(engine);
        int attempts = 0;
        int guess = 0;

        while (guess != answer) {
            std::cout << "Your guess: ";
            if (!(std::cin >> guess)) {
                std::cout << "Please enter a whole number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            ++attempts;
            if (guess < 1 || guess > 100) {
                std::cout << "Keep your guess between 1 and 100.\n";
            } else if (guess < answer) {
                std::cout << "Too Low! Try again.\n";
            } else if (guess > answer) {
                std::cout << "Too High! Try again.\n";
            } else {
                std::cout << "Correct! You found it in " << attempts
                          << (attempts == 1 ? " guess.\n" : " guesses.\n");
            }
        }

        char response;
        std::cout << "Play again? (y/n): ";
        std::cin >> response;
        playAgain = (response == 'y' || response == 'Y');
    }
    std::cout << "Thanks for playing.\n";
    return 0;
}
