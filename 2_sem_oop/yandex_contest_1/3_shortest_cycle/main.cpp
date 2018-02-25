#include <iostream>
#include <vector>
#include <queue>
//#include <limits>

using namespace std;

int ans = 999999999;

void bfs(const vector<vector<int>> &g, vector<int> &cycle, int start, int n) {
    //vector < int > len (n);
    vector<int> len(n, 0);
//    vector<bool> used(n, false);
    vector<int> from(n, -1);
    queue<int> q;
    q.push(start);

//    used[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < g[v].size(); i++) {
            int to = g[v][i];

            if (from[v] == to) continue;

            if (from[to] == -1) {
                from[to] = v;
                q.push(to);
                len[to] = len[v] + 1;
//                cout << len[v];
            } else {
                //cout<<"1 ";
                int len_candidate = len[v] + 1 + len[to];
                if (ans > len_candidate) {
                    ans = len_candidate;
                }
                return;
//                cycle[start] = len[v] + 1 + len[to];
//                cout << cycle[to] << " ";
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    int m;
    cin >> m;

    vector<vector<int >> NOGraph(n);

    for (int i = 0; i < m; i++) {
        int beg;
        int end;
        cin >> beg;
        cin >> end;
        NOGraph[beg].push_back(end);
        NOGraph[end].push_back(beg);
    }

    vector<int> len_cycle(n, 0);

    for (int index = 0; index < n; index++) {
        bfs(NOGraph, len_cycle, index, n);
    }

//    int minimum = numeric_limits<int>::max();
//    int counter = 0;

//    for (unsigned long i = 0; i < n; i++) {
//        if (len_cycle[i] < minimum) {
//            if ((len_cycle[i] == 0) || (len_cycle[i] == 1)) {
//                counter += 1;
//            } else if (len_cycle[i] != 1) {
//                minimum = len_cycle[i];
//            }
//        }
//    }
//    for (int i = 0; i < n; i++) {
//        cout << len_cycle[i] << " ";
//    }
//    if (counter == n) {
//        cout << "0 ";
//    } else {
//        cout << minimum;
//    }
    if (ans == 999999999) {
        cout<<"-1";
    }
    else {
        cout << ans << endl;
    }
    return 0;
}