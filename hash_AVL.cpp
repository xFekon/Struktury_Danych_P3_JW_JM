#include "hash_AVL.h"

int hash_AVL::hash(int key) const {
    return key % capacity; // Mo¿na u¿yæ lepszej, ale to wystarczy
}

// Konstruktor
hash_AVL::hash_AVL(int size)
    : capacity(size), table(size, nullptr) {
    for (int i = 0; i < capacity; ++i)
        table[i] = new AVL_tree();
}

// Destruktor
hash_AVL::~hash_AVL() {
    for (int i = 0; i < capacity; ++i)
        delete table[i];
}

// Wstawianie
void hash_AVL::insert(int key, int value) {
    int index = hash(key);
    table[index]->insert(key, value);
}

// Usuwanie
void hash_AVL::remove(int key) {
    int index = hash(key);
    table[index]->remove(key);
}

// Szukanie
bool hash_AVL::find(int key, int& value) {
    int index = hash(key);
    return table[index]->find(key, value);
}