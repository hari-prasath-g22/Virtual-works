// Task 5: File-based Contact Management System
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic task5_contact_management.cpp -o contacts
// Run:     ./contacts   (Windows: contacts.exe)
// contacts.txt is created in the current working directory and persists between runs.
// The simple file format uses | between fields, so do not include | in entered data.

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Contact {
    int id{};
    std::string name;
    std::string phone;
    std::string email;
};

constexpr const char* DATA_FILE = "contacts.txt";

bool containsDelimiter(const std::string& value) {
    return value.find('|') != std::string::npos || value.find('\n') != std::string::npos;
}

std::vector<Contact> loadContacts() {
    std::vector<Contact> contacts;
    std::ifstream input(DATA_FILE);
    Contact contact;
    while (input >> contact.id && input.get() == '|') {
        if (!std::getline(input, contact.name, '|')) break;
        if (!std::getline(input, contact.phone, '|')) break;
        if (!std::getline(input, contact.email)) break;
        contacts.push_back(contact);
    }
    return contacts;
}

bool saveContacts(const std::vector<Contact>& contacts) {
    std::ofstream output(DATA_FILE, std::ios::trunc);
    if (!output) return false;
    for (const Contact& contact : contacts)
        output << contact.id << '|' << contact.name << '|'
               << contact.phone << '|' << contact.email << '\n';
    return static_cast<bool>(output);
}

std::string lowerCopy(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return text;
}

void printContact(const Contact& contact) {
    std::cout << "ID: " << contact.id << "\nName: " << contact.name
              << "\nPhone: " << contact.phone << "\nEmail: " << contact.email << "\n\n";
}

void addContact() {
    auto contacts = loadContacts();
    Contact contact;
    contact.id = 1;
    for (const Contact& saved : contacts) contact.id = std::max(contact.id, saved.id + 1);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Name: ";
    std::getline(std::cin, contact.name);
    std::cout << "Phone: ";
    std::getline(std::cin, contact.phone);
    std::cout << "Email: ";
    std::getline(std::cin, contact.email);

    if (contact.name.empty() || contact.phone.empty() || contact.email.empty() ||
        containsDelimiter(contact.name) || containsDelimiter(contact.phone) ||
        containsDelimiter(contact.email)) {
        std::cout << "All fields are required; the | character and line breaks are not allowed.\n";
        return;
    }
    contacts.push_back(contact);
    if (saveContacts(contacts)) std::cout << "Contact saved with ID " << contact.id << ".\n";
    else std::cout << "Could not save the contact. Check folder permissions.\n";
}

void viewContacts() {
    const auto contacts = loadContacts();
    if (contacts.empty()) {
        std::cout << "No contacts have been saved yet.\n";
        return;
    }
    std::cout << "\n--- Contacts ---\n";
    for (const Contact& contact : contacts) printContact(contact);
}

void searchContacts() {
    const auto contacts = loadContacts();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string query;
    std::cout << "Search by name, phone or email: ";
    std::getline(std::cin, query);
    const std::string needle = lowerCopy(query);
    bool found = false;
    for (const Contact& contact : contacts) {
        if (lowerCopy(contact.name).find(needle) != std::string::npos ||
            lowerCopy(contact.phone).find(needle) != std::string::npos ||
            lowerCopy(contact.email).find(needle) != std::string::npos) {
            printContact(contact);
            found = true;
        }
    }
    if (!found) std::cout << "No matching contacts found.\n";
}

void deleteContact() {
    auto contacts = loadContacts();
    int id;
    std::cout << "Enter contact ID to delete: ";
    if (!(std::cin >> id)) {
        std::cout << "Please enter a valid whole-number ID.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    const auto oldSize = contacts.size();
    contacts.erase(std::remove_if(contacts.begin(), contacts.end(),
                                 [id](const Contact& contact) { return contact.id == id; }),
                   contacts.end());
    if (contacts.size() == oldSize) {
        std::cout << "No contact with that ID was found.\n";
    } else if (saveContacts(contacts)) {
        std::cout << "Contact deleted.\n";
    } else {
        std::cout << "Could not update the contacts file.\n";
    }
}

int main() {
    while (true) {
        std::cout << "\n=== Contact Management ===\n"
                  << "1. Add contact\n2. View contacts\n3. Search contacts\n"
                  << "4. Delete contact\n0. Exit\n";
        int choice;
        std::cout << "Selection: ";
        if (!(std::cin >> choice)) {
            std::cout << "Please enter a whole-number menu selection.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContacts(); break;
            case 4: deleteContact(); break;
            case 0: std::cout << "Goodbye.\n"; return 0;
            default: std::cout << "Choose a number from 0 to 4.\n";
        }
    }
}
