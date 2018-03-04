#include <iostream>
#include <vector>
using namespace std;

int cur_c, next_vis;

void DFS(int x, vector <vector<int>>& graph, vector<int>& time_out, vector <int>& used) {
    used[x] = next_vis; // "закрашиваем" эту вершину "цветом" next_vis
    for (int i = 0; i < graph[x].size(); i++)
        if (!used[graph[x][i]]) DFS(graph[x][i], graph, time_out, used);
    time_out.push_back(x);
}

void DFSTr(int x, vector <vector<int>>& tgraph, vector<int>& col) {
    col[x] = cur_c;
    for (int i = 0; i < tgraph[x].size(); i++)
        if (!col[tgraph[x][i]])
            DFSTr(tgraph[x][i], tgraph, col);
}

bool match(int x, vector<int>& used, vector<int>& m_b, vector<vector<int>>& graph, unsigned long n, vector<int>& next_s, vector<int>& col) {
    vector <bool> dead(n), out(n);
    if (dead[x] || used[x] == next_vis) return false;

    used[x] = next_vis;

    if (!out[col[x]]) {
        m_b.push_back(x);
        out[col[x]] = true;
        return true;
    }

    while (next_s[x] < graph[x].size() && !match(graph[x][next_s[x]], used, m_b, graph, n, next_s, col))
        next_s[x]++;
    return !(dead[x] = next_s[x] == graph[x].size());
}

int main() {
    unsigned long n, m, a = 0, b = 0;
    vector <bool> in, out, dead;
    vector <int> time_out(n), m_a(n), m_b(n), used(n), col(n), next_s(n);
    vector <vector<int>> OGraph;
    vector <vector<int>> TOGraph;

    cin >> n;
    cin >> m;
    int beg, en;
    for (int i = 0; i<m; i++) {
        cin >> beg;
        cin >> en;
        OGraph[beg].push_back(en);
        TOGraph[en].push_back(beg);
    }

    next_vis = 1;
    for (int i = 0; i < n; i++) {
        if (!used[i]) DFS(i,OGraph, time_out, used);
    }

    for (int i = n - 1; i >= 0; i--)
        if (!col[time_out[i]]) {
            cur_c++;
            DFSTr(time_out[i], TOGraph, col);
        }

    // Находим связные компоненты в которые что-то входит
    // и связные компоненты из которых что-то выходит в другие компоненты.
    for (int i = 0; i < n; i++)
        for (int j = 0; j < OGraph[i].size(); j++)
            if (col[i] != col[OGraph[i][j]])
                out[col[i]] = in[col[OGraph[i][j]]] = true;

    if (cur_c == 1) {
        printf("0\n");
        return 0;
    }

    for (int i = 1; i <= cur_c; i++) {
        a += !out[i];
        b += !in[i];
    }
    cout << max(a, b); //  Бинарный оператор "a >? b" есть max(a,b).

    for (int i = 0; i < n; i++) {
        next_vis++;
        if (!in[col[i]] && !dead[i] && match(i, used, m_b, OGraph, n, next_s, col)) {
            m_a.push_back(i);
            in[col[i]] = true;
        }
    }

    for (int i = 0; i < m_a.size(); i++)
        printf("%d %d\n", m_b[i], m_a[(i + 1) % m_a.size()]);

    vector<int> A, B;
    for (int i = 0; i < n; i++) {
        if (!in[col[i]]) A.push_back(i);
        in[col[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        if (!out[col[i]]) B.push_back(i);
        out[col[i]] = true;
    }

    while (A.size() && B.size()) {
        printf("%d %d\n", B.back(), A.back());
        A.pop_back();
        B.pop_back();
    }

    while (A.size()) {
        printf("%d %d\n", m_b.back(), A.back());
        A.pop_back();
    }

    while (B.size()) {
        printf("%d %d\n", B.back(), m_a.back());
        B.pop_back();
    }

    return 0;
}