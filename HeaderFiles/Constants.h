#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
using namespace std;


const char ENEMY = 'E';
const char PLAYER = 'P';
const char PATH = 'T';
const char WALL = 'W';
const char DIRT = 'D';
const char SECRET_PASSAGE = 'S';

const int MAX_ROWS = 100;
const int MAX_COLS = 100;
const int MAX_VERTICES = MAX_ROWS * MAX_COLS;

const int ENEMY_STOP_DISTANCE = 1;

// Color definitions
const string COLOR_PLAYER = "\033[32m";
const string COLOR_ENEMY = "\033[31m";
const string COLOR_PATH = "\033[97m";
const string COLOR_DIRT = "\033[38;5;94m";
const string COLOR_SECRET = "\033[35m";
const string COLOR_WALL = "\033[38;5;214m";
const string COLOR_RESET = "\033[0m";

#endif // CONSTANTS_H
