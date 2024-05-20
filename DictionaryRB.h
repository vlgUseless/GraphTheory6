#pragma once
#include "RBTree.h"
class DictionaryRB
{
	RBTree* dict;
public:
	DictionaryRB();
	~DictionaryRB();

	void add(string& word);
	void remove(string& word);
	bool find(string& word);
	void clear();
	void update();

	void print();
	void saveToFile();
};


void InputProcessing(string Action, DictionaryRB*& dict);
void MenuRB();