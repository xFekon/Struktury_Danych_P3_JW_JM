#pragma once
#include <vector>
#include "AVL_tree.h"
class hash_AVL
{
private:
    std::vector<AVL_tree*> table;
    int capacity;

    int hash(int key) const;

public:
    hash_AVL(int size = 101); // domyœlna wielkoœæ tablicy
    ~hash_AVL();

    void insert(int key, int value);
    void remove(int key);
    bool find(int key, int& value);
};

