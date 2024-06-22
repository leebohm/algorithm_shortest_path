#include "AStar.h"
#include "Dijkstra.h"
#include "GA.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;


// ���� ���� ����
const int MAX_WEIGHT = 15; // �ִ� ����ġ

const long long NUM_NODE = 50;
const int POPULATION_SIZE = 500;
const int GENERATIONS = 2000;
const double MUTATION_RATE = 0.01;
int start_node = 0;
int goal_node = 49;


// �׷��� ���� �Լ�

vector<vector<long long>> createGraph1() {
	vector<vector<long long>> graph(NUM_NODE, vector<long long>(NUM_NODE, INT_MAX));

	// ���ǳ�Ʈ 64 �������� ������ �׷���
	graph[0][1] = 8;
	graph[0][2] = 9;
	graph[0][3] = 11;
	graph[1][4] = 10;
	graph[2][1] = 6;
	graph[2][3] = 3;
	graph[2][4] = 1;
	graph[3][5] = 8;
	graph[3][6] = 8;
	graph[4][7] = 2;
	graph[5][2] = 12;
	graph[5][7] = 5;
	graph[6][5] = 7;
	graph[7][6] = 4;

	// ���� ������ ��δ� 0���� ����
	for (int i = 0; i < NUM_NODE; i++) {
		graph[i][i] = 0;
	}
	return graph;
}


vector<vector<long long>> createGraph2() {
	vector<vector<long long>> graph(NUM_NODE, vector<long long>(NUM_NODE, INT_MAX));

	// �������� ������ �߰�
	srand(time(0)); // ���� �ʱ�ȭ

	for (int i = 0; i < NUM_NODE; i++) {
		for (int j = 0; j < NUM_NODE; j++) {
			if (i != j) {
				// 20% Ȯ���� ������ �߰�
				if (rand() % 100 < 20) {
					graph[i][j] = rand() % MAX_WEIGHT + 10; // 1���� MAX_WEIGHT������ ����ġ
				}
			}
		}
	}

	// ���� ������ ��δ� 0���� ����
	for (int i = 0; i < NUM_NODE; i++) {
		graph[i][i] = 0;
	}

	graph[0][goal_node] = INT_MAX;

	return graph;
}


int main() {

	double elapsed_dij = 0.0;
	double elapsed_astar = 0.0;
	double elapsed_ga = 0.0;

	for (int i = 0; i < 5; i++) {
		// 1. Dijkstra 
	// �׷��� ����
		vector<vector<long long>> graph = createGraph2();

		// ���� �ð� ���
		
		clock_t start_time_dij = clock();

		// DijkstraAlgorithm ��ü ����
		DijkstraAlgorithm dijkstra(graph);

		// �˰��� ����
		cout << "================================================" << endl;
		cout << "Dijkstra �˰��� ���� " << endl;
		dijkstra.runDijkstra();

		// ���� �ð� ���
		clock_t end_time_dij = clock();

		// ���� �ð� ���
		elapsed_dij += double(end_time_dij - start_time_dij) / CLOCKS_PER_SEC * 1000; // �и��� ����

		//////////////////////////////////////////////////////////////////

		// 2. AStar


		// AStar ��ü ����
		cout << endl;
		cout << "================================================" << endl;
		cout << "A* �˰��� ����" << endl;

		// ���� �ð� ���
		clock_t start_time_astar = clock();

		AStar astar(graph);

		// ���� ���� ��ǥ ��� ����

		astar.RunAStar(start_node, goal_node);

		// ���� �ð� ���
		clock_t end_time_astar = clock();

		// ���� �ð� ���
		elapsed_astar += double(end_time_astar - start_time_astar) / CLOCKS_PER_SEC * 1000; // �и��� ����

		//////////////////////////////////////////////////////////////////

		// 3. Genetic Algotirhm
		srand(time(0));
		cout << endl;
		cout << "================================================" << endl;
		// ���� �ð� ���
		// ���� �ð� ���
		
		clock_t start_time_ga = clock();

		cout << "GA ����" << endl << endl;
		GeneticAlgorithm ga(graph);
		ga.Run();

		cout << endl;

		// ���� �ð� ���
		clock_t end_time_ga = clock();

		// ���� �ð� ���
		elapsed_ga += double(end_time_ga - start_time_ga) / CLOCKS_PER_SEC * 1000; // �и��� ����
	
	
	




    return 0;
}