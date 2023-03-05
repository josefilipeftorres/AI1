#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Game {

    public:
        Game(int size);
        Game(const Game& other);
        
        // bool compareBoards(const Game& other) const;
        bool compareBoards(Game* other);
        vector<Game*> possibleMoves();
        void swap(int x1, int y1, int x2, int y2);
        void updateBlankPosition(int x, int y);
        void hashMaker();
        size_t getId();

        bool solvability();
        void setPiece(int i, int j, int value);
        
        // void setVisited();
        // bool isVisited();
        
        // void setParent(Game* parent);
        // Game* getParent();
        string getPath();
        void setPath(string p);
        void printBoard();

        int misplacedTiles(Game* goal); 
        void setH(int h);   // Heuristic function
        void setG(int g);   // Cost to reach this node (number of moves made so far)
        int getG();          
        void setF(int f);   // f(n) = g(n) + h(n)
        int getF(); 
        int getH();

        int manhattanDistance(Game* goal);        
        
    private:
        int board[4][4];
        // bool visited;
        vector<int> pieces;
        int id;
        int rows, cols;
        int blankX, blankY;
        string path;
        // Game* parent;
        int h, g, f;

};
#endif