#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
using namespace std;


class Game {

    public:
        Game(int size);
        void addValue(int i, int j, int value);
        void printBoard();
        bool solvability();
        bool compareBoards(Game goalConf);
        vector<Game> possibleMoves();
    
    private:
        int board[4][4];
        // string moves[4] = {"up", "down", "left", "right"};
        vector<int> pieces;
        int rows;
        int cols;
        int blankX;
        int blankY;
};

#endif