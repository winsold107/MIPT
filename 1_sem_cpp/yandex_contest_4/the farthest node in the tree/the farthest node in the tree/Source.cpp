#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node
{
	Node(int val, int dep) : v(val), depth(dep) { }
	int v;
	int depth;
};

vector<Node> nodas;
vector <vector<Node*>> matrix;
vector<int> depths;
int* answers;


void calcDepths(int curDepth, Node* v)
{
	int maks = 0;
	for (int i = 0; i < matrix[v->v].size(); i++)
	{
		calcDepths(curDepth, matrix[v->v][i]);

		int cur = matrix[v->v][i]->depth + 1;
		if (cur > maks)
		{
			maks = cur;
		}
	}
	v->depth = maks;
};


int maxChild(Node* val, Node* e)
{
	int maks = -1;
	vector<Node*>& children = matrix[val->v];
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] != e)
		{
			if (children[i]->depth > maks)
			{
				maks = children[i]->depth;
			}
		}
	}
	return maks;
}

void calcDists(int maxDist, Node* v)
{
	answers[v->v] = max(maxChild(v, nullptr) + 1, maxDist);
	vector<Node*>& children = matrix[v->v];
	for (int i = 0; i < children.size(); i++)
	{
		int ch = maxChild(v, children[i]) + 2;
		calcDists(max(ch, maxDist + 1), children[i]);
	}
}

int main()
{


	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		nodas.push_back(Node(i, -1));
	}
	
	matrix.resize(n, vector <Node*>());
	answers = new int[n];

	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		cin >> a >> b;
		if (a < b)
		{
			matrix[a].push_back(&nodas[b]);
		}
		else {
			matrix[b].push_back(&nodas[a]);
		}
	}

	calcDepths(0, &nodas[0]);
	calcDists(0, &nodas[0]);

	for (int i = 0; i < n; i++)
	{
		cout << answers[i] << endl;
	};

	system("pause");
	return 0;
}
