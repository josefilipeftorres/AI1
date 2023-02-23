#include <iostream>
#include <fstream>
#include <string>
#include "Game.h" // Create a Game class

using namespace std;

const int SIZE = 4;

Game readConfigFile(char* inputFile);
bool checkIfSolvable(Game initConf, Game goalConf);


int main(int argc, char* argv[])
{
    // Check for correct number of arguments
    if (argc == 1 || argc > 3) {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    // Read the initial configuration file
    Game initConf = readConfigFile(argv[1]);
    Game goalConf(SIZE);

    // Read the goal configuration file
    if (argc == 3) {
        // Pode-se definir a goalConf como default (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0) e caso haja um ficheiro de goalConf, substituir a default
        goalConf = readConfigFile(argv[2]);
    }

    // Check if its solvable
    if (!checkIfSolvable(initConf, goalConf)) {
        printf("The initial configuration is not solvable!\n");
        return 1;
    }

    return 0;
}


Game readConfigFile(char* confFile) {
    // Open the file
    ifstream inputFile(confFile);

    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error opening file " << confFile << "\n";
        exit(1);
    }

    // Create a new Game object
    Game game(SIZE);
    
    // Read the configuration file
    int value;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inputFile >> value;
            game.addValue(i,j, value);
        }
    }

    inputFile.close();
    return game;
}

bool checkIfSolvable(Game initConf, Game goalConf) {
    return initConf.solvability() == goalConf.solvability();
}