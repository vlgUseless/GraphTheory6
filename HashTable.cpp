#include "HashTable.h"
int HashFunctionHorner(const string& s, int table_size, const int key)
{
	int hash_result = 0;
	for (int i = 0; s[i] < s.size(); i++)
		hash_result = (key * hash_result + s[i]) % table_size;
	hash_result = (hash_result * 2 + 1) % table_size;
	return hash_result;
}

HashTable::HashTable()
{
	HT.resize(8, make_pair(string(), true)); // ��������� ������ ���-�������
	size = 0;
	size_all = 0;
}

int HashTable::getBufferSize() const { return HT.size(); }

int HashTable::getFactSize() const { return size; }

vector<pair<string, bool>> HashTable::getHashTable() const { return HT; }

void HashTable::resize()
{
	size_all = 0;
	size = 0;
	vector<pair<string, bool>> HT2(HT.size() * 2, make_pair(string(), true));
	vector<pair<string, bool>> old = HT;
	HT = HT2;
	for (const auto& node : old) {
		if (node.first != string() and node.second) {
			add(node.first);
		}
	}
}

void HashTable::rehash()
{
	size_all = 0;
	size = 0;
	vector<list<pair<string, bool>>> HT2(HT.size(), list<pair<string, bool>>(1, pair<string, bool>(string(), true)));
	for (const auto& node : HT) {
		if (node.first != string() and node.second) {
			add(node.first);
		}
	}
}

bool HashTable::find(const string& value, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(value, HT.size()); // ��������, ���������� �� ��������� �������
	int h2 = hash2(value, HT.size()); // ��������, ������������� �� "���" �� �������
	int i = 0;
	while (HT[h1].first != string() && i < HT.size())
	{
		if (HT[h1].first == value && HT[h1].second)
			return true; // ����� ������� ����
		h1 = (h1 + h2) % HT.size();
		++i; // ���� � ��� i >=  buffer_size, ������ �� ��� ������ ��������� ��� ������, ������ ��� ����� �� ������� i, ����� �� ����� �� �����������.
	}
	return false;
}

bool HashTable::remove(const string& value, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(value, HT.size());
	int h2 = hash2(value, HT.size());
	int i = 0;
	while (HT[h1].first != string() && i < HT.size())
	{
		if (HT[h1].first == value && HT[h1].second)
		{
			HT[h1].second = false;
			--size;
			return true;
		}
		h1 = (h1 + h2) % HT.size();
		++i;
	}
	return false;
}

bool HashTable::add(const string& value, const HashFunction1& hash1, const HashFunction2& hash2)
{
	if (size + 1 > int(factor * HT.size())) {
		resize();
	}
	else if (size_all > 2 * size) {
		rehash(); // ���������� �����, ��� ��� ������� ����� deleted-���������
	}
	int h1 = hash1(value, HT.size());
	int h2 = hash2(value, HT.size());
	int i = 0;
	int first_deleted = -1; // ���������� ������ ���������� (���������) �������
	while (HT[h1].first != string() && i < HT.size())
	{
		if (HT[h1].first == value && HT[h1].second)
			return false; // ����� ������� ��� ����, � ������ ��� ������ ��������� ��������
		if (!HT[h1].second && first_deleted == -1) // ������� ����� ��� ������ ��������
			first_deleted = h1;
		h1 = (h1 + h2) % HT.size();
		++i;
	}
	if (first_deleted == -1) // ���� �� ������� ����������� �����, ������� ����� Node
	{
		HT[h1] = make_pair(value, true);
		size_all++; // ��� ��� �� ��������� ���� ������, �� �������� ��������, ��� ��� ����� ������ ������
	}
	else
	{
		HT[first_deleted] = make_pair(value,true);
	}
	size++; // � � ����� ������ �� ��������� ���������� ���������
	return true;
}


unsigned int crc32(string& str) {
	unsigned int crc = 0xFFFFFFFF;

	int i = 0;
	while (i < str.size()) {
		crc ^= str[i++];
		for (int bit = 0; bit < 8; bit++) {
			if (crc & 1) {
				crc = (crc >> 1) ^ 0xEDB88320;
			}
			else {
				crc = (crc >> 1);
			}
		}
	}
	return crc ^ 0xFFFFFFFF;
}
