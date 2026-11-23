#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <limits>
using namespace std;

struct FileRecord {
    char fileName[50];
    int fileSize;
};

void addFile() {
    FileRecord file{};
    string name;

    cout << "Enter file name (maximum 49 characters): ";
    cin >> ws;
    getline(cin, name);

    if (name.empty() || name.size() >= sizeof(file.fileName)) {
        cout << "Invalid file name length.\n";
        return;
    }

    cout << "Enter file size in KB: ";
    cin >> file.fileSize;
    if (file.fileSize < 0) {
        cout << "File size cannot be negative.\n";
        return;
    }

    strcpy(file.fileName, name.c_str());

    ofstream outFile("filesystem.dat", ios::binary | ios::app);
    if (!outFile) {
        cout << "Unable to open storage file.\n";
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&file), sizeof(file));
    cout << "File record added successfully.\n";
}

void displayFiles() {
    ifstream inFile("filesystem.dat", ios::binary);
    if (!inFile) {
        cout << "No file records found yet.\n";
        return;
    }

    FileRecord file{};
    cout << "\n--- Stored File Records ---\n";
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&file), sizeof(file))) {
        found = true;
        cout << "File Name: " << file.fileName << '\n';
        cout << "File Size: " << file.fileSize << " KB\n";
        cout << "--------------------------\n";
    }

    if (!found) cout << "No records available.\n";
}

int main() {
    int choice;
    do {
        cout << "\nMINI FILE SYSTEM SIMULATOR\n";
        cout << "1. Add File\n2. Display Files\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addFile();
            break;
        case 2:
            displayFiles();
            break;
        case 3:
            cout << "Exiting File System Simulator...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
