#pragma once
#include <vector>
#include <list>
#include <string>
using namespace std;

int HashFunctionHorner(const string& s, int table_size, const int key);

struct HashFunction1
{
	int operator()(const std::string& s, int table_size) const
	{
		return HashFunctionHorner(s, table_size, table_size - 1); // ����� ������ ���� ������������, ���������� ����� <������ �������> ���� � ����� ����.
	}
};

struct HashFunction2
{
	int operator()(const std::string& s, int table_size) const
	{
		return HashFunctionHorner(s, table_size, table_size + 1);
	}
};

class HashTable {
	vector<pair<string, bool>> HT;
	int size; // ������� ��������� ��� deleted
	int size_all; // ������� ����� ���������
	const double factor = 0.75;
	struct Node
	{
		string value;
		bool state; // ���� �������� ����� state = false, ������ ������� ������� ��� ������ (deleted)
		Node(const string& value_) : value(value_), state(true) {}
	};
public:
	HashTable();
	int getBufferSize() const; // ������ ����� ���-�������
	int getFactSize() const; // ������� ��������� �� ������ ������ � ������� (��� deleted)

	vector<pair<string, bool>> getHashTable() const;
	void resize();
	void rehash();
	bool find(const string& value, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
	bool remove(const string& value, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
	bool add(const string& value, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
};

unsigned int crc32(string& str);