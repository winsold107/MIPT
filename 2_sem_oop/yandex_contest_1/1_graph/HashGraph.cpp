//
// Created by darin on 25.02.18.
//

#include "HashGraph.h"

HashGraph::HashGraph(int size) : _verticesLists(size) {}

HashGraph::HashGraph(const IGraph *another) : _verticesLists(another->VerticesCount()) {
    vector<int> curList;

    for (int i = 0; i < _verticesLists.size(); ++i) {

        another->GetNextVertices(i, curList);

        for (int j = 0; j < curList.size(); ++j) {
            _verticesLists[i].insert(curList[j]);
        }

        curList.resize(0);
    }


}

void HashGraph::AddEdge(int from, int to) {
    _verticesLists[from].insert(to);
}

int HashGraph::VerticesCount() const {
    return _verticesLists.size();
}

void HashGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for (const auto& x: _verticesLists[vertex]) {
        vertices.push_back(x);
    }
}

void HashGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for (int i = 0; i < _verticesLists.size(); ++i) {
        auto& my_set = _verticesLists[i];

        if (my_set.find(vertex) != my_set.end()) {
            vertices.push_back(i);
        }
    }
}

//IGraph* get_my_hash_graph() {
//    return new HashGraph(5);
//}
