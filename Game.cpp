#include "Game.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

Game::Game(int size) {
    this->rows = size;
    this->cols = size;
    this->blankX = 0;
    this->blankY = 0;

    int k = 1;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            board[i][j] = k++;
        }
    }
    board[this->rows - 1][this->cols - 1] = 0;
    // this->visited = false;
}

Game::Game(const Game& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->blankX = other.blankX;
    this->blankY = other.blankY;
    
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            this->board[i][j] = other.board[i][j];
        }
    }
    this->path = other.path;
    // this->visited = other.visited;
    this->parent = other.parent;
}

void Game::printBoard() {
    int maxDigits = 1;
    int maxValue = this->rows * this->cols;
    
    while (maxValue >= 10) {
        maxDigits++;
        maxValue /= 10;
    }

    for (int i = 0; i < this->rows; i++) {
        cout << "| ";
        for (int j = 0; j < this->cols; j++) {
            int num = this->board[i][j];
            int numDigits = 1;
            while (num >= 10) {
                numDigits++;
                num /= 10;
            }
            int numSpaces = maxDigits - numDigits;
            for (int k = 0; k < numSpaces; k++) {
                cout << " ";
            }
            cout << this->board[i][j] << " ";
        }
        cout << "|\n";
    }
}

void Game::setPiece(int i, int j, int value) {
    this->board[i][j] = value;
    this->pieces.push_back(value);
    if (value == 0) {
        this->blankX = i;
        this->blankY = j;
    }
}

bool Game::solvability() {
    int inversions = 0;
    
    // for(int i: this->pieces)
    //     printf("%d ", i);
    // printf("\n");
    
    for (int i = 0; i < this->pieces.size(); i++) {
        if (this->pieces[i] == 0)
            continue;
        int count = 0;
        for (int j = i + 1; j < this->pieces.size(); j++) {
            if (this->pieces[j] == 0)
                continue;
            if (this->pieces[i] > this->pieces[j])
                count++;
        }
        inversions += count;
    }
    // printf("inversions: %d\n", inversions);
    // printf("blankX: %d\n", this->rows - this->blankX);
    return (inversions % 2 == 0) == ((this->rows - this->blankX) % 2 == 1);
}

bool Game::compareBoards(const Game& other) const {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (this->board[i][j] != other.board[i][j])
                return false;
        }
    }
    return true;
}

vector<Game*> Game::possibleMoves() {
    vector<Game*> moves;

    int x = this->blankX;
    int y = this->blankY;
    
    /*
    vector<pair<int,int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto& dir: directions) {
        int newBlankX = x + dir.first;
        int newBlankY = y + dir.second;

        if (newBlankX >= 0 && newBlankX < rows && newBlankY >= 0 && newBlankY < cols) { 
            // Create a new object to represent the move
            Game* newGame = new Game(*this);

            // Swap the blank piece with the piece in the direction
            newGame->swap(x, y, newBlankX, newBlankY);

            // Set the parent of the new game to the current game
            newGame->setParent(this);

            // Update the blank position
            newGame->updateBlankPosition(newBlankX, newBlankY);

            // Add the new game to the list of possible moves
            moves.push_back(newGame);
        }
    }
    */
    
    // Move blank piece up
    if (x > 0) {
        Game* up = new Game(*this);
        up->swap(x, y, x - 1, y);
        up->updateBlankPosition(x - 1, y);
        up->path += 'U';
        moves.push_back(up);
    }

    // Move blank piece down
    if (x < rows - 1) { 
        Game* down = new Game(*this);
        down->swap(x, y, x + 1, y);
        down->updateBlankPosition(x + 1, y);
        down->path += 'D';
        moves.push_back(down);
    }

    // Move blank piece left
    if (y > 0) {
        Game* left = new Game(*this);
        left->swap(x, y, x, y - 1);
        left->updateBlankPosition(x, y - 1);
        left->path += 'L';
        moves.push_back(left);
    }

    // Move blank piece right
    if (y < cols - 1) {
        Game* right = new Game(*this);
        right->swap(x, y, x, y + 1);
        right->updateBlankPosition(x, y + 1);
        right->path += 'R';
        moves.push_back(right);
    }
    return moves;
}

void Game::swap(int x1, int y1, int x2, int y2) {
    int temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;
}

void Game::updateBlankPosition(int x, int y) {
    this->blankX = x;
    this->blankY = y;
}

void Game::setVisited() {
    this->visited = true;
}

bool Game::isVisited() {
    return this->visited;
}

void Game::setParent(Game* parent) {
    this->parent = parent;
}

Game* Game::getParent() {
    return this->parent;
}

string Game::getPath() {
    return this->path;
}

void Game::setPath(string p) {
    this->path = p;
}


/*
    GameData
*/

GameData::GameData() {
    this->expandedNodes = 0;
    this->memoryUsed = 0;
    this->path = "";
    this->startTime = clock();
}

void GameData::printData() {
    printf("Steps: %d\n", this->path.size());
    string path_copy = this->path;
    printf("Path: %s\n", path_copy.c_str());
    printf("Expanded Nodes: %d\n", this->expandedNodes);
    printf("Memory Used: %d\n", this->memoryUsed);
    printf("Time Taken: %fs\n", ((float)(clock() - this->startTime)) / CLOCKS_PER_SEC);
}

void GameData::incrementExpandedNodes() {
    this->expandedNodes++;
}

int GameData::getExpandedNodes() const {
    return expandedNodes;
}

void GameData::incrementMemoryUsed() {
    this->memoryUsed++;
}

int GameData::getMemoryUsed() const {
    return this->memoryUsed;
}

void GameData::setPath(string path) {
    this->path += path;
}

string GameData::getPath() const {
    return this->path;
}
