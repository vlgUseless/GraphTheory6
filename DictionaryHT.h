#pragma once
#include "HashTable.h"
using namespace std;

class DictionaryHT
{
	HashTable* dict;

public:
	DictionaryHT();
	~DictionaryHT();

	void add(string& word);
	void remove(string& word);
	bool find(string& word);
	void clear();
	void update();

	void print();
	void saveToFile();
};


void InputProcessing(string Action, DictionaryHT*& dict);
void MenuHT();
