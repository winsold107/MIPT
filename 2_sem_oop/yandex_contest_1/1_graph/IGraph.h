//
// Created by darin on 25.02.18.
//

#ifndef INC_1_GRAPH_IGRAPH_H
#define INC_1_GRAPH_IGRAPH_H

#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};

IGraph* get_my_hash_graph();

#endif //INC_1_GRAPH_IGRAPH_H
