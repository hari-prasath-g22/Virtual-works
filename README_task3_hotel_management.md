# Task 3 — Hotel Management System

A simple console system for checking guests in, viewing active stays, checking out, and calculating bills from nightly room rates plus additional charges. Active stays and completed bills are stored in text files.

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -pedantic task3_hotel_management.cpp -o hotel
./hotel
```

On Windows with MinGW, build as `hotel.exe` and run that executable.

The program creates `hotel_stays.txt` and `hotel_bills.txt` in the **current working directory** when needed. Preserve those files to keep the saved records.

Source: [`task3_hotel_management.cpp`](task3_hotel_management.cpp)
