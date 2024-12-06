#ifndef GRAPH_H
#define GRAPH_H

#include "Array.h"

class Graph {
public:
    int** adjMatrix; // Dynamic 2D array for adjacency matrix
    int vertices;

    Graph(int v);
    ~Graph();
    void addEdge(int u, int v, int weight);
    Array Dijkstra(int start, int end);
};

#endif // GRAPH_H
