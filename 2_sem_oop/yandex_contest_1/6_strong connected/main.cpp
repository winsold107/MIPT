// Задача 6 про дополнение до сильносвязного графа

#include <iostream>
#include <vector>

using namespace std;

int cur_color = 0;

void DFS(int x, const vector<vector<int>>& graph, vector<int>& time_out, vector <bool>& used) {
    used[x] = true;
    for (int i = 0; i < graph[x].size(); i++)
        if (!used[graph[x][i]])
            DFS(graph[x][i], graph, time_out, used);
    time_out.push_back(x);
}


void DFSTr(int x, const vector<vector<int>>& tgraph, vector<int>& col) {
    col[x] = cur_color;
    for (int i = 0; i < tgraph[x].size(); i++)
        if (!col[tgraph[x][i]])
            DFSTr(tgraph[x][i], tgraph, col);
}


int main() {
    int n, m, a = 0, b = 0;
    cin >> n >> m;

    vector <bool> in(n), out(n), used(n, false);
    vector <int> time_out, col(n, 0);
    vector <vector<int>> OGraph(n), TOGraph(n);

    int beg, en;
    for (int i = 0; i < m; i++) {
        cin >> beg >> en;
        OGraph[beg-1].push_back(en-1);
        TOGraph[en-1].push_back(beg-1);
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) DFS(i,OGraph, time_out, used);
    }

    for (int i = n - 1; i >= 0; i--)
        if (!col[time_out[i]]) {
            cur_color++;
            DFSTr(time_out[i], TOGraph, col);
        }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < OGraph[i].size(); j++)
            if (col[i] != col[OGraph[i][j]]) {
                out[col[i]] = true;
                in[col[OGraph[i][j]]] = true;
            }

    if (cur_color == 1) {
        cout << "0" << endl;
        return 0;
    }

    for (int i = 1; i <= cur_color; i++) {
        a += !out[i];
        b += !in[i];
    }

    cout << max(a, b);

    return 0;
}