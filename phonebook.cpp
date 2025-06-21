#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Contact {
    string name;
    string phone;
};

void addContact() {
    Contact c;
    cin.ignore();  
    cout << "Enter name: ";
    getline(cin, c.name);
    cout << "Enter phone number: ";
    getline(cin, c.phone);

    ofstream outFile;
    outFile.open("phonebook.txt", ios::app);
    if (!outFile) {
        cout << "❌ Error: Could not open file for writing.\n";
        return;
    }

    outFile << c.name << "," << c.phone << endl;
    outFile.close();
    cout << "✅ Contact added successfully.\n";
}

void viewContacts() {
    ifstream inFile("phonebook.txt");
    if (!inFile) {
        cout << "❌ No contacts found.\n";
        return;
    }

    cout << "\n📒 Contact List:\n";
    cout << left << setw(20) << "Name" << setw(15) << "Phone" << endl;
    cout << "----------------------------------\n";

    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            string phone = line.substr(pos + 1);
            cout << left << setw(20) << name << setw(15) << phone << endl;
        }
    }
    inFile.close();
}

void searchContact() {
    cin.ignore();
    cout << "Enter name to search: ";
    string searchName;
    getline(cin, searchName);

    ifstream inFile("phonebook.txt");
    if (!inFile) {
        cout << "❌ No contacts found.\n";
        return;
    }

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            string phone = line.substr(pos + 1);
            if (name.find(searchName) != string::npos) {
                cout << "✅ Found: " << name << " - " << phone << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "❌ Contact not found.\n";
    }
    inFile.close();
}

int main() {
    int choice;
    while (true) {
        cout << "\n=== PHONEBOOK MENU ===\n";
        cout << "1. Add Contact\n";
        cout << "2. View All Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: cout << "👋 Exiting program.\n"; return 0;
            default: cout << "❌ Invalid choice. Try again.\n";
        }
    }
}
