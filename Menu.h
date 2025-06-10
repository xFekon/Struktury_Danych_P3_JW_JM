#pragma once

#include "hash_AVL.h"
#include "HashTableChaining.h"
#include "HashTableOpenAddressing.h"
#include <memory>
#include <vector>
#include <string>

class Menu
{
public:
    void run();


private:
    void runAVLMenu();
    void runChainingMenu();
    void runOpenAddressingMenu();

    void runTest();

    std::unique_ptr<hash_AVL> avlTree;
    std::unique_ptr<HashTableChaining> chainingTable;
    std::unique_ptr<HashTableOpenAddressing> openAddressingTable;
};

