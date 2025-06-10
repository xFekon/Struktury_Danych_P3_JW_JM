#include "Menu.h"
#include "Operacje_danych.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <random>

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
    avlTree = std::make_unique<hash_AVL>(101);  
    int option, key, value;
    do {
        std::cout << "\n-- HASH AVL MENU --\n1. Dodaj\n2. Usun\n3. Znajdz\n0. Powrot\nWybor: ";
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
        std::cout << "\n-- CHAINING MENU --\n";
        std::cout << "1. Dodaj\n2. Usun\n3. Znajdz\n4. Wyswietl\n0. Powrot\nWybor: ";
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
        case 4:
            chainingTable->display();
            break;
        }
    } while (option != 0);
}

void Menu::runOpenAddressingMenu() {
    openAddressingTable = std::make_unique<HashTableOpenAddressing>(101);
    int option, key, value;
    do {
        std::cout << "\n-- OPEN ADDRESSING MENU --\n";
        std::cout << "1. Dodaj\n2. Usun\n3. Znajdz\n4. Wyswietl\n0. Powrot\nWybor: ";
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
        case 4:
            openAddressingTable->display();
            break;
        }
    } while (option != 0);
}



void Menu::runTest() {
    using namespace std::chrono;
    std::vector<int> rozmiary = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
    std::string operacja = "chaining_remove"; 
    std::ofstream csv("wyniki_" + operacja + ".csv");
    csv << "rozmiar,czas_usredniony_ns\n";

    for (int rozmiar : rozmiary) {
        std::string plik_danych = "dane_" + std::to_string(rozmiar) + ".txt";
        auto zbiory = wczytaj_dane_hash(plik_danych);
        long long suma_czasu = 0;

        for (const auto& zbior : zbiory) {

            // Dostosuj do struktury:
            int tablica_rozmiar = static_cast<int>(zbior.size() / 0.4);  // load factor 0.4
            HashTableChaining tabela(tablica_rozmiar);

            // Wype³nij strukturê oryginalnymi danymi
            for (const auto& [klucz, wartosc] : zbior) {
                tabela.insert(klucz, wartosc);
            }

            for (int i = 0; i < 100; ++i) {
                
                std::mt19937 gen(std::random_device{}());
                std::uniform_int_distribution<> dist(1, rozmiar*10);
                
				int klucz = dist(gen); 
                int wartosc = dist(gen); 

                auto start = high_resolution_clock::now();
                
                    //tabela.remove(klucz);
                    tabela.insert(klucz, wartosc);
                
                auto end = high_resolution_clock::now();

                auto czas = duration_cast<nanoseconds>(end - start).count();
                suma_czasu += czas;

                tabela.remove(klucz);
                //tabela.insert(klucz, wartosc);
            }
        }

        double sredni_czas = static_cast<double>(suma_czasu) / (zbiory.size() * 100);
        csv << rozmiar << "," << sredni_czas << "\n";
        std::cout << "Zakonczono: " << rozmiar << " - œredni czas: " << sredni_czas << " ns\n";
    }

    csv.close();

    //Manualnie zmienie dla testów

    //dla openaddresing pe³nosc ustawiæ na 0,5 (wyk³ad zwiêkszenie tablicy przy 0,6-0,8)
    //dla chaining pe³noœæ ustawic na 0,8 (wyk³ad zwiêkszenie tablicy przy soft 1-3)
}