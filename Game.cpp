#include "Game.h"

#include <iostream>
#include <vector>

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

void Game::addValue(int i, int j, int value) {
    this->board[i][j] = value;
    this->pieces.push_back(value);
    if (value == 0) {
        this->blankX = i;
        this->blankY = j;
    }
}

bool Game::solvability() {
    int inversions = 0;
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

bool Game::compareBoards(Game goalConf) {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (this->board[i][j] != goalConf.board[i][j])
                return false;
        }
    }
    return true;
}

vector<Game> Game::possibleMoves() {
    vector<Game> moves;
    Game move = *this;
    int x = this->blankX;
    int y = this->blankY;

    if (x > 0 && x < this->rows - 1) {
        Game upMove = *this;
        upMove.board[x][y] = upMove.board[x - 1][y];
        upMove.board[x - 1][y] = 0;
        moves.push_back(upMove);
    }

    if (x < this->rows - 1 && x > 0) {
        Game downMove = *this;
        downMove.board[x][y] = downMove.board[x + 1][y];
        downMove.board[x + 1][y] = 0;
        moves.push_back(downMove);
    }

    if (y > 0 && y < this->cols - 1) {
        Game leftMove = *this;
        leftMove.board[x][y] = leftMove.board[x][y - 1];
        leftMove.board[x][y - 1] = 0;
        moves.push_back(leftMove);
    }

    if (y < this->cols - 1 && y > 0) {
        Game rightMove = *this;
        rightMove.board[x][y] = rightMove.board[x][y + 1];
        rightMove.board[x][y + 1] = 0;
        moves.push_back(rightMove);
    }

    return moves;
}