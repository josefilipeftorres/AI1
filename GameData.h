#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>

using namespace std;

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