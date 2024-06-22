#pragma once

// AStar.h
#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <queue>
#include <climits>

using namespace std;

extern vector<long long> answer_astar;
extern const long long  NUM_NODE;

struct Node_AStar {
    int vertex;
    long long gCost;
    long long fCost;
    bool operator>(const Node_AStar& other) const {
        return fCost > other.fCost;
    }
};

class AStar {
private:
    vector<vector<long long>> graph;
    vector<bool> visited;
    vector<long long> heuristic_cost;

    void InitVisited();
    void CalHeuristic();
    

public:
    AStar(const vector<vector<long long>>& g);
    void RunAStar(int start, int goal);
    void PrintHeuristic() const;
    void PrintPath(const vector<long long>& parent, int start, int goal, long long pathCost) const;
};

#endif // ASTAR_H
