#include "HashTableChaining.h"

HashTableChaining::HashTableChaining(std::size_t size)
	: tableSize(size)
{
	table.resize(tableSize);
}

HashTableChaining::~HashTableChaining() {
	
}

std::size_t HashTableChaining::hashFunction(int key) const {
	// zak³adamy, ¿e key >= 0 lub pozwalamy na rzutowanie ujemnych liczb na size_t
	return static_cast<std::size_t>(key) % tableSize;
}

void HashTableChaining::insert(int key, int value) {
	std::size_t idx = hashFunction(key);
	
	for (auto &kv : table[idx]) {
		if (kv.first == key) {
			kv.second = value;
			return;
		}
	}

	table[idx].emplace_back(key, value);
}

bool HashTableChaining::remove(int key) {
	std::size_t idx = hashFunction(key);
	auto &chain = table[idx];
	for (auto it = chain.begin(); it != chain.end(); ++it) {
		if (it->first == key) {
			chain.erase(it);
			return true;
		}
	}
	return false;
}

bool HashTableChaining::find(int key, int &value) const {
	std::size_t idx = hashFunction(key);
	for (const auto &kv : table[idx]) {
		if (kv.first == key) {
			value = kv.second;
			return true;
		}
	}
	return false;
}
