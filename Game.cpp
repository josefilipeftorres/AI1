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
        for(int j = 0; j < this->cols; j++) {
            board[i][j] = k++;
        }
    }
    board[this->rows-1][this->cols-1] = 0;
    
}

void Game::printBoard() {
    for (int i = 0; i < this->rows; i++) {
        printf("| ");
        for (int j = 0; j < this->cols; j++) {
            printf("%d ", this->board[i][j]);
        }
        printf("|\n");
    }
}

void Game::addValue(int i, int j, int value) {
    this->board[i][j] = value;
    if(value == 0) {
        this->blankX = i;
        this->blankY = j;
        //this->blankRowIndx = this->rows - i;
    }
}

// void Game::blankRow() {
//     for (int i = 0; i < this->rows; i++) {
//         for (int j = 0; j < this->cols; j++) {
//             if (this->board[i][j] == 0) {
//                 this->blankRowIndx = this->rows - i;
//             }
//         }
//     }
// }

bool Game::solvability() {
    int inversions = 0;
    int piece = 1;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (piece++ != this->board[i][j] && this->board[i][j] != 0)
                inversions++;
        }
    }

    //this->blankRow();
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
    move.printBoard();
    int x = this->blankX;
    int y = this->blankY;
    cout << "blankX: " << x << " blankY: " << y << endl;

    if (x > 0 && x < this->rows-1) {
        move.board[x][y] = move.board[x-1][y];
        move.board[x-1][y] = 0;
        moves.push_back(move);
    }

    if (x < this->rows-1 && x > 0) {
        move.board[x][y] = move.board[x+1][y];
        move.board[x+1][y] = 0;
        moves.push_back(move);
    }

    if (y > 0 && y < this->cols-1) {
        move.board[x][y] = move.board[x][y-1];
        move.board[x][y-1] = 0;
        moves.push_back(move);
    }

    if (y < this->cols-1 && y > 0) {
        move.board[x][y] = move.board[x][y+1];
        move.board[x][y+1] = 0;
        moves.push_back(move);
    }

    return moves;
}