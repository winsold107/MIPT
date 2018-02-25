//
// Created by darin on 25.02.18.
//

#ifndef INC_1_GRAPH_HASHGRAPH_H
#define INC_1_GRAPH_HASHGRAPH_H

#include "IGraph.h"
#include <unordered_set>

using namespace std;

class HashGraph : public IGraph {
public:

    HashGraph(int size);

    HashGraph(const IGraph* another);

    virtual void AddEdge(int from, int to);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
    vector<unordered_set<int>> _verticesLists;

};

#endif //INC_1_GRAPH_HASHGRAPH_H
