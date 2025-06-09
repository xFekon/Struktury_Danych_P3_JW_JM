#include "Menu.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

void Menu::run() {
    int choice;
    do {
        std::cout << "\n=== MENU GLOWNE ===\n";
        std::cout << "1. AVL Tree\n";
        std::cout << "2. Hash Table (Chaining)\n";
        std::cout << "3. Hash Table (Open Addressing)\n";
		std::cout << "4. Wykonaj test czasowy\n";
        std::cout << "0. Wyjscie\n";
        std::cout << "Wybor: ";
        std::cin >> choice;

        switch (choice) {
        case 1: runAVLMenu(); break;
        case 2: runChainingMenu(); break;
        case 3: runOpenAddressingMenu(); break;
        case 4: runTest(); break;
        case 0: break;
        default: std::cout << "Nieprawidlowy wybor!\n";
        }
    } while (choice != 0);
}

void Menu::runAVLMenu() {
    avlTree = std::make_unique<AVL_tree>();
    int option, key, value;
    do {
        std::cout << "\n-- AVL MENU --\n1. Dodaj\n2. Usun\n3. Znajdz\n0. Powrot\nWybor: ";
        std::cin >> option;

        switch (option) {
        case 1:
            std::cout << "Podaj klucz i wartosc: ";
            std::cin >> key >> value;
            avlTree->insert(key, value);
            break;
        case 2:
            std::cout << "Podaj klucz: ";
            std::cin >> key;
            avlTree->remove(key);
            break;
        case 3:
            std::cout << "Podaj klucz: ";
            std::cin >> key;
            if (avlTree->find(key, value))
                std::cout << "Znaleziono: " << value << "\n";
            else
                std::cout << "Nie znaleziono\n";
            break;
        }
    } while (option != 0);
}

void Menu::runChainingMenu() {
    chainingTable = std::make_unique<HashTableChaining>(101);
    int option, key, value;
    do {
        std::cout << "\n-- CHAINING MENU --\n1. Dodaj\n2. Usun\n3. Znajdz\n0. Powrot\nWybor: ";
        std::cin >> option;

        switch (option) {
        case 1:
            std::cout << "Podaj klucz i wartosc: ";
            std::cin >> key >> value;
            chainingTable->insert(key, value);
            break;
        case 2:
            std::cout << "Podaj klucz: ";
            std::cin >> key;
            chainingTable->remove(key);
            break;
        case 3:
            std::cout << "Podaj klucz: ";
            std::cin >> key;
            if (chainingTable->find(key, value))
                std::cout << "Znaleziono: " << value << "\n";
            else
                std::cout << "Nie znaleziono\n";
            break;
        }
    } while (option != 0);
}

void Menu::runOpenAddressingMenu() {
    openAddressingTable = std::make_unique<HashTableOpenAddressing>(101);
    int option, key, value;
    do {
        std::cout << "\n-- OPEN ADDRESSING MENU --\n1. Dodaj\n2. Usun\n3. Znajdz\n0. Powrot\nWybor: ";
        std::cin >> option;

        switch (option) {
        case 1:
            std::cout << "Podaj klucz i wartosc: ";
            std::cin >> key >> value;
            openAddressingTable->insert(key, value);
            break;
        case 2:
            std::cout << "Podaj klucz: ";
            std::cin >> key;
            openAddressingTable->remove(key);
            break;
        case 3:
            std::cout << "Podaj klucz: ";
            std::cin >> key;
            {
                auto result = openAddressingTable->find(key);
                if (result.has_value())
                    std::cout << "Znaleziono: " << result.value() << "\n";
                else
                    std::cout << "Nie znaleziono\n";
            }
            break;
        }
    } while (option != 0);
}


void Menu::runTest() {
    std::cout << "\n=== TEST CZASOWY ===\n";

    int testSize;
    std::cout << "Podaj liczbe elementow do testu (np. 5000): ";
    std::cin >> testSize;

    AVL_tree testTree;
    
    

    auto start = std::chrono::high_resolution_clock::now();

    

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Czas wykonania operacji insert() dla " << testSize << " elementow: "
        << duration.count() << " mikrosekund\n";

    //Manualnie zmienie dla testów
}