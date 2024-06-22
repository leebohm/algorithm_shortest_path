#include "AStar.h"
#include "Dijkstra.h"
#include "GA.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;


// 전역 변수 정의
const int MAX_WEIGHT = 15; // 최대 가중치

const long long NUM_NODE = 50;
const int POPULATION_SIZE = 500;
const int GENERATIONS = 2000;
const double MUTATION_RATE = 0.01;
int start_node = 0;
int goal_node = 49;


// 그래프 생성 함수

vector<vector<long long>> createGraph1() {
	vector<vector<long long>> graph(NUM_NODE, vector<long long>(NUM_NODE, INT_MAX));

	// 강의노트 64 페이지에 나오는 그래프
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

	// 동일 노드로의 경로는 0으로 설정
	for (int i = 0; i < NUM_NODE; i++) {
		graph[i][i] = 0;
	}
	return graph;
}


vector<vector<long long>> createGraph2() {
	vector<vector<long long>> graph(NUM_NODE, vector<long long>(NUM_NODE, INT_MAX));

	// 무작위로 간선을 추가
	srand(time(0)); // 난수 초기화

	for (int i = 0; i < NUM_NODE; i++) {
		for (int j = 0; j < NUM_NODE; j++) {
			if (i != j) {
				// 20% 확률로 간선을 추가
				if (rand() % 100 < 20) {
					graph[i][j] = rand() % MAX_WEIGHT + 10; // 1부터 MAX_WEIGHT까지의 가중치
				}
			}
		}
	}

	// 동일 노드로의 경로는 0으로 설정
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
	// 그래프 생성
		vector<vector<long long>> graph = createGraph2();

		// 시작 시간 기록
		
		clock_t start_time_dij = clock();

		// DijkstraAlgorithm 객체 생성
		DijkstraAlgorithm dijkstra(graph);

		// 알고리즘 실행
		cout << "================================================" << endl;
		cout << "Dijkstra 알고리즘 실행 " << endl;
		dijkstra.runDijkstra();

		// 종료 시간 기록
		clock_t end_time_dij = clock();

		// 실행 시간 계산
		elapsed_dij += double(end_time_dij - start_time_dij) / CLOCKS_PER_SEC * 1000; // 밀리초 단위

		//////////////////////////////////////////////////////////////////

		// 2. AStar


		// AStar 객체 생성
		cout << endl;
		cout << "================================================" << endl;
		cout << "A* 알고리즘 실행" << endl;

		// 시작 시간 기록
		clock_t start_time_astar = clock();

		AStar astar(graph);

		// 시작 노드와 목표 노드 설정

		astar.RunAStar(start_node, goal_node);

		// 종료 시간 기록
		clock_t end_time_astar = clock();

		// 실행 시간 계산
		elapsed_astar += double(end_time_astar - start_time_astar) / CLOCKS_PER_SEC * 1000; // 밀리초 단위

		//////////////////////////////////////////////////////////////////

		// 3. Genetic Algotirhm
		srand(time(0));
		cout << endl;
		cout << "================================================" << endl;
		// 시작 시간 기록
		// 시작 시간 기록
		
		clock_t start_time_ga = clock();

		cout << "GA 실행" << endl << endl;
		GeneticAlgorithm ga(graph);
		ga.Run();

		cout << endl;

		// 종료 시간 기록
		clock_t end_time_ga = clock();

		// 실행 시간 계산
		elapsed_ga += double(end_time_ga - start_time_ga) / CLOCKS_PER_SEC * 1000; // 밀리초 단위
	
	
	




    return 0;
}