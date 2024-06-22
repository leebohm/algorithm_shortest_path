// AStar.cpp
#include "AStar.h"
#include <iostream>
#include <algorithm>

using namespace std;


extern int goal_node;

AStar::AStar(const vector<vector<long long>>& g) : graph(g), visited(NUM_NODE), heuristic_cost(NUM_NODE) {
    CalHeuristic();
}

void AStar::InitVisited() {
    fill(visited.begin(), visited.end(), false);
}

void AStar::CalHeuristic() {
    cout << endl;
    cout << "Heuristic cost 계산" << endl;

    for (int i = 0; i < NUM_NODE; i++) {
        InitVisited();
        int total_dist = 0;

        int next_node = i;
        visited[i] = true;
        for (int k = 0; k < NUM_NODE; k++) {
            if (next_node == goal_node) break;
            int min_dist = INT_MAX;
            int tmp_node = next_node;
            for (int j = 0; j < NUM_NODE; j++) {
                if (next_node != j) {
                    int tmp_dist = graph[next_node][j];
                    if (tmp_dist < min_dist && !visited[j] && tmp_dist != INT_MAX) {
                        min_dist = tmp_dist;
                        tmp_node = j;
                    }
                }
            }
            if (min_dist != INT_MAX) {
                next_node = tmp_node;
                visited[next_node] = true;
                total_dist += min_dist;
            }
        }
    
        heuristic_cost[i] = total_dist;
    }
    // PrintHeuristic();
}

void AStar::PrintHeuristic() const {
    for (int i = 0; i < NUM_NODE; i++) {
        cout << "h[" << i << "] : " << heuristic_cost[i] << "  ";
    }
    cout << endl << endl;
}

void AStar::PrintPath(const vector<long long>& parent, int start, int goal, long long pathCost) const {
   
    cout << "노드 " << start << "에서 노드 " << goal << "까지의 최단 경로: ";
    vector<long long> path;
    for (int at = goal; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << endl;
    cout << "최단 경로 길이: " << pathCost << endl;
    answer_astar.push_back(pathCost);

    int num = path.size();
    for (int i = 0; i < num - 1; i++)
        cout << graph[path[i]][path[i+1]] << " ";
}

void AStar::RunAStar(int start, int goal) {
    vector<int> gCost(NUM_NODE, INT_MAX);
    vector<long long> parent(NUM_NODE, -1);
    priority_queue<Node_AStar, vector<Node_AStar>, greater<Node_AStar>> pq_AStar;

    gCost[start] = 0;
    pq_AStar.push({ start, 0, heuristic_cost[start] });

    while (!pq_AStar.empty()) {
        Node_AStar current = pq_AStar.top();
        pq_AStar.pop();

        if (current.vertex == goal) break;

        for (int neighbor = 0; neighbor < NUM_NODE; neighbor++) {
            if (graph[current.vertex][neighbor] != INT_MAX) {
                int tentative_gCost = gCost[current.vertex] + graph[current.vertex][neighbor];
                if (tentative_gCost < gCost[neighbor]) {
                    gCost[neighbor] = tentative_gCost;
                    int fCost = tentative_gCost + heuristic_cost[neighbor];
                    pq_AStar.push({ neighbor, tentative_gCost, fCost });
                    parent[neighbor] = current.vertex;
                }
            }
        }
    }

    if (gCost[goal] == INT_MAX) {
        cout << "경로가 없음." << endl;
    }
    else {
        PrintPath(parent, start, goal, gCost[goal]);
    }
}
