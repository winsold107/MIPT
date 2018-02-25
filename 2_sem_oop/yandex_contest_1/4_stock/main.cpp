#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

bool checkCandidate(int candidate, const vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        assert(matrix[i][i] == 0);
        if (candidate == i) continue;

        if ((matrix[i][candidate] == 0) || (matrix[candidate][i] == 1)) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            cin >> matrix[i][k];
        }
    }
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<int> potential;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (visited[i][k] == false) {
                visited[i][k] = true;
                visited[k][i] = true;
                if (matrix[i][k] != matrix[k][i]) {
                    if (matrix[i][k] == 1) {
                        potential.push_back(k);
//                        for (int m = 0; m < potential.size(); m++) {
//                            if (matrix[potential[m]][i] == 1) {
//                                potential.erase(potential.begin() + m);
//                            }
//                        }
                    } else {
                        potential.push_back(i);
//                        for (int l = 0; l < potential.size(); l++) {
//                            if (matrix[potential[l]][k] == 0) {
//                                potential.erase(potential.begin() + l);
//                            }
//                        }
                    }
                }
            }
        }
    }


    for (int p = 0; p < potential.size(); p++) {
        if (checkCandidate(potential[p], matrix)) {
            cout << "YES" << endl;
            return 0;
        }
    }

    cout << "NO" << endl;
    return 0;
}
