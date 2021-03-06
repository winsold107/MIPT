#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
//#include "Hufman.h"
using namespace std;

static void copyStream(istream& input, ostream& output)
{
	char value;
	while (!input.eof())
	{
		input >> value;
		output << value;
	}
}

/*void Encode(istream& original, ostream& compressed)
{
	{
		int amount[256];
		for (auto &i : amount)
			i = 0;
		{
			while (!original.eof())
			{
				unsigned char ch;
				original.read((char *)&ch, sizeof(ch));
				++amount[ch];
			}
		}
		multimap<int, int > sortedamount;
		struct Node
		{
			char ch;
			int parent;
			int zero;
			int one;
			bool branch;
		};
		vector<Node> tree;
		map<char, int> charMap;
		for (size_t i = 0; i < 256; ++i)
		{
			if (amount[i] > 0)
			{
				tree.push_back(Node{ (char)i, -1, -1, -1, false });
				charMap[i] = tree.size() - 1;
				sortedamount.insert(make_pair(amount[i], tree.size() - 1));
			}
		}
		while (sortedamount.size() > 1)
		{
			int w0 = begin(sortedamount)->first;
			int n0 = begin(sortedamount)->second;
			sortedamount.erase(begin(sortedamount));
			int w1 = begin(sortedamount)->first;
			int n1 = begin(sortedamount)->second;
			sortedamount.erase(begin(sortedamount));
			tree.push_back(Node{ '\0', -1, n0, n1, false });
			tree[n0].parent = tree.size() - 1;
			tree[n0].branch = false;
			tree[n1].parent = tree.size() - 1;
			tree[n1].branch = true;
			sortedamount.insert(make_pair(w0 + w1, tree.size() - 1));
		}
		vector < int > data;
		{
			//ifstream f("../off.txt");
			while (!original.eof())
			{
				unsigned char ch;
				original.read((char *)&ch, sizeof(ch));
				auto n = tree[charMap[ch]];
				vector<int> compressedChar;
				while (n.parent != -1)
				{
					compressedChar.push_back(n.branch);
					n = tree[n.parent];
				}
				data.insert(end(data), compressedChar.rbegin(), compressedChar.rend());
			}
		}
		//ofstream f("../dick in the ass.txt");
		int treeSize = tree.size();
		compressed.write((char *)&treeSize, sizeof(treeSize));
		for (auto i : tree)
			compressed.write((char *)&i, sizeof(i));
		for (size_t i = 0; i <= data.size() / 8; ++i)
		{
			unsigned char ch = 0;
			for (int j = 0; j < 8; ++j)
				if (data[i * 8 + j])
					ch |= (1 << j);
			compressed.write((char *)&ch, sizeof(ch));
		}

		copyStream(original, compressed);
	}
}

void Decode(istream& compressed, ostream& original)
{
		struct Node
		{
			char ch;
			int parent;
			int zero;
			int one;
			bool branch;
		};
		vector<Node> tree;

		//ifstream f("../lesson48.huff");
		int treeSize;
		compressed.read((char *)&treeSize, sizeof(treeSize));
		for (int i = 0; i < treeSize; ++i)
		{
			Node n;
			compressed.read((char *)&n, sizeof(n));
			tree.push_back(n);
		}
		vector<int> data;
		while (!compressed.eof())
		{
			unsigned char ch;
			compressed.read((char *)&ch, sizeof(ch));
			for (int i = 0; i < 8; ++i)
				data.push_back((ch & (1 << i)) != 0);
		}
		auto n = tree.size() - 1;
		for (auto i : data)
		{
			if (i)
				n = tree[n].one;
			else
				n = tree[n].zero;
			if (tree[n].one == -1)
			{
				cout << tree[n].ch;
				n = tree.size() - 1;
			}
		}

	copyStream(compressed, original);
}*/

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Node
{
public:
	int a;
	char c;
	Node *left, *right;

	Node() { left = right = nullptr; }

	Node(Node *L, Node *R)
	{
		left = L;
		right = R;
		a = L->a + R->a;
	}
};

list<Node*> t;

struct MyCompare
{
	bool operator()(const Node* l, const Node* r) const { return l->a < r->a; }
};


vector<int> code;
map<char, vector<int> > table;

void BuildTable(Node *root)
{
	if (root->left != nullptr)
	{
		code.push_back(false);
		BuildTable(root->left);
	}

	if (root->right != nullptr)
	{
		code.push_back(true);
		BuildTable(root->right);
	}

	if (root->left == nullptr && root->right == nullptr) table[root->c] = code;

	code.pop_back();
}


void Encode(/*int argc, char *argv[]*/)
{
	////// ������� ������� ��������	
	ifstream f("C:\\Users\\darin\\Documents\\Visual Studio 2017\\Projects\\HFMN\\dick in the ass.txt", ios::out | ios::binary);

	map<char, int> m;

	while (!f.eof())
	{
		char c = f.get();
		m[c]++;
	}


	////// ���������� ��������� ���� � ������ list

	list<Node*> t;
	for (map<char, int>::iterator itr = m.begin(); itr != m.end(); ++itr)
	{
		Node *p = new Node;
		p->c = itr->first;
		p->a = itr->second;
		t.push_back(p);
	}
	//////  ������� ������		

	while (t.size() != 1)
	{
		t.sort(MyCompare());

		Node *SonL = t.front();
		t.pop_front();
		Node *SonR = t.front();
		t.pop_front();

		Node *parent = new Node(SonL, SonR);
		t.push_back(parent);

	}

	Node *root = t.front();   //root - ��������� �� ������� ������

							  ////// ������� ���� '������-���':			

	BuildTable(root);

	////// ������� ���� � ���� output.txt

	f.clear(); f.seekg(0); // ���������� ��������� ����� � ������ �����

	ofstream g("output.txt", ios::out | ios::binary);

	int count = 0; char buf = 0;
	while (!f.eof())
	{
		char c = f.get();
		vector<int> x = table[c];
		for (int n = 0; n < x.size(); n++)
		{
			buf = buf | x[n] << (7 - count);
			count++;
			if (count == 8) { count = 0;   g << buf; buf = 0; }
		}
	}

	f.close();
	g.close();
}
void Decode(/*int argc, char *argv[]*/) {
	///// ���������� �� ����� output.txt � �������������� �������

	ifstream F("output.txt", ios::in | ios::binary);

	setlocale(LC_ALL, "Russian"); // ���� ������� ������� ������������ � ��������� ������
	Node *root = t.front();
	Node *p = root;
	int count = 0; char byte;
	byte = F.get();
	while (!F.eof())
	{
		bool b = byte & (1 << (7 - count));
		if (b) p = p->right; else p = p->left;
		if (p->left == nullptr && p->right == nullptr) { cout << p->c; p = root; }
		count++;
		if (count == 8) { count = 0; byte = F.get(); }
	}

	F.close();
}

int main()
{
	const string fileNamea = "C:\\Users\\darin\\Documents\\Visual Studio 2017\\Projects\\HFMN\\dick in the ass.txt";
	const string fileNameb = "C:\\Users\\darin\\Documents\\Visual Studio 2017\\Projects\\HFMN\\off.txt";
	fstream myFileIn(fileNamea, std::ios_base::in);
	fstream myFileOut(fileNameb, std::ios_base::out);
	Encode();
	Decode();
	return 0;
}

