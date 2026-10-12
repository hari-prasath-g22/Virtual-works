# Five C++ Programming Tasks

This folder contains five **independent console programs**. Each source file has its own `main()` function, so compile and run one task at a time rather than compiling all five into one executable.

## Requirements

- A C++17-compatible compiler, such as GCC (`g++`) or Clang (`clang++`).
- A terminal/command prompt opened in this folder.

## Compile and run

### Linux or macOS (GCC or Clang)

```bash
g++ -std=c++17 -Wall -Wextra -pedantic task1_calculator.cpp -o calculator
./calculator

g++ -std=c++17 -Wall -Wextra -pedantic task2_guessing_game.cpp -o guessing_game
./guessing_game

g++ -std=c++17 -Wall -Wextra -pedantic task3_hotel_management.cpp -o hotel
./hotel

g++ -std=c++17 -Wall -Wextra -pedantic task4_tic_tac_toe.cpp -o tic_tac_toe
./tic_tac_toe

g++ -std=c++17 -Wall -Wextra -pedantic task5_contact_management.cpp -o contacts
./contacts
```

To use Clang, replace `g++` with `clang++` in the commands.

### Windows (MinGW-w64)

From Command Prompt or PowerShell in this folder, use `g++` as above but run the `.exe` file, for example:

```bat
g++ -std=c++17 -Wall -Wextra -pedantic task1_calculator.cpp -o calculator.exe
calculator.exe
```

Repeat with the relevant source and executable name for each task. In PowerShell, use `./calculator.exe` to run it.

## Programs

1. **Basic Calculator** — menu-driven addition, subtraction, multiplication, and division; rejects invalid menu input and prevents division by zero.
2. **Number Guessing Game** — chooses a random integer from 1 to 100, gives high/low hints, counts guesses, and allows replay.
3. **Hotel Management System** — records active room stays, prevents assigning an occupied room, calculates a checkout bill including optional additional charges, and lists saved bills. `hotel_stays.txt` and `hotel_bills.txt` are stored in the **current working directory**.
4. **Tic-Tac-Toe** — two players alternate X and O; the program validates moves and detects wins and draws.
5. **Contact Management System** — adds, lists, searches (case-insensitive), and deletes contacts. Contact data persists in `contacts.txt` in the **current working directory**. Contact fields may contain spaces but not the `|` delimiter or line breaks.

The hotel and contact programs create their data files on first save. Keep the data files in a safe location if you want to preserve the records; deleting those files removes the saved data.
