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
        
        bool compareBoards(const Game& other) const;
        vector<Game*> possibleMoves();
        void swap(int x1, int y1, int x2, int y2);
        void updateBlankPosition(int x, int y);
        void hashMaker();
        size_t getId();

        bool solvability();
        void setPiece(int i, int j, int value);
        
        void setVisited();
        bool isVisited();
        
        void setParent(Game* parent);
        Game* getParent();
        string getPath();
        void setPath(string p);
        void printBoard();
        
    private:
        int board[4][4];
        bool visited;
        vector<int> pieces;
        int id;
        int rows, cols;
        int blankX, blankY;
        string path;
        Game* parent;
};

class GameData {
    public:
        GameData();
        void printData();
        
        void incrementExpandedNodes();
        int getExpandedNodes() const;
        
        void incrementMemoryUsed();
        int getMemoryUsed() const;
        
        void setPath(string path);
        string getPath() const;

    private:
        int expandedNodes;
        int memoryUsed;
        clock_t startTime;
        string path;
};

#endif