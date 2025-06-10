#include "Operacje_danych.h"

#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>


// Generuje dane testowe do pliku.
// Ka¿dy plik zawiera 10 zestawów danych oddzielonych "---", ka¿dy zestaw ma 'rozmiar' par <klucz, wartoœæ>.
void generuj_dane(const std::string& nazwa_pliku, int rozmiar) {
    std::ofstream plik(nazwa_pliku);
    if (!plik.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku: " << nazwa_pliku << "\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> klucz_losowy(1, 10 * rozmiar);
    std::uniform_int_distribution<> wartosc_losowy(1, 1'000'000);

    for (int zestaw = 0; zestaw < 10; ++zestaw) {
        for (int i = 0; i < rozmiar; ++i) {
            int klucz = klucz_losowy(gen);
            int wartosc = wartosc_losowy(gen);
            plik << klucz << " " << wartosc << "\n";
        }
        plik << "---\n";
    }

    plik.close();
    std::cout << "Wygenerowano dane do pliku: " << nazwa_pliku << "\n";
}

std::vector<std::vector<std::pair<int, int>>> wczytaj_dane_hash(const std::string& nazwa_pliku) {
    std::ifstream plik(nazwa_pliku);
    std::vector<std::vector<std::pair<int, int>>> zbiory;
    std::string linia;
    std::vector<std::pair<int, int>> aktualny_zbior;

    while (getline(plik, linia)) {
        if (linia == "---") {
            if (!aktualny_zbior.empty()) {
                zbiory.push_back(aktualny_zbior);
                aktualny_zbior.clear();
            }
        }
        else {
            std::stringstream ss(linia);
            int klucz, wartosc;
            ss >> klucz >> wartosc;
            aktualny_zbior.emplace_back(klucz, wartosc);
        }
    }

    if (!aktualny_zbior.empty()) {
        zbiory.push_back(aktualny_zbior);
    }

    return zbiory;
}