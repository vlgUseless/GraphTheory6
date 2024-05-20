#include "special.h"
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

// ������� ��� �������� ����������� �������� �� ������
void remove_special_characters(string& str) {
	str.erase(remove_if(str.begin(), str.end(), [](unsigned char c) {
		return !isalpha(c);  // ������� ��� �������, ������� �� �������� �������
		}), str.end());
}

// ������� ��� �������������� ������ � ������ �������
void to_lower_case(string& str) {
	transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
		return tolower(c);  // ����������� ������ � ������ �������
		});
}