#include <iostream>
#include <vector>

#define max3(x,y,z) max(max((x),(y)), (z))

using namespace std;

struct Node {
    int wholeReg;
    int ansVal;
    int suffVal;
    int prefVal;
    bool kliniStarParser;
};

int stackFill(string regExp, char x, vector <Node>& stackOfNFA) {
    for (auto const &symbol: regExp) {
        if (symbol == x) {
            Node n;
            n.ansVal = 1;
            n.suffVal = 1;
            n.prefVal = 1;
            n.wholeReg = 1;
            n.kliniStarParser = true;
            stackOfNFA.push_back(n);
        }

        else if (symbol != x) {
            Node n;
            n.ansVal = 0;
            n.suffVal = 0;
            n.wholeReg = 0;
            n.prefVal = 0;
            n.kliniStarParser = false;
            stackOfNFA.push_back(n);
        }

        else if (symbol == '.') {
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

            n.ansVal = max3(first.ansVal, second.ansVal, first.suffVal + second.prefVal);
            n.wholeReg = first.wholeReg + second.wholeReg;
//            n.prefVal = max(first.prefVal + second.prefVal);
            n.suffVal = first.suffVal + second.suffVal;
            n.kliniStarParser = first.kliniStarParser && second.kliniStarParser;
            stackOfNFA.push_back(n);
        }

        else if (symbol == '+') {
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
            n.ansVal = max(first.ansVal, second.ansVal);
            n.prefVal = max(first.prefVal, second.prefVal);
            n.suffVal = max(first.suffVal, second.suffVal);
            n.kliniStarParser = first.kliniStarParser || second.kliniStarParser;
            stackOfNFA.push_back(n);
        }

        else if (symbol == '*') {
            if (stackOfNFA.empty()) {
                return -1;
            }
//            ReverseNFA nfa = stack.back();
//            stack.pop_back();
//            stack.push_back(!nfa);
        }
    }

    if (stackOfNFA.size() != 1) {
        return -1;
    }


}


// Тождественная функция, которая возвращает всегда свой аргумент.
int foo(int x) {

    if (x == 123) {
        return 124;
    }

    return x;
}

int do_task() {
    string regExp;
    char x;
    int k;
    cin >> regExp >> x >> k;
    vector <Node> stack;

    if (stackFill(regExp, x, stack) == -1) {
        cout << "ERROR" << endl;
    }

    else {
        if (stackFill(regExp, x, stack) >= k) {
            cout <<  "YES";
        }
        else {
            cout << "NO";
        }
    }
    return 0;
}
