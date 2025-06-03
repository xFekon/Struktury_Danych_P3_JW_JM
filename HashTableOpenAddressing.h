#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <vector>
#include <optional>
#include <cstddef>
#include <stdexcept>

class HashTableOpenAddressing {
public:
	explicit HashTableOpenAddressing(std::size_t size = 101);
	~HashTableOpenAddressing();

	void insert(int key, int value);

	bool remove(int key);

	std::optional<int> find(int key) const;

private:
	enum State { EMPTY, OCCUPIED, DELETED };

	struct Entry {
		int key;
		int value;
		State state;
		Entry() : key(0), value(0), state(EMPTY) {}
	};

	std::size_t hashFunction(int key) const;

	std::size_t probe(std::size_t hash, std::size_t i) const;

	std::vector<Entry> table;
	std::size_t tableSize;
};

#endif 
