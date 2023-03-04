#include "GameData.h"

#include <iostream>
#include <vector>
#include <string>

GameData::GameData() {
    this->expandedNodes = 0;
    this->memoryUsed = 0;
    this->path = "";
    this->startTime = clock();
}

void GameData::printData() {
    printf("Steps: %lu\n", this->path.size());
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
