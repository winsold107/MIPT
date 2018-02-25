#include <iostream>
//#include "IGraph.h"
#include "HashGraph.h"

using namespace std;


int main() {

    HashGraph* g = new HashGraph(5);
    IGraph* ig = g;

//    IGraph* ig = get_my_hash_graph();


    vector<int> res;
    ig->GetPrevVertices(2, res);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}