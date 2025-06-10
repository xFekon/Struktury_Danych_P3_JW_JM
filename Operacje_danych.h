#pragma once
#include <vector>
#include <string>
#include <utility>

void generuj_dane(const std::string& nazwa_pliku, int rozmiar);

std::vector<std::vector<std::pair<int, int>>> wczytaj_dane_hash(const std::string& nazwa_pliku);
