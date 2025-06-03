#ifndef HASHTABLE_CHAINING_H
#define HASHTABLE_CHAINING_H

#include <vector>
#include <list>
#include <utility>
#include <cstddef>

class HashTableChaining {
public:
	
	explicit HashTableChaining(std::size_t size = 101);
	~HashTableChaining();

	
	void insert(int key, int value);

	bool remove(int key);

	bool find(int key, int &value) const;

private:
	std::size_t hashFunction(int key) const;

	std::vector<std::list<std::pair<int, int>>> table;
	std::size_t tableSize;
};

#endif 
