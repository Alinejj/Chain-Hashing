#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <string>
#include "hash_chn.h"

using namespace std;

// Constructor
Table::Table() {
    used = 0;
    for (int i = 0; i < CAPACITY; i++) {
        table[i] = nullptr;  // Initialize all buckets as empty
    }
}

// Chaining insert method
void Table::insert(const RecordType& entry) {
    int index = hash(entry.key);
    Node* newNode = new Node{entry, nullptr};

    // Insert at the beginning of the linked list (head insertion)
    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        newNode->next = table[index];
        table[index] = newNode;
    }
    used++;
}

// Quadratic Probing insert method for chaining
void Table::insertQuadraticHashing(const RecordType& entry) {
    int attempt = 0;
    int index;

    do {
        index = QuadraticProbing(entry.key, attempt);
        attempt++;
    } while (attempt < CAPACITY && table[index] != nullptr);

    if (table[index] == nullptr) {
        Node* newNode = new Node{entry, nullptr};
        table[index] = newNode;
        used++;
    } else {
        cerr << "Error: Table is full.\n";
    }
}

// Double Hashing insert method for chaining
void Table::insertDoubleHashing(const RecordType& entry) {
    int attempt = 0;
    int index;

    do {
        index = DoubleHashing(entry.key, attempt);
        attempt++;
    } while (attempt < CAPACITY && table[index] != nullptr);

    if (table[index] == nullptr) {
        Node* newNode = new Node{entry, nullptr};
        table[index] = newNode;
        used++;
    } else {
        cerr << "Error: Table is full.\n";
    }
}

// Mid-Square Hashing insert method for chaining
void Table::insertMidSquareHashing(const RecordType& entry) {
    int index = MidSquareHashing(entry.key);
    Node* newNode = new Node{entry, nullptr};

    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        newNode->next = table[index];
        table[index] = newNode;
    }
    used++;
}

// Find method for chaining
void Table::find(int key, bool& found, RecordType& result) const {
    int index = hash(key);
    Node* current = table[index];
    found = false;

    while (current != nullptr) {
        if (current->record.key == key) {
            found = true;
            result = current->record;
            return;
        }
        current = current->next;
    }
}

// Erase method for chaining
void Table::erase(int key, bool& found, RecordType& del) {
    int index = hash(key);
    Node* current = table[index];
    Node* prev = nullptr;
    found = false;

    while (current != nullptr) {
        if (current->record.key == key) {
            found = true;
            del = current->record;

            if (prev == nullptr) {
                // Remove head node
                table[index] = current->next;
            } else {
                // Remove non-head node
                prev->next = current->next;
            }

            delete current;
            used--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Hashing Functions
int Table::hash(int key) const {
    return key % CAPACITY;
}

int Table::QuadraticProbing(int key, int attempt) const {
    return (hash(key) + attempt * attempt) % CAPACITY;
}

int Table::DoubleHashing(int key, int attempt) const {
    int hashFunc1 = hash(key);
    int hashFunc2 = 1 + (key % (CAPACITY - 1));
    return (hashFunc1 + attempt * hashFunc2) % CAPACITY;
}

int Table::MidSquareHashing(int key) const {
    long long squared = static_cast<long long>(key) * key;
    string sqrdSTR = to_string(squared);

    int length = sqrdSTR.length();
    int start = max(0, length / 2 - 1); 
    int end = min(start + 3, length);   
    string midStr = sqrdSTR.substr(start, end - start);
    int hashValue = stoi(midStr) % CAPACITY;

    return hashValue;
}

// Print the hash table
void Table::print() const {
    cout << "Index   Keys (Key, Data Pairs)\n";
    for (int i = 0; i < CAPACITY; i++) {
        cout << setw(5) << i << " : ";
        Node* current = table[i];

        if (current == nullptr) {
            cout << "Empty\n";
        } else {
            while (current != nullptr) {
                cout << "(" << current->record.key << ", " << current->record.data << ") -> ";
                current = current->next;
            }
            cout << "NULL\n";
        }
    }
}

// Get the size of the table
int Table::size() const {
    return used;
}

// Helper method to find the index of a key
void Table::findIndex(int key, bool& found, int& index) const {
    index = hash(key);
    Node* current = table[index];
    found = false;

    while (current != nullptr) {
        if (current->record.key == key) {
            found = true;
            return;
        }
        current = current->next;
    }
}