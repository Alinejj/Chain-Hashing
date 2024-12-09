#ifndef HASH_CH_H
#define HASH_CH_H

typedef int ItemType;
const int CAPACITY = 31;

struct RecordType {
    int key;
    ItemType data;
};

// Node for the linked list in each bucket
struct Node {
    RecordType record;
    Node* next;
};

class Table {
public:
    Table(); // Constructor

    // Insert methods
    void insert(const RecordType& entry); // Chaining
    void insertQuadraticHashing(const RecordType& entry);
    void insertDoubleHashing(const RecordType& entry);
    void insertMidSquareHashing(const RecordType& entry);

    // Find, erase, and print methods
    void find(int key, bool& found, RecordType& result) const;
    void erase(int key, bool& found, RecordType& del);
    int size() const;
    void print() const;

private:
    // Helper methods
    int hash(int key) const;
    void findIndex(int key, bool& found, int& index) const;

    // Collision methods
    int QuadraticProbing(int key, int attempt) const;
    int DoubleHashing(int key, int attempt) const;
    int MidSquareHashing(int key) const;

    // Data members
    Node* table[CAPACITY]; // Chaining with linked list
    int used; // Keeps track of used slots in the table
};

#endif
