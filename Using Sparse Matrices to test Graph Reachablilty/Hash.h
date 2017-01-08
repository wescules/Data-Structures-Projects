#pragma once
#ifndef HASH
#define HASH

//similar code from lab

const int TABLE_SIZE = 10000;

class HashEntry {
private:
	int key;
	string value;
public:
	HashEntry(int key, string value) {
		this->key = key;
		this->value = value;
	}

	int getKey() {
		return key;
	}

	string getValue() {
		return value;
	}
};



class HashMap {
private:
	HashEntry **table;
public:
	HashMap();
	string get(int key);
	void insert(int key, string value);
};


//initializes hashmap to a null state
HashMap::HashMap() {
	this->table = new HashEntry*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = NULL;
}

// gets value of inputted key
string HashMap::get(int key) {
	int hash = (key % TABLE_SIZE);
	while (table[hash] != NULL && table[hash]->getKey() != key)
		hash = (hash + 1) % TABLE_SIZE;
	//if not found dont print anything
	if (table[hash] == NULL)
		return "";
	//printvalue if found
	else
		return table[hash]->getValue();
}

//inserts key value pairs into table
void HashMap::insert(int key, string value) {
	int hash = (key % TABLE_SIZE);
	while (table[hash] != NULL && table[hash]->getKey() != key)
		hash = (hash + 1) % TABLE_SIZE;
	if (table[hash] != NULL)
		delete table[hash];
	table[hash] = new HashEntry(key, value);
}

#endif