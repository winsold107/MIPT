#include <iostream>
//#include "IGraph.h"
#include "HashGraph.h"
#include <memory>

using namespace std;


int main() {

    unique_ptr<HashGraph> g( new HashGraph(5) );
    IGraph* ig = g.get();

//    IGraph* ig = get_my_hash_graph();

    ig->AddEdge(2, 3);
    vector<int> res;
    ig->GetPrevVertices(3, res);

    for( int i = 0; i < res.size(); i++ ) {
        cout << res[i];
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}