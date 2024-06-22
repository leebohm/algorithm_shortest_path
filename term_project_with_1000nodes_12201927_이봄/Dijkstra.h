#pragma once
// Dijkstra.h

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <queue>
#include <climits>

using namespace std;


extern const long long NUM_NODE;
extern int goal_node;
typedef pair<int, int> Node;
extern vector<long long> answer_dij;


class DijkstraAlgorithm {
private:
    vector<std::vector<long long>> graph;
    vector<bool> s;
    vector<long long> dist;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    

public:
    DijkstraAlgorithm(const vector<vector<long long>>& g);
    void runDijkstra();
    void printShortestPaths() const;
    
};

#endif // DIJKSTRA_H