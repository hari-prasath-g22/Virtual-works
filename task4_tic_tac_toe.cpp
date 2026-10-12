// Task 4: Two-player console Tic-Tac-Toe
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic task4_tic_tac_toe.cpp -o tic_tac_toe
// Run:     ./tic_tac_toe   (Windows: tic_tac_toe.exe)

#include <array>
#include <iostream>
#include <limits>

using Board = std::array<char, 9>;

void displayBoard(const Board& board) {
    std::cout << '\n';
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            const int index = row * 3 + column;
            std::cout << ' ' << board[index] << ' ';
            if (column < 2) std::cout << '|';
        }
        std::cout << '\n';
        if (row < 2) std::cout << "---+---+---\n";
    }
    std::cout << '\n';
}

bool hasWon(const Board& b, char mark) {
    constexpr int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };
    for (const auto& line : lines)
        if (b[line[0]] == mark && b[line[1]] == mark && b[line[2]] == mark)
            return true;
    return false;
}

int main() {
    Board board{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char currentPlayer = 'X';
    int moves = 0;

    std::cout << "=== Tic-Tac-Toe ===\nChoose a cell by entering its number (1-9).\n";
    while (moves < 9) {
        displayBoard(board);
        int cell;
        std::cout << "Player " << currentPlayer << ", choose a cell: ";
        if (!(std::cin >> cell)) {
            std::cout << "Please enter a whole number from 1 to 9.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (cell < 1 || cell > 9 || board[cell - 1] == 'X' || board[cell - 1] == 'O') {
            std::cout << "That cell is invalid or already occupied. Try again.\n";
            continue;
        }

        board[cell - 1] = currentPlayer;
        ++moves;
        if (hasWon(board, currentPlayer)) {
            displayBoard(board);
            std::cout << "Player " << currentPlayer << " wins!\n";
            return 0;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    displayBoard(board);
    std::cout << "The game is a draw.\n";
    return 0;
}
