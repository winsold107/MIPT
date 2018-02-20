#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
using namespace std;

//class graph {
//public:

//struct Vert {
//int beg;
//int end;
//};

//void deleteTree_(BinarsyNode* value);

/*void DFS(int start, vector < vector < bool >> edges, vector <bool> mark)
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

};

int main() {
int n; int m;
cin >> n >> m;
vector <vector < bool >> NOGraph(n, vector < bool >(m, false));
for (int i = 0; i<m; i++)
{
    int beg;
    int end;
    cin >> beg;
    cin >> end;
    NOGraph[beg - 1][end] = true;
}
int min = 200000;
vector < bool > Cycle(n, 0);

}*/
//рассмотреть случаи вершин нет ребра дальше есть в обе стороны дальше в одну сторону претендент обход матрицы лесенкой

int main() {
    int n;
    cin >> n;
    vector <vector < int >> OGraph(n, vector < int >(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
        {
            cin >> OGraph[i][j];
        }
    }
    int i = 0;
    int j = 0;
    while (i < n) {
        while (j < n) {
            if (OGraph[i][j] == OGraph[j][i]) {
                j++;
            }
            else {
                if (OGraph[i][j] == 0) {
                    int k = 0;
                    int counter = 0;
                    while (k < n) {
                        if ((OGraph[i][k] == 0) && (OGraph[k][i] == 1) || (OGraph[k][k] == 0)) {
                            k++;
                        }
                        else {
                            j++;
                        }
                    }
                }
            }
        }
    }
    /*int i = 0;
    int j = 0;
    int k = 0;
    while (i <= n) {
        cout << "1 ";
        while (j < n) {
            cout << "2 ";
            if ((j == n - 1) && (OGraph[i][n-1] == 0)) {
                cout << "3 ";
                while (k < n) {
                    cout << "4 ";
                    if ((k == n - 1) && (OGraph[k][i] == 0)) {
                        cout << "5 ";
                        cout << "YES";
                        return 0;
                    }
                    if ((OGraph[k][i] == 1) && (OGraph[i][i] == 0)) {
                        cout << "6 ";
                        k++;
                    }
                }
            }
            if (OGraph[i][j] == 0) {
                cout << "7 ";
                j++;
            }
            else {
                cout << "8 ";
                j = 0;
                break;
            }
        }
        i++;
        /*if (i == n) {
            cout << "NO";
        }
        return 0;
    }*/
    //cout << "9";
    //cout << "NO";
    return 0;
}