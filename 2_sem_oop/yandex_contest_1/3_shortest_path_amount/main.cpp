#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int pathCounterFromTo (int start, int end, vector <bool> used, vector <vector<int>> g, vector <int> paths, vector <int> depths)
{
    // Stores info about visited vertex
    //vector<Vertex> states(verticesNumber_);
    // BFS queue
    queue<int> q;
    q.push(start);
    paths[0] = 1;

    // BFS from first vertex
    while(!q.empty()){
        //vector<int> nextVertices;
        // Current vertex
        int v = q.front();
        q.pop();
        //getNextVertices(v, nextVertices);

        int n = start;
        for(int i = 0; g[n].size(); i++){
            if (!used[end]) {
                used[end] = true;
                if (paths[i] == 0) {
                    // If not visited push into queue
                    q.push(i);
                    depths[i] = depths[v] + 1;
                    paths[i] = paths[v];
                }
            }
            else if (depths[i] == depths[v] + 1) {
                // If visited and has same depth increase path number
                paths[i] += paths[v];
            }
        }
    }
    return paths[end];
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

    int from;
    int to;
    cin >> from >> to;
    ///кажется некорректно работает чтение графа, прочитать про списки смежностей
    ///true или же значение соединения (те 2й конец ребра)?

    vector < int > paths (n, 0);
    vector < bool > used (n, false);
    vector < int > depths (n, 0);

    pathCounterFromTo(from, to, used, NOGraph, paths, depths);
    return 0;
}