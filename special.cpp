#include "special.h"
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

// Функция для удаления специальных символов из строки
void remove_special_characters(string& str) {
	str.erase(remove_if(str.begin(), str.end(), [](unsigned char c) {
		return !isalpha(c);  // Удаляем все символы, которые не являются буквами
		}), str.end());
}

// Функция для преобразования строки в нижний регистр
void to_lower_case(string& str) {
	transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
		return tolower(c);  // Преобразуем символ в нижний регистр
		});
}