#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "Array.h"
#include "Graph.h"

class Characters {
public:
    bool movePlayer(char** terrain, int& playerRow, int& playerCol, char& lastTile, bool& b);
    void moveEnemies(char** terrain, Graph& graph, int playerVertex, Array& enemyPositions, bool& b);
};

#endif // CHARACTERS_H
