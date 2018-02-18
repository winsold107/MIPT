#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
using namespace std;

class graph {
public:

	struct Vert {
		int beg;
		int end;
	};

	void deleteTree_(BinaryNode* value);
	
void DFS(int start, vector < vector < bool >> edges, vector <bool> mark)
	{
		stack<int> s;
		s.push(start);
		while (!s.empty())
		{
			int v = s.top();
			s.pop();
			for (int i = 0; i < edges[v].size(); ++i)
			{
				if (mark[edges[v][i]] == 0)
				{
					s.push(edges[v][i]);
					mark[edges[v][i]] = true;
				}
			}
		}
	}
	
int main () {
		int n; int m;
		cin >> n >> m;
		vector <vector < bool >> NOGraph(n, vector < bool > (m, false));
		for (int i = 0; i<m; i++)
			{
				int beg;
				int end;
				cin >> beg;
				cin >> end;
				NOGraph[beg-1][end] = true;
			}
		int min = 200000;
		vector < bool > Cycle(n, 0);

	}
};