#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "hash_chn.h"

void print_menu();

int main() {
    RecordType entries[] = {
        {2, 100},  {46, 200}, {139, 500}, {17, 1200}, {48, 1300}
    };

    char choice;   
    int key;
    bool found;
    int size;
    RecordType rec;

    Table chainingTable;   
    Table quadraticTable;
    Table doubleHashTable;
    Table midSquareTable;

    for (const auto& rec : entries) {
        chainingTable.insert(rec);   
        quadraticTable.insertQuadraticHashing(rec);
        doubleHashTable.insertDoubleHashing(rec);
        midSquareTable.insertMidSquareHashing(rec);   
    }

    // Print initial tables
    cout << "Initial Hash Tables with Chaining:\n";
    cout << "Chaining Table:\n";
    chainingTable.print();
    cout << "Quadratic Probing Table:\n";
    quadraticTable.print();
    cout << "Double Hashing Table:\n";
    doubleHashTable.print();
    cout << "Mid-Square Hashing Table:\n";
    midSquareTable.print();
    
    do {
        print_menu();
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl; 
        choice = toupper(choice);

        switch (choice) {
            case 'I': // Insert with chaining
                cout << "Enter key (int >= 0) for record: ";
                cin >> rec.key;
                cout << "Enter data (int) for record: ";
                cin >> rec.data;
                chainingTable.insert(rec); 
                cout << "Record was inserted in table using Chaining" << endl << endl;
                chainingTable.print();
                break;
            case 'P': // Insert with quadratic probing
                cout << "Enter key (int >= 0) for record: ";
                cin >> rec.key;
                cout << "Enter data (int) for record: ";
                cin >> rec.data;
                quadraticTable.insertQuadraticHashing(rec);
                cout << "Record was inserted in table using Quadratic Hashing" << endl << endl;
                quadraticTable.print();
                break;
            case 'H': // Insert with double hashing
                cout << "Enter key (int >= 0) for record: ";
                cin >> rec.key;
                cout << "Enter data (int) for record: ";
                cin >> rec.data;
                doubleHashTable.insertDoubleHashing(rec);
                cout << "Record was inserted in table using Double Hashing" << endl << endl;
                doubleHashTable.print();
                break;
            case 'M': // Insert with mid-square hashing
                cout << "Enter key (int >= 0) for record: ";
                cin >> rec.key;
                cout << "Enter data (int) for record: ";
                cin >> rec.data;
                midSquareTable.insertMidSquareHashing(rec);
                cout << "Record was inserted in table using Midsquare Hashing" << endl << endl;
                midSquareTable.print();
                break;
            case 'F': // Find record
                cout << "Enter key (int >= 0) to search for: ";
                cin >> key;
                chainingTable.find(key, found, rec);
                if (found) {
                    cout << "Record was found." << endl;
                    cout << "   key            = " << setw(8) 
                         << rec.key << endl;
                    cout << "   data = " << setw(8) 
                         << rec.data << endl << endl;
                }
                else
                    cout << "Record with key " << key << " not found." 
                         << endl << endl;
                break;
            case 'S': // Get size of the table
                size = chainingTable.size();
                cout << "There are " << size << " records in the table." 
                     << endl;
                cout << "There are " << (CAPACITY - size) 
                     << " empty slots left in the table." << endl << endl;
                break;
            case 'D': // Delete a record
                cout << "Enter key (int >= 0) to delete: ";
                cin >> key;
                chainingTable.erase(key, found, rec);
                if (found) {
                    cout << "Record with key " << key << " was deleted" << endl;
                } else {
                    cout << "Record with key " << key << " was not found" << endl;
                }
                chainingTable.print();
                break;
            case 'Q': // Quit program
                cout << "Test program ended." << endl;
                break;
            default: 
                cout << choice << " is invalid." << endl;
        }
    } while ((choice != 'Q'));

    return EXIT_SUCCESS;
}

void print_menu() {
    cout << endl;
    cout << "The following choices are available: " << endl;
    cout << " I   Insert a new record using Chaining" << endl;
    cout << " P   Insert a new record using Quadratic Probing" << endl;
    cout << " H   Insert a new record using Double Hashing" << endl;
    cout << " M   Insert a new record using Mid-Square Hashing" << endl;
    cout << " F   Find a record" << endl;
    cout << " S   Get the number of records" << endl;
    cout << " D   Delete a record" << endl;
    cout << " Q   Quit this test program" << endl << endl;
}
