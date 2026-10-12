# Task 5 — Contact Management System

A file-based console application that adds, lists, searches (case-insensitive), and deletes contacts.

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra -pedantic task5_contact_management.cpp -o contacts
./contacts
```

On Windows with MinGW, build as `contacts.exe` and run that executable.

Contact records persist in `contacts.txt` in the **current working directory**. Contact fields may contain spaces; the `|` delimiter and line breaks are not supported in fields.

Source: [`task5_contact_management.cpp`](task5_contact_management.cpp)
