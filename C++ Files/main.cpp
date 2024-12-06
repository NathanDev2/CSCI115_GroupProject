#include "Map.h"
#include "Graph.h"
#include "Array.h"
#include "Constants.h"
#include "Characters.h"
#include <iostream>
using namespace std;

int main() {
    Map map;                          // Map object with dynamic terrain
    int playerVertex;                 // Player's position in the graph
    Array enemyPositions;             // Array to store enemy positions
    Graph graph(MAX_VERTICES);        // Graph with dynamic adjacency matrix
    Characters characters;            // Characters class for player and enemies
    char charInput = '\0';            // Input for map selection

    bool b = true;
    while (b) { // Loop to select the map or quit
        charInput = '\0'; // Reset userInput to initial value at the beginning of each iteration

        system("color 0A");
        system("cls");
        cout << "\t\t\t*******************************************" << endl;
        cout << "\t\t\t|                                         |" << endl;
        cout << "\t\t\t|   Choose a Map or press 'q'  to quit.   |" << endl;
        cout << "\t\t\t|                                         |" << endl;
        cout << "\t\t\t|                                         |" << endl;
        cout << "\t\t\t|  1. Map 1                               |" << endl;
        cout << "\t\t\t|  2. Map 2                               |" << endl;
        cout << "\t\t\t|  3. Map 3                               |" << endl;
        cout << "\t\t\t|  4. Map 4                               |" << endl;
        cout << "\t\t\t|  5. Map 5                               |" << endl;
        cout << "\t\t\t|                                         |" << endl;
        cout << "\t\t\t*******************************************" << endl;
        cout << "\t\t\t Enter here: ";
        cin >> charInput;
        system("cls");

        // Load the selected map
        if (charInput == '1') {
            map.loadFromFile(graph, playerVertex, enemyPositions, "map1.txt");
            b = false;
        } else if (charInput == '2') {
            map.loadFromFile(graph, playerVertex, enemyPositions, "map2.txt");
            b = false;
        } else if (charInput == '3') {
            map.loadFromFile(graph, playerVertex, enemyPositions, "map3.txt");
            b = false;
        } else if (charInput == '4') {
            map.loadFromFile(graph, playerVertex, enemyPositions, "map4.txt");
            b = false;
        } else if (charInput == '5') {
            map.loadFromFile(graph, playerVertex, enemyPositions, "map5.txt");
            b = false;
        } else if (charInput == 'q' || charInput == 'Q') {
            return 0; // Quit the program
        } else {
            cout << "Invalid Value. Press any key to continue..." << endl;
            cin.get();
            cin.ignore();
            system("color 0A");
            system("cls");
            b = true;
        }

        // Game logic begins once a map is selected
        int playerRow = playerVertex / MAX_COLS;  // Row of the player
        int playerCol = playerVertex % MAX_COLS;  // Column of the player
        char lastTile = PATH;                     // Last tile the player was on
        


        if (!b) { // Game loop
            while (!b) {
                map.display(); // Show the map

                // Move player and only move enemies if the player input is valid
                if (characters.movePlayer(map.getTerrain(), playerRow, playerCol, lastTile, b)) {
                    playerVertex = playerRow * MAX_COLS + playerCol;
                    characters.moveEnemies(map.getTerrain(), graph, playerVertex, enemyPositions, b);
                }
            }
        }
    }

    return 0;
}
