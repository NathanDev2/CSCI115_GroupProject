#include "Map.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>

//Allocate terrain dynamically
Map::Map(){
    rows = 0;
    cols = 0;
    terrain = new char*[MAX_ROWS]; //Create terrain array with a capacity equal to MAX_ROWS
    
    //Fills every array element with an array of elements of size equal to MAX_COLS
    for (int i = 0; i < MAX_ROWS; i++) {
        terrain[i] = new char[MAX_COLS];
    }
}

// Destructor: Free `terrain`
Map::~Map() {
    for (int i = 0; i < MAX_ROWS; i++) {
        delete[] terrain[i];
    }
    delete[] terrain;
}

//Loads file completely if successful, if file is not found, return false
bool Map::loadFromFile(Graph& graph, int& playerVertex, Array& enemyPositions, const string& filename) {
    // Clear previous map data
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            terrain[i][j] = ' '; // Reset terrain to a blank state
        }
    }

    // Clear graph and enemies
    enemyPositions.Clear();
    for (int i = 0; i < graph.vertices; i++) {
        for (int j = 0; j < graph.vertices; j++) {
            if (i == j) {
                graph.adjMatrix[i][j] = 0;
            } else {
                graph.adjMatrix[i][j] = INT_MAX;
            }
        }
    }

    // Reset player position
    playerVertex = -1;

  // Construct the full path to the file in the "Maps" folder
    string fullPath = "Maps/" + filename;

    // Open the file
    ifstream file(fullPath);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    string line;
    rows = 0;
    cols = 0;

    //Get every line from each row
    while (getline(file, line) && rows < MAX_ROWS) {
        cols = max(cols, static_cast<int>(line.length())); //Set cols equal to length of line 
        
        //For loop to go through every column in line
        for (size_t col = 0; col < line.length() && col < MAX_COLS; col++) {
            terrain[rows][col] = line[col]; //Append each character to terrain
            int position = rows * MAX_COLS + col; //Set position equal to vertex number of the character currently on

            //Set player and enemy vertexs
            if (terrain[rows][col] == PLAYER) {
                playerVertex = position;
            } 
            //If character is a enemy
            else if (terrain[rows][col] == ENEMY) {
                enemyPositions.Insert(position); 
            }

            // Weight Definitions (Checks if it is a valid terrain)
            if (terrain[rows][col] == PATH || terrain[rows][col] == DIRT || terrain[rows][col] == SECRET_PASSAGE || terrain[rows][col] == PLAYER || terrain[rows][col] == ENEMY) {
                int weight = 1;
                if (terrain[rows][col] == SECRET_PASSAGE) {     //If Secret Passage, Weight = INT_MAX
                    weight = INT_MAX;
                } 
                else if (terrain[rows][col] == WALL) {          //If Wall, Weight = -1
                    weight = -1;
                }
                else if (terrain[rows][col] == DIRT) {          //If Dirt, Weight = 2
                    weight = 2;
                }

                //If position at row n-1 isn't a wall, add edge between n and n-1 with appropriate weight (Position of x to top of x)
                if (rows > 0 && terrain[rows - 1][col] != WALL) {
                    graph.addEdge(position, (rows - 1) * MAX_COLS + col, weight);
                }
                //If position at row n+1 isn't a wall, add edge between n+1 and n with appropriate weight (Position of x to bottom of x)
                if (rows < MAX_ROWS - 1 && terrain[rows + 1][col] != WALL) {
                    graph.addEdge(position, (rows + 1) * MAX_COLS + col, weight);
                }
                //If position at column n-1 isn't a wall, add edge between n and n-1 with appropriate weight (Position of x to left of x)
                if (col > 0 && terrain[rows][col - 1] != WALL) {
                    graph.addEdge(position, rows * MAX_COLS + (col - 1), weight);
                }
                //If position at column n+1 isn't a wall, add edge between n and n-1 with appropriate weight (Position of x to right of x)
                if (col < MAX_COLS - 1 && terrain[rows][col + 1] != WALL) {
                    graph.addEdge(position, rows * MAX_COLS + (col + 1), weight);
                }
            }
        }
        rows++; //Go to the next row
    }

    file.close(); //Close file
    return true; //Return true if file opens successful
}


void Map::display() const {

    system("cls"); // Clear the screen for a clean display

    // Display controls with colors
    cout << "Controls: ";
    cout << "\033[32mW (up)\033[0m, "     // Green for "W"
         << "\033[34mA(left)\033[0m, "   // Blue for "A"
         << "\033[33mS(down)\033[0m, "   // Yellow for "S"
         << "\033[31mD(right)\033[0m, "  // Red for "D"
         << "\033[35mM(change map)\033[0m, " // Magenta for "M"
         << "\033[36mQ(quit)\033[0m"     // Cyan for "Q"
         << endl;

    cout << "-------------------------------------------------------------" << endl;

    // Display the map with the cell and its assigned color
    for (int i = 0; i < rows; i++) {                      
        for (int j = 0; j < cols; j++) {                  
            if (terrain[i][j] == PLAYER) {               
                cout << COLOR_PLAYER << "o " << COLOR_RESET;
            } else if (terrain[i][j] == ENEMY) {           
                cout << COLOR_ENEMY << "x " << COLOR_RESET;
            } else if (terrain[i][j] == DIRT) {            
                cout << COLOR_DIRT << "* " << COLOR_RESET;
            } else if (terrain[i][j] == PATH) {             
                cout << COLOR_PATH << ". " << COLOR_RESET;
            } else if (terrain[i][j] == SECRET_PASSAGE) {   
                cout << COLOR_SECRET << "* " << COLOR_RESET;
            } else if (terrain[i][j] == WALL) {            
                cout << COLOR_WALL << "# " << COLOR_RESET;
            } else {                                        
                cout << "  "; // Empty spaces for unknown tiles
            }
        }
        cout << endl;
    }
}

char** Map::getTerrain(){
    return terrain;
}