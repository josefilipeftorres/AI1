#ifndef GAME_H
#define GAME_H
#include <vector>
using namespace std;


class Game {

    public:
        Game(int size);
        void addValue(int i, int j, int value);
        void printBoard();
        void blankRow();
        bool solvability();
        bool compareBoards(Game goalConf);
        vector<Game> possibleMoves();
    
    private:
        int board[4][4];
        int rows;
        int cols;
        int blankRowIndx;
        int blankX;
        int blankY;
};

#endif