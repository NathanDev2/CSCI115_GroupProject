#include "Characters.h"
#include "Constants.h"
#include <conio.h>
#include <cstdlib>

bool Characters::movePlayer(char** terrain, int& playerRow, int& playerCol, char& lastTile, bool& b) { 
    char input;

    input = _getch();

    int newRow = playerRow;
    int newCol = playerCol;

    bool validInput = false; // Default to invalid input

    // Actions for each user input and set bools for input validity and map looping
    if (input == 'W' || input == 'w') {
        newRow--;          
        validInput = true;  
        b = false;
    } else if (input == 'S' || input == 's') {
        newRow++;           
        validInput = true;
        b = false;
    } else if (input == 'A' || input == 'a') {
        newCol--;           
        validInput = true;
        b = false;
    } else if (input == 'D' || input == 'd') {
        newCol++;           
        validInput = true;
        b = false;
    } else if (input == ' ') { 
        validInput = true;
        b = false;
    } else if (input == 'M' || input == 'm') {
        validInput = true;
        b = true;           
    } else if (input == 'Q' || input == 'q') {
        exit(0);            
    }

    // Ensure new position is within bounds and walkable
    if (validInput && !b &&newRow >= 0 && newRow < MAX_ROWS &&newCol >= 0 && newCol < MAX_COLS && (terrain[newRow][newCol] == PATH || terrain[newRow][newCol] == SECRET_PASSAGE || terrain[newRow][newCol] == DIRT)) {

        // Restore the last tile where the player was
        if (lastTile == DIRT || lastTile == SECRET_PASSAGE) {
            terrain[playerRow][playerCol] = lastTile; // Restore DIRT or SECRET_PASSAGE
        } else {
            terrain[playerRow][playerCol] = PATH; // Default to PATH
        }

        // Update the player's position
        lastTile = terrain[newRow][newCol];
        terrain[newRow][newCol] = PLAYER;
        playerRow = newRow;
        playerCol = newCol;
    }

    return validInput; // Return whether the input was valid
}


void Characters::moveEnemies(char** terrain, Graph& graph, int playerVertex, Array& enemyPositions, bool& b) {
    static char* lastEnemyTiles = new char[MAX_VERTICES]; // Dynamic array for enemy tiles
    bool* occupied = new bool[MAX_VERTICES]();           // Dynamic array for occupied positions

    // Search for and Initialize occupied positions
    for (int i = 0; i < enemyPositions.arraySize; i++) {
        occupied[enemyPositions.GetElement(i)] = true;
    }
    //For each enemy, run once
    for (int i = 0; i < enemyPositions.arraySize; i++) {
        int enemyVertex = enemyPositions.GetElement(i); //Get enemy vertex
        Array path = graph.Dijkstra(enemyVertex, playerVertex); // Get the shortest path

        //If path is longer than stop distance, update row and column variables
        if (path.arraySize > ENEMY_STOP_DISTANCE + 1) {
            int nextMoveVertex = path.GetElement(1);
            int enemyRow = enemyVertex / MAX_COLS;
            int enemyCol = enemyVertex % MAX_COLS;
            int newRow = nextMoveVertex / MAX_COLS;
            int newCol = nextMoveVertex % MAX_COLS;

            //Check if next vertice is a valid position
            if (terrain[newRow][newCol] != WALL && terrain[newRow][newCol] != PLAYER && !occupied[nextMoveVertex]) {
                // Restore the original tile under the enemy's previous position
                if (lastEnemyTiles[enemyVertex] == PATH || lastEnemyTiles[enemyVertex] == DIRT || lastEnemyTiles[enemyVertex] == SECRET_PASSAGE) {
                    terrain[enemyRow][enemyCol] = lastEnemyTiles[enemyVertex];
                } else {
                    terrain[enemyRow][enemyCol] = PATH; // Default to PATH if undefined
                }

                // Save the current tile under the new position
                lastEnemyTiles[nextMoveVertex] = terrain[newRow][newCol];
                terrain[newRow][newCol] = ENEMY; 

                // Update enemy position in the array
                enemyPositions.array[i] = nextMoveVertex;
                occupied[nextMoveVertex] = true;
            }
        }
    }

    // Clean up dynamically allocated memory for this iteration
    delete[] occupied;
}
