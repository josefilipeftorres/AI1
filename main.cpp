#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stdlib.h>

#include "Game.h"  // Create a Game class

using namespace std;

const int SIZE = 4;

void readConfigFile(char* inputFile, Game* initConf, Game* goalConf);
bool checkIfSolvable(Game* initConf, Game* goalConf);
void debugBoard(Game* initConf, Game* goalConf);
void BFS(Game* initConf, Game* goalConf);

int main(int argc, char* argv[]) {
    system("clear"); 

    // Check for correct number of arguments
    if (argc == 1 || argc > 3) {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    // Get the algorithm to run
    string algorithm = argv[1];

    // Read the configuration file
    Game* initConf = new Game(SIZE);
    Game* goalConf = new Game(SIZE);
    readConfigFile(argv[2], initConf, goalConf);

    // debugBoard(initConf, goalConf);

    // Check if its solvable
    if (!checkIfSolvable(initConf, goalConf)) {
        printf("The initial configuration is not solvable!\n");
        return 1;
    }

    // debugBoard(initConf, goalConf);

    // Run the algorithm
    if (algorithm == "BFS") {
        BFS(initConf, goalConf);
    } else {
        printf("Invalid algorithm!\n");
        return 1;
    }

    return 0;
}

void readConfigFile(char* confFile, Game* initConf, Game* goalConf) {
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
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            initConf->setPiece(i, j, init.front());
            goalConf->setPiece(i, j, goal.front());

            init.erase(init.begin());
            goal.erase(goal.begin());
        }
    }
    inputFile.close();
}

bool checkIfSolvable(Game* initConf, Game* goalConf) {
    return initConf->solvability() == goalConf->solvability();
}

void debugBoard(Game* initConf, Game* goalConf) {
    
    printf("Initial configuration:\n");
    // initConf->setVisited();
    initConf->printBoard();
    printf("%d\n", initConf->isVisited());
    
    printf("--------------------\n");
    
    printf("Goal configuration:\n");
    goalConf->printBoard();

    printf("--------------------\n");

    // printf("Possible moves:\n");
    // vector<Game*> possibleMoves = initConf->possibleMoves();

    // for (int i = 0; i < possibleMoves.size(); i++) {
    //     printf("--------------------\n");
    //     possibleMoves[i]->printBoard();
    //     cout << possibleMoves[i]->getPath() << " " << possibleMoves[i]->isVisited() << endl;
    // }
}

void BFS(Game* initConf, Game* goalConf) {
    queue<Game*> q;
    q.push(initConf);
    initConf->setVisited();

    GameData data;
    // data.printData();
    
    while(!q.empty()) {
        // Get the next node and remove it from the queue to evaluate
        Game* cur = q.front();
        q.pop();
        data.incrementExpandedNodes();

        // Check if the current node is the goal node
        if(cur->compareBoards(*goalConf)) {
            printf("Found the goal configuration!\n");
            cur->printBoard();
            data.setPath(cur->getPath());
            data.printData();
            return;
        }
        
        // cout << cur->getPath() << endl;
        // printf("Current node:\n");
        // cur->printBoard();
        // printf("--------------------\n");
        
        // Get the possible moves from the current node
        vector<Game*> possibleMoves = cur->possibleMoves();
        // Debug for possibleMoves
        
        // for (int i = 0; i < possibleMoves.size(); i++) {
        //     vector<Game*> p = possibleMoves[i]->possibleMoves();
        //     printf("Current node:\n");
        //     possibleMoves[i]->printBoard();
        //     printf("Visited: %d\n", possibleMoves[i]->isVisited());
        //     printf("--------------------\n");
        //     for (int j = 0; j < p.size(); j++) {
        //         p[j]->printBoard();
        //         printf("Visited: %d\n", p[j]->isVisited());
        //         printf("--------------------\n");
        //     }
        // }
        // return;
    
        for (int i = 0; i < possibleMoves.size(); i++) {
            Game* nextMove = possibleMoves[i];
            if (!nextMove->isVisited()) {
                nextMove->setVisited();
                q.push(nextMove);
                data.incrementMemoryUsed();
            } else {
                delete nextMove;
            }
        }
    }
}
