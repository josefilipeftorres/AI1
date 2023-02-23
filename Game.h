#ifndef GAME_H
#define GAME_H
#include <vector>

class Game {

    public:
        Game(int size);
        void addValue(int i, int j, int value);
        void printBoard();
        void blankRow();
        bool solvability();
    
    private:
        int** board;
        int rows;
        int cols;
        int blankRowIndx;
};

#endif