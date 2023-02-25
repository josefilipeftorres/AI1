#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Game.h"  // Create a Game class

using namespace std;

const int SIZE = 4;

void readConfigFile(char* inputFile, Game& initConf, Game& goalConf);
bool checkIfSolvable(Game initConf, Game goalConf);
void debugBoard(Game initConf, Game goalConf);

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc == 1 || argc > 2) {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    // Read the configuration file
    Game initConf(SIZE);
    Game goalConf(SIZE);
    readConfigFile(argv[1], initConf, goalConf);
    
    // debugBoard(initConf, goalConf);

    // Check if its solvable
    if (!checkIfSolvable(initConf, goalConf)) {
        printf("The initial configuration is not solvable!\n");
        return 1;
    }

    debugBoard(initConf, goalConf);

    // Print all possible moves
    /*printf("Initial configuration:\n");
    initConf.printBoard();
    printf("Goal configuration:\n");
    goalConf.printBoard();
    printf("--------------------\n");
    printf("Possible moves:\n");
    vector<Game> possibles = initConf.possibleMoves();
    for (int i = 0; i < possibles.size(); i++) {
        printf("--------------------\n");
        possibles[i].printBoard();
    }
    */

    return 0;
}

void readConfigFile(char* confFile, Game& initConf, Game& goalConf) {
    // Open the file
    ifstream inputFile(confFile);

    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error opening file " << confFile << "\n";
        exit(1);
    }

    // Read the file
    string lineINIT, lineGOAL;
    getline(inputFile, lineINIT);
    getline(inputFile, lineGOAL);

    // Parse the file
    stringstream ssINIT(lineINIT);
    stringstream ssGOAL(lineGOAL);

    // Read the initial configuration
    vector<int> init;
    int num = 0;
    while (ssINIT >> num) {
        init.push_back(num);
    }

    // Read the goal configuration
    vector<int> goal;
    while (ssGOAL >> num) {
        goal.push_back(num);
    }

    // Add the values to the board
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) {
            initConf.addValue(i, j, init.front());
            goalConf.addValue(i, j, goal.front());

            init.erase(init.begin());
            goal.erase(goal.begin());
        }

    inputFile.close();
}

bool checkIfSolvable(Game initConf, Game goalConf) {
    return initConf.solvability() == goalConf.solvability();
}

void debugBoard(Game initConf, Game goalConf) {
    printf("Initial configuration:\n");
    initConf.printBoard();
    printf("--------------------\n");
    printf("Goal configuration:\n");
    goalConf.printBoard();
}
// depth-first search algorithm for solving the 15-puzzle
/*void DFS(Game initConf, Game goalConf) {
    int moves = 1;
    stack<Game> stack;
    stack.push(initConf);
    //while the stack is not empty
    while (!stack.empty()) {
        //pop the top node from the stack
        Game cur = stack.top();
        stack.pop();
        //if the node is the goal configuration
        if (cur.compareBoards(goalConf)) {
            cout << moves << endl;
        }
        //else
        else {
            //create a vector of nodes with the possible moves
            vector<Node> possibleMoves = node.possibleMoves();
            //for each node in the vector
            for (int i = 0; i < possibleMoves.size(); i++) {
                //push the node into the stack
                stack.push(possibleMoves[i]);
            }
        }
    }
}*/