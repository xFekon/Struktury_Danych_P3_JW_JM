#pragma once

#include "AVL_tree.h"
#include "HashTableChaining.h"
#include "HashTableOpenAddressing.h"
#include <memory>

class Menu
{
public:
    void run();

private:
    void runAVLMenu();
    void runChainingMenu();
    void runOpenAddressingMenu();
    void runTest();

    std::unique_ptr<AVL_tree> avlTree;
    std::unique_ptr<HashTableChaining> chainingTable;
    std::unique_ptr<HashTableOpenAddressing> openAddressingTable;
};

