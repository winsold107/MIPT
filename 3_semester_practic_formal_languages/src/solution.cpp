#include <iostream>
#include <vector>
#include <limits>
#define max3(x,y,z) max(max((x),(y)), (z))

using namespace std;

int NUM = (-1) * numeric_limits <int>::max();

struct Node {
    int wholeReg;
    int ansVal;
    int suffVal;
    int prefVal;
};

int stackFill(string regExp, char x, int k) {
    vector <Node> stackOfNFA;
    for (auto const &sym: regExp) {
        if (sym == x) {
            Node n;
            n.ansVal = 1;
            n.suffVal = 1;
            n.prefVal = 1;
            n.wholeReg = 1;
            stackOfNFA.push_back(n);
        }

        else if (sym != x && sym != '.' && sym != '*' && sym != '+') {
            Node n;
            n.ansVal = 0;
            n.suffVal = 0;
            n.wholeReg = NUM;
            n.prefVal = 0;
            stackOfNFA.push_back(n);
        }

        else if (sym == '.') {
            if (stackOfNFA.empty()) {
                return -1;
            }
            Node second = stackOfNFA.back();
            stackOfNFA.pop_back();
            if (stackOfNFA.empty()) {
                return -1;
            }
            Node first = stackOfNFA.back();
            stackOfNFA.pop_back();
            Node n;

            n.prefVal = max(first.prefVal, second.prefVal + first.wholeReg);
            n.suffVal = max(second.suffVal, first.suffVal + second.wholeReg);
            n.ansVal = max3(first.ansVal, second.ansVal, first.suffVal + second.prefVal);
            if (first.wholeReg < 0 || second.wholeReg < 0) {
                n.wholeReg = NUM;
            }
            else {
                n.wholeReg = first.wholeReg + second.wholeReg;
            }
            stackOfNFA.push_back(n);
        }

        else if (sym == '+') {
            if (stackOfNFA.empty()) {
                return -1;
            }
            Node second = stackOfNFA.back();
            stackOfNFA.pop_back();
            if (stackOfNFA.empty()) {
                return -1;
            }
            Node first = stackOfNFA.back();
            stackOfNFA.pop_back();
            Node n;
            n.prefVal = max(first.prefVal, second.prefVal);
            n.suffVal = max(first.suffVal, second.suffVal);
            n.wholeReg = max(first.wholeReg, second.wholeReg);
            n.ansVal = max(first.ansVal, second.ansVal);
            stackOfNFA.push_back(n);
        }

        else if (sym == '*') {
            if (stackOfNFA.empty()) {
                return -1;
            }
            Node last = stackOfNFA.back();
            stackOfNFA.pop_back();
            Node n;

            if (last.wholeReg == 0) {
                n.wholeReg = 0;
            }

            else if(last.wholeReg > 0) {
                n.wholeReg = (-1) * NUM;
            }

            else {
                n.wholeReg = max(0, last.wholeReg);
            }

            n.suffVal = max(n.wholeReg, last.suffVal);
            n.prefVal = max(n.wholeReg, last.prefVal);
            n.ansVal = max3(n.wholeReg, last.suffVal + last.prefVal, last.ansVal);
            stackOfNFA.push_back(n);
        }
    }

    if (stackOfNFA.size() != 1) {
        return -1;
    }

    else {
        if (stackOfNFA.back().ansVal >= k) {
            return 0;
        }

        else {
            return 1;
        }
    }
}

int regExpParser() {
    string regExp;
    char x;
    int k;
    cin >> regExp >> x >> k;

    int potential_answer = stackFill(regExp, x, k);

    if (potential_answer == -1) {
        cout << "ERROR" << endl;
    }

    else {
        if (potential_answer == 0) {
            cout <<  "YES";
        }

        else {
            cout << "NO";
        }
    }
    return 0;
}