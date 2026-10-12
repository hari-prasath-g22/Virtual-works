// Task 3: Simple Hotel Management and Billing System
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic task3_hotel_management.cpp -o hotel
// Run:     ./hotel   (Windows: hotel.exe)
// Data files are created in the current working directory:
//   hotel_stays.txt = active stays; hotel_bills.txt = completed bills.

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Stay {
    int roomNumber{};
    std::string guestName;
    int nights{};
    double nightlyRate{};
};

constexpr const char* STAYS_FILE = "hotel_stays.txt";
constexpr const char* BILLS_FILE = "hotel_bills.txt";

// Keep the simple pipe-delimited file format unambiguous.
bool hasDelimiter(const std::string& text) {
    return text.find('|') != std::string::npos;
}

std::vector<Stay> loadStays() {
    std::vector<Stay> stays;
    std::ifstream input(STAYS_FILE);
    Stay stay;
    while (input >> stay.roomNumber && input.get() == '|') {
        if (!std::getline(input, stay.guestName, '|')) break;
        if (!(input >> stay.nights) || input.get() != '|') break;
        if (!(input >> stay.nightlyRate)) break;
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        stays.push_back(stay);
    }
    return stays;
}

bool saveStays(const std::vector<Stay>& stays) {
    std::ofstream output(STAYS_FILE, std::ios::trunc);
    if (!output) return false;
    output << std::fixed << std::setprecision(2);
    for (const Stay& stay : stays)
        output << stay.roomNumber << '|' << stay.guestName << '|'
               << stay.nights << '|' << stay.nightlyRate << '\n';
    return static_cast<bool>(output);
}

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) return value;
        std::cout << "Please enter a whole number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readNonnegativeAmount(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0.0) return value;
        std::cout << "Enter a valid non-negative amount.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void checkIn() {
    auto stays = loadStays();
    Stay newStay;
    newStay.roomNumber = readInt("Room number: ");
    if (newStay.roomNumber <= 0) {
        std::cout << "Room number must be positive.\n";
        return;
    }
    for (const Stay& stay : stays) {
        if (stay.roomNumber == newStay.roomNumber) {
            std::cout << "That room already has an active stay.\n";
            return;
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Guest name (do not use the | character): ";
    std::getline(std::cin, newStay.guestName);
    if (newStay.guestName.empty() || hasDelimiter(newStay.guestName)) {
        std::cout << "Guest name is empty or contains an unsupported character.\n";
        return;
    }
    newStay.nights = readInt("Number of nights: ");
    if (newStay.nights <= 0) {
        std::cout << "Number of nights must be positive.\n";
        return;
    }
    newStay.nightlyRate = readNonnegativeAmount("Rate per night: ");

    stays.push_back(newStay);
    if (saveStays(stays)) std::cout << "Guest checked in and stay saved.\n";
    else std::cout << "Could not save the stay. Check folder permissions.\n";
}

void showActiveStays() {
    const auto stays = loadStays();
    if (stays.empty()) {
        std::cout << "There are no active stays.\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(2)
              << "\nActive stays\nRoom   Guest                     Nights   Rate/night\n";
    for (const Stay& stay : stays)
        std::cout << std::left << std::setw(7) << stay.roomNumber
                  << std::setw(26) << stay.guestName << std::setw(9) << stay.nights
                  << '$' << stay.nightlyRate << '\n';
}

void checkOut() {
    auto stays = loadStays();
    const int room = readInt("Room number to check out: ");
    for (std::size_t i = 0; i < stays.size(); ++i) {
        if (stays[i].roomNumber != room) continue;

        const double roomCharge = stays[i].nights * stays[i].nightlyRate;
        const double extras = readNonnegativeAmount("Additional charges (meals, etc.; enter 0 if none): ");
        const double total = roomCharge + extras;

        // Append a completed bill, then remove the stay from the active-stay file.
        std::ofstream bills(BILLS_FILE, std::ios::app);
        if (!bills) {
            std::cout << "Could not write the bill; the stay remains active.\n";
            return;
        }
        bills << std::fixed << std::setprecision(2)
              << "Room " << stays[i].roomNumber << " | Guest: " << stays[i].guestName
              << " | Nights: " << stays[i].nights << " | Room: $" << roomCharge
              << " | Extras: $" << extras << " | Total: $" << total << '\n';
        bills.close();

        std::cout << std::fixed << std::setprecision(2)
                  << "\n--- Checkout Bill ---\nGuest: " << stays[i].guestName
                  << "\nRoom: " << stays[i].roomNumber
                  << "\nRoom charge: $" << roomCharge
                  << "\nAdditional charges: $" << extras
                  << "\nTotal due: $" << total << '\n';

        stays.erase(stays.begin() + static_cast<std::ptrdiff_t>(i));
        if (saveStays(stays)) std::cout << "Checkout completed; bill saved to " << BILLS_FILE << ".\n";
        else std::cout << "Warning: bill was written, but active-stay data could not be updated.\n";
        return;
    }
    std::cout << "No active stay found for that room.\n";
}

void showRecentBills() {
    std::ifstream bills(BILLS_FILE);
    if (!bills) {
        std::cout << "No completed bills have been saved yet.\n";
        return;
    }
    std::cout << "\n--- Saved Bills ---\n";
    std::string line;
    bool found = false;
    while (std::getline(bills, line)) {
        if (!line.empty()) { std::cout << line << '\n'; found = true; }
    }
    if (!found) std::cout << "No completed bills have been saved yet.\n";
}

int main() {
    while (true) {
        std::cout << "\n=== Hotel Management ===\n"
                  << "1. Check in guest\n2. View active stays\n"
                  << "3. Check out and create bill\n4. View saved bills\n0. Exit\n";
        const int choice = readInt("Selection: ");
        switch (choice) {
            case 1: checkIn(); break;
            case 2: showActiveStays(); break;
            case 3: checkOut(); break;
            case 4: showRecentBills(); break;
            case 0: std::cout << "Goodbye.\n"; return 0;
            default: std::cout << "Choose a number from 0 to 4.\n";
        }
    }
}
