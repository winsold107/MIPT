#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <cassert>
using namespace std;

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */
unsigned long hashFunction2(const char* s)
{
	unsigned h = FIRSTH;
	while (*s) {
		h = (h * A) ^ (s[0] * B);
		s++;
	}
	return h*2 + 1; // or return h % C;
}

unsigned long hashFunction1(const char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}

class HashTable {
public:
	HashTable(): table (8), deleted (8, false), elNum (0) {};
	bool Has(const string& key) const;
	bool Add(const string& key);
	bool Delete(const string& key);
private:
	vector<list<string>> table;
	size_t elNum;
	vector <bool> deleted;
	void rehash();
	int find_place(const string& key) const;
};

int HashTable::find_place(const string& key) const
{
	unsigned long index = hashFunction1(key.c_str()) % table.size();
	unsigned long h2 = hashFunction2(key.c_str()) % table.size();
	assert(h2 % 2 == 1);

	for (int i = 0; i < table.size(); i++)
	{
		if (!table[index].empty())
		{
			if ((table[index].front() == key)&&(deleted[index] == false))
			{
				return index;
			}
		}
		else { return -1; }
		(index += h2) %= table.size();
	}
	return -1;
}

void HashTable::rehash()
{
	vector <list<string>> old = table;
	vector<bool> oldDeleted = deleted;

	table = vector <list<string>>(old.size() * 2);
	deleted = vector<bool>(oldDeleted.size() * 2, false);
	
	for (int i = 0; i < old.size(); i++)
	{
		if (!old[i].empty() && oldDeleted[i] == false) {
			Add(old[i].front());
		}
	}
}

bool HashTable::Add (const string& key)
{
	if (elNum >= (3*table.size())/4)
	{
		rehash();
	}
	unsigned long index = hashFunction1(key.c_str()) % table.size();
	unsigned long h2 = hashFunction2(key.c_str()) % table.size();
	assert(h2 % 2 == 1);

	for (int i = 0; i < table.size(); i++) 
	{
		if (table[index].empty())
		{
			table[index].push_back(key);
			deleted[index] == false;
			elNum++;
			return true;
		}
		if (deleted[index] == true)
		{
			table[index].front() = key;
			deleted[index] = false;
			elNum++;
			return true;
		}

		if (table[index].front() == key) {
			return false;
		}
		index = (index + h2) % table.size();
	} 
	//table[index].push_back(key);
	return false;

}

bool HashTable::Has (const string& key) const
{
	return find_place(key) != -1;
}

bool HashTable::Delete(const string& key)
{
	int place = find_place(key);
	if (place == -1) {
		return false;
	}
	deleted[place] = true;
	elNum--;
	return true;
}



int main ()
{
	HashTable HASH;
	ifstream F("input.txt");
	char order;
	char key[100000];

	while (F>>order>>key) 
	{
		if (order == '+')
		{
			if (HASH.Add(key))
			{
				cout << "OK" << endl;
			}
			else
			{
				cout << "FAIL" << endl;
			}
		}
		else if (order == '?')
		{
			if (HASH.Has(key))
			{
				cout << "OK" << endl;
			}
			else
			{
				cout << "FAIL" << endl;
			}
		}
		else if (order == '-') 
		{
			if (HASH.Delete(key))
			{
				cout << "OK" << endl;
			}
			else
			{
				cout << "FAIL" << endl;
			}
		}
	}
	system("pause");
}
