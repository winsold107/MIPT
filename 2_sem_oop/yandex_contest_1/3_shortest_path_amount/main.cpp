#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cassert>

using namespace std;
//int pathCounterFromTo (int start, int end, vector <bool> used, vector <vector<int>> g, vector <int> paths, vector <int> depths)
//{
//    // Stores info about visited vertex
//    //vector<Vertex> states(verticesNumber_);
//    // BFS queue
//    queue<int> q;
//    q.push(start);
//    paths[0] = 1;
//
//    // BFS from first vertex
//    while(!q.empty()){
//        //vector<int> nextVertices;
//        // Current vertex
//        int v = q.front();
//        q.pop();
//        //getNextVertices(v, nextVertices);
//
//        int n = start;
//        for(int i = 0; g[n].size(); i++){
//            if (used[i])
//            if (!used[end]) {
//                //used[end] = true;
//                if (paths[i] == 0) {
//                    // If not visited push into queue
//                    q.push(i);
//                    depths[i] = depths[v] + 1;
//                    paths[i] = paths[v];
//                }
//            }
//            else if (depths[i] == depths[v] + 1) {
//                // If visited and has same depth increase path number
//                paths[i] += paths[v];
//            }
//        }
//    }
//    return paths[end];
//}


int pathCounterFromTo(const vector<vector<int>> &g, int start, int n, int end) {
//    int min_length = numeric_limits<int>::max();
    vector<int> depth(n, 0);
    vector<int> ans(n, 0);
    vector<int> from(n, -1);

    ans[start] = 1;
    depth[start] = 0;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < g[v].size(); i++) {
            int to = g[v][i];

            if (from[v] == to) continue;

            if (from[to] == -1) {
                from[to] = v;
                ans[to] = ans[v];
                depth[to] = depth[v] + 1;
                q.push(to);
                continue;
            }

//            depth[to] = min(depth[v]+1, depth[to]);
//
            int suggested_depth = depth[v] + 1;
            assert(suggested_depth >= depth[to]);

            if (suggested_depth == depth[to]) {
                // не понятно так: ans[to]++; или
                ans[to]+=ans[v];
            }


//                cout << len[v];
//            else {
//                cout<<"1 ";
//                int path_candidate = path[v] + 1 + path[to];
//                if (ans > path_candidate) {
//                    ans = path_candidate;
//                }
//                return;
//                cycle[start] = len[v] + 1 + len[to];
//                cout << cycle[to] << " ";

//            if (to == end) {
//                if (path[v] + 1 < min_length) {
//                    min_length = path[v] + 1;
//                    counter = 0;
//                    counter++;
//                } else if (path[v] + 1 == min_length) {
//                    counter++;
//                }
        }
    }

    return ans[end];
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

    int from;
    int to;
    cin >> from >> to;

    vector<int> paths(n, 0);
    vector<bool> used(n, false);
    vector<int> depths(n, 0);

    cout << pathCounterFromTo(NOGraph, from, n, to);
    return 0;
}