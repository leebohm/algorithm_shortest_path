// Dijkstra.cpp
#include "dijkstra.h"
#include <iostream>

using namespace std;


DijkstraAlgorithm::DijkstraAlgorithm(const vector<vector<long long>>& g)
	: graph(g), s(NUM_NODE, false), dist(NUM_NODE, INT_MAX) {}

void DijkstraAlgorithm::runDijkstra() {
    dist[0] = 0;
    pq.push({ 0, 0 });

    while (!pq.empty()) {
        int current = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();

        if (s[current]) continue;
        s[current] = true;

        for (int next = 0; next < NUM_NODE; next++) {
            if (graph[current][next] != INT_MAX) {
                int new_dist = current_dist + graph[current][next];
                if (new_dist < dist[next]) {
                    dist[next] = new_dist;
                    pq.push({ new_dist, next });
                }
            }
        }
    }
    printShortestPaths();
}

void DijkstraAlgorithm::printShortestPaths() const {
	cout << "���۳�尡 ��� 0�� �� ��ǥ ��� "  << goal_node << "������ �ִ� ��� ���� " << endl << endl;
	/*
    for (int i = 0; i < NUM_NODE; i++) {
		if (dist[i] == INT_MAX) {
			cout << i << "�� ��� : INF" << endl;
		}
		else {
			cout << i << "�� ��� : " << dist[i] << endl;
		}
	}
    */
    
    cout << goal_node  << "�� ��� : " << dist[goal_node] << endl;
    answer_dij.push_back(dist[goal_node]);
    //cout << graph[0][goal_node - 1] << endl;
}
