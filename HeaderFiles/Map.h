#ifndef MAP_H
#define MAP_H

#include "Graph.h"
#include "Array.h"
#include <string>

class Map {
private:
    char** terrain;
    int rows;
    int cols;

public:
    Map();
    ~Map();
    bool loadFromFile(Graph& graph, int& playerVertex, Array& enemyPositions, const std::string& filename);
    void display() const;
    char** getTerrain();
};

#endif // MAP_H
