#include "DictionaryRB.h"
#include "HashTable.h"
#include "special.h"
#include <iostream>
#include <fstream>

using namespace std;

DictionaryRB::DictionaryRB() {
	dict = new RBTree();
}
DictionaryRB::~DictionaryRB() {
	delete dict;
}

void DictionaryRB::add(string& word) {
	if (find(word)) {
		cout << "The word \"" << word << "\" is already in the dictionary." << endl << endl;
	}
	else {
		dict->insert(crc32(word), word);
		cout << endl <<  "The word \"" << word << "\" has been successfully added to the dictionary." << endl << endl;
	}
}

void DictionaryRB::remove(string& word) {
	if (!find(word)) {
		cout << "There's no word \"" << word << "\" in the dictionary. Please, try again. " << endl << endl;
	}
	else {
		dict->remove(word);
		if (!find(word)) {
			cout << endl << endl << "The word \"" << word << "\" has been successfully removed from the dictionary." << endl << endl;
		}
		else {
			cout << endl << endl << "ERROR. The word \"" << word << "\" hasn't been removed from the dictionary." << endl << endl;
		}
	}
}
bool DictionaryRB::find(string& word) {
	return dict->getRoot()->search(word);
}
void DictionaryRB::clear() {
	cout << "-----Clearing the dictionary-----" << endl << endl;
	while (true) {
		string input;
		cout << "Are you sure you want to clear the whole dictionary?" << endl;
		cout << "(Yy / Nn): ";
		cin >> input;

		if (input == "Y" or input == "y") {
			dict->getRoot()->deleteTree();
			delete dict->getRoot();
			delete dict;
			dict = new RBTree();
			cout << endl << "Dictionary has been successfully cleared." << endl << endl;
			return;
		}
		else if (input == "N" or input == "n") {
			return;
		}
	}
}

void DictionaryRB::print() {
	cout << "-----Dictionary-----" << endl;
	dict->printRBTree();
	cout << endl << endl;
}

void DictionaryRB::update() {
	cout << "-----Updating the dictionary from the file-----" << endl << endl;
	string filename;
	cout << "Enter a file name without the '.txt' extension: ";
	cin >> filename;

	filename += ".txt";

	ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Couldn't find file named \"" << filename << "\"." << endl << endl;
		return;
	}

	string word;
	while (file >> word) {
		// Преобразование слова в нижний регистр
		to_lower_case(word);

		// Удаление специальных символов из слова
		remove_special_characters(word);

		// Если слово не пустое и ранее не было добавлено, добавляем его в словарь
		if (!word.empty() and !find(word)) {
			dict->insert(crc32(word), word);
		}
	}

	file.close();

	cout << endl << "The dictionary update was successful." << endl << endl;
}


void DictionaryRB::saveToFile() {
	cout << "-----Saving the dictionary to the file-----" << endl << endl;
	string filename;
	cout << "Enter a file name without the '.txt' extension: ";
	cin >> filename;

	filename += ".txt";

	string separator;
	cout << endl << "Enter a separator: ";
	cin >> separator;
	if (separator == "endl" || separator == "\\n") {
		separator = "\n"; // Используем символ новой строки в качестве разделителя
	}
	if (separator == "spb") {
		separator = " ";
	}

	fstream file(filename, ios::out);
	dict->getRoot()->saveToFileOne(file, separator);
	file.close();
	cout << endl << "Dictionary successfully saved." << endl << endl;
}



void InputProcessing(string Action, DictionaryRB*& dict) {
	if (Action == "1") {
		cout << "-----Adding the word to the dictionary-----" << endl << endl;

		string word;
		cout << "Enter a word you want to add: ";
		cin >> word;

		// Преобразование слова в нижний регистр
		to_lower_case(word);

		// Удаление специальных символов из слова
		remove_special_characters(word);
		
		if (word == "") {
			cout << "Your word consists only of special characters." << endl << endl;
			return;
		}

		string input;
		cout << endl << "Do you want to add this word to the dictionary?: " << word << endl;
		cout << "(Yy / Nn): ";
		cin >> input;

		if (input == "Y" or input == "y") {
			dict->add(word);
			return;
		}
		else if (input == "N" or input == "n") {
			return;
		}

	}
	else if (Action == "2") {
		cout << "-----Checking if the word is in the dictionary-----" << endl << endl;

		string word;
		cout << "Enter a word you want to find: ";
		cin >> word;

		// Преобразование слова в нижний регистр
		to_lower_case(word);

		// Удаление специальных символов из слова
		remove_special_characters(word);

		if (word == "") {
			cout << "Your word consists only of special characters." << endl << endl;
			return;
		}

		if (dict->find(word)) {
			cout << endl << "The word \"" << word << "\" is in the dictionary." << endl << endl;
		}
		else {
			cout << endl << "There's no word \"" << word << "\" in the dictionary." << endl << endl;
		}
		return;
	}
	else if (Action == "3") {
		cout << "-----Removing the word to the dictionary-----" << endl << endl;

		string word;
		cout << "Enter a word you want to remove: ";
		cin >> word;

		// Преобразование слова в нижний регистр
		to_lower_case(word);

		// Удаление специальных символов из слова
		remove_special_characters(word);

		if (word == "") {
			cout << "Your word consists only of special characters." << endl << endl;
			return;
		}

		string input;
		cout << endl << "Do you want to remove this word from the dictionary?: " << word << endl;
		cout << "(Yy / Nn): ";
		cin >> input;

		if (input == "Y" or input == "y") {
			dict->remove(word);
			return;
		}
		else if (input == "N" or input == "n") {
			return;
		}
	}
	else if (Action == "4") {
		dict->print();
	}
	else if (Action == "5") {
		dict->clear();
	}
	else if (Action == "6") {
		dict->update();
	}
	else if (Action == "7") {

		dict->saveToFile();

	}
}

void MenuRB() {
	cout << endl << "-----MENU-----" << endl;
	DictionaryRB* dict = new DictionaryRB();
	while (true)
	{
		cout << "Select an action:" << endl;
		cout << "(1) Add the word to the dictionary" << endl;
		cout << "(2) Check if the word is in the dictionary" << endl;
		cout << "(3) Remove the word from the dictionary" << endl;
		cout << "(4) Print current dictionary" << endl;
		cout << "(5) Clear current dictionary" << endl;
		cout << "(6) Load/update dictionary from file" << endl;
		cout << "(7) Save dictionary to the file" << endl;
		cout << "(0) Go back to the main menu " << endl << endl;

		string InputAction;
		cin >> InputAction;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (InputAction == "0")
		{
			break;
		}
		cout << endl;

		InputProcessing(InputAction, dict);
	}
}