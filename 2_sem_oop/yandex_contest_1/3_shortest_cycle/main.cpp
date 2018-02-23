#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs (vector<vector<int>> g, vector <bool>& used, vector <int>& cycle, int start, int n, vector < int > len) {
    //vector < int > len (n);

    queue<int> q;
    q.push(start);

    used[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < g[v].size(); i++) {
            int to = g[v][i];

            if (!used[to]) {
                used[to] = true;
                q.push(to);
                len[to] = len[v] + 1;
                //cout << len[v];
            }

            else {
                //cout<<"1 ";
                cycle[to] = len[to]+1;
                cout<<cycle[to]<<" ";
                return;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    int m;
    cin >> m;

    vector <vector < int >> NOGraph(n);

    for (int i = 0; i<m; i++) {
        int beg;
        int end;
        cin >> beg;
        cin >> end;
        NOGraph[beg].push_back(end);
    }
    ///кажется некорректно работает чтение графа, прочитать про списки смежностей
    ///true или же значение соединения (те 2й конец ребра)?

    vector < int > len_cycle (n, 0);
    vector < bool > used (n, false);
    vector < int > length (n, 0);

    for (int index = 0; index<n; index++) {
        bfs(NOGraph, used, len_cycle, index, n, length);
    }

    int minimum = 9999999;
    int counter = 0;

    for (unsigned long i = 0; i<n; i++){
        if (len_cycle[i] < minimum) {
            if ((len_cycle[i] == 0)||(len_cycle[i] == 1)) {
                counter += 1;
            }
            else if (len_cycle[i]!=1){
                minimum = len_cycle[i];
            }
        }
    }
    for (int i = 0; i<n; i++){
        cout<<len_cycle[i]<<" ";
    }
    if (counter == n) {
        cout << "0 ";
    }
    else {
        cout << minimum;
    }
    return 0;
}