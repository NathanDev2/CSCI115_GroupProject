#include "Graph.h"
#include "Constants.h"
#include "MinHeap.h"
#include <climits>

Graph::Graph(int v) : vertices(v) {
    adjMatrix = new int*[vertices];
    for (int i = 0; i < vertices; i++) {
        adjMatrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            adjMatrix[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < vertices; i++) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

void Graph::addEdge(int u, int v, int weight) {
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight;
}

Array Graph::Dijkstra(int start, int end) {
    int* dist = new int[vertices];  // Dynamic distance array
    int* prev = new int[vertices]; // Dynamic previous vertex array
    bool* visited = new bool[vertices](); // Dynamic visited array

    for (int i = 0; i < vertices; i++) { //Set default values for both arrays
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[start] = 0;

    //MinHeap setup
    MinHeap pq;    
    pq.Insert(start, 0); 

    bool pathFound = false;

    //Process every vertice until end is found
    while (!pq.isEmpty() && !pathFound) {
        auto [currentDist, u] = pq.Poll();

        if (!visited[u]) {
            visited[u] = true;

            if (u == end) {
                pathFound = true;
            } 
            else {   //Compares all valid vertices and inserts the best one to pq
                for (int v = 0; v < vertices; v++) {
                    if (!visited[v] && adjMatrix[u][v] != INT_MAX) {
                        int alt = dist[u] + adjMatrix[u][v];
                        if (alt < dist[v]) {
                            dist[v] = alt;
                            prev[v] = u;
                            pq.Insert(v, alt);
                        }
                    }
                }
            }
        }
    }
    //Flips the shortest path to be from start to the end
    Array path;
    int at = end;
    while (at != -1) {
        path.Insert(at);
        at = prev[at];
    }
    for (int i = 0; i < path.arraySize / 2; i++) {
        swap(path.array[i], path.array[path.arraySize - i - 1]);
    }


    // Free dynamically allocated arrays
    delete[] dist;
    delete[] prev;
    delete[] visited;

    return path;
}