#include "HashTableOpenAddressing.h"
#include <limits>
#include <iostream>

HashTableOpenAddressing::HashTableOpenAddressing(std::size_t size)
	: tableSize(size)
{
	table.resize(tableSize);
}

HashTableOpenAddressing::~HashTableOpenAddressing() {
}

std::size_t HashTableOpenAddressing::hashFunction(int key) const {
	return static_cast<std::size_t>(key) % tableSize;
}

std::size_t HashTableOpenAddressing::probe(std::size_t hash, std::size_t i) const {
	return (hash + i) % tableSize;  
}

void HashTableOpenAddressing::insert(int key, int value) {
	std::size_t h = hashFunction(key);
	std::size_t firstDeletedIndex = tableSize; 

	for (std::size_t i = 0; i < tableSize; ++i) {
		std::size_t idx = probe(h, i);
		if (table[idx].state == OCCUPIED) {
			if (table[idx].key == key) {
				table[idx].value = value;
				return;
			}
		}
		else if (table[idx].state == DELETED) {
			if (firstDeletedIndex == tableSize) {
				firstDeletedIndex = idx;
			}
		}
		else { // EMPTY
			// Jeœli wczeœniej widzieliœmy DELETED, wstaw tam; w przeciwnym razie – w to EMPTY
			std::size_t target = (firstDeletedIndex != tableSize) ? firstDeletedIndex : idx;
			table[target].key = key;
			table[target].value = value;
			table[target].state = OCCUPIED;
			return;
		}
	}

	if (firstDeletedIndex != tableSize) {
		table[firstDeletedIndex].key = key;
		table[firstDeletedIndex].value = value;
		table[firstDeletedIndex].state = OCCUPIED;
		return;
	}

	throw std::overflow_error("Hash table is full");
}

bool HashTableOpenAddressing::remove(int key) {
	std::size_t h = hashFunction(key);

	for (std::size_t i = 0; i < tableSize; ++i) {
		std::size_t idx = probe(h, i);
		if (table[idx].state == EMPTY) {
			return false;
		}
		if (table[idx].state == OCCUPIED && table[idx].key == key) {
			table[idx].state = DELETED;
			return true;
		}
	}
	return false;
}



std::optional<int> HashTableOpenAddressing::find(int key) const {
	std::size_t h = hashFunction(key);

	for (std::size_t i = 0; i < tableSize; ++i) {
		std::size_t idx = probe(h, i);
		if (table[idx].state == EMPTY) {
			return std::nullopt;
		}
		if (table[idx].state == OCCUPIED && table[idx].key == key) {
			return table[idx].value;
		}
	}
	return std::nullopt;
}

void HashTableOpenAddressing::display() const {
	for (std::size_t i = 0; i < tableSize; ++i) {
		const auto& entry = table[i];
		std::cout << i << ": ";
		if (entry.state == EMPTY) {
			std::cout << "[EMPTY]";
		}
		else if (entry.state == DELETED) {
			std::cout << "[DELETED]";
		}
		else {
			std::cout << "(" << entry.key << ", " << entry.value << ")";
		}
		std::cout << "\n";
	}
}
