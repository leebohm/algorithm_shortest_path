// GA.cpp
#include "GA.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


GeneticAlgorithm::GeneticAlgorithm(const vector<vector<long long>>& g) : graph(g) {
    nodeList.resize(NUM_NODE);
    iota(nodeList.begin(), nodeList.end(), 0);
}

void GeneticAlgorithm::InitPopulation(vector<Path>& population) {
    bool pathFound = false;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        Path path;
        path.nodes.push_back(start_node);

        int current = start_node;
        while (current != goal_node) {
            vector<int> neighbors;
            for (int j = 0; j < NUM_NODE; j++) {
                if (graph[current][j] != INT_MAX && j != current &&
                    find(path.nodes.begin(), path.nodes.end(), j) == path.nodes.end()) {
                    neighbors.push_back(j);
                }
            }

            if (neighbors.empty()) break;
            int next = neighbors[rand() % neighbors.size()];
            path.nodes.push_back(next);
            current = next;
        }

        if (current == goal_node) {
            pathFound = true;
            path.fitness = CalFitness(path);
            population.push_back(path);
        }
    }

    if (!pathFound) {
        cout << "경로가 없습니다." << endl;
        exit(1); // Exit if no path found
    }
}

long long GeneticAlgorithm::CalFitness(const Path& path) {
    long long fitness = 0;
    for (size_t i = 0; i < path.nodes.size() - 1; i++) {
        fitness += graph[path.nodes[i]][path.nodes[i + 1]];
    }
    return fitness;
}

void GeneticAlgorithm::EvalPopulation(vector<Path>& population) {
    vector<int> to_remove;

    for (int i = 0; i < population.size(); i++) {
        population[i].fitness = CalFitness(population[i]);
        if (population[i].fitness < 0 || population[i].fitness > MAX_WEIGHT * 100) {
            to_remove.push_back(i);
        }
    }

    for (int i = to_remove.size() - 1; i >= 0; i--) {
        population.erase(population.begin() + to_remove[i]);
    }

    sort(population.begin(), population.end());
}

Path GeneticAlgorithm::SelectParent(const vector<Path>& population) {
    long long totalFitness = 0;
    for (const auto& path : population) {
        totalFitness += path.fitness;
    }

    if (totalFitness == 0) {
        if (population.size() != 0)
            return population[rand() % population.size()];
        else
            return population[0];
    }
    int randomValue = rand() % 100;
    long long tmp_Sum = 0;
    for (const auto& path : population) {
        tmp_Sum += path.fitness;
        if (tmp_Sum > randomValue) {
            return path;
        }
    }
    return population[0];
}

Path GeneticAlgorithm::Crossover(const Path& parent1, const Path& parent2) {
    Path child;
    child.nodes.push_back(start_node);

    set<int> used_nodes;
    used_nodes.insert(start_node);

    while (child.nodes.back() != goal_node) {
        int current = child.nodes.back();
        vector<int> candidates;

        if (find(parent1.nodes.begin(), parent1.nodes.end(), current) != parent1.nodes.end()) {
            auto it = find(parent1.nodes.begin(), parent1.nodes.end(), current);
            if (next(it) != parent1.nodes.end()) candidates.push_back(*next(it));
        }
        if (find(parent2.nodes.begin(), parent2.nodes.end(), current) != parent2.nodes.end()) {
            auto it = find(parent2.nodes.begin(), parent2.nodes.end(), current);
            if (next(it) != parent2.nodes.end()) candidates.push_back(*next(it));
        }

        int next_node = -1;
        for (int candidate : candidates) {
            if (used_nodes.find(candidate) == used_nodes.end()) {
                next_node = candidate;
                break;
            }
        }

        if (next_node == -1) {
            for (int i = 0; i < NUM_NODE; i++) {
                if (graph[current][i] != INT_MAX && used_nodes.find(i) == used_nodes.end()) {
                    next_node = i;
                    break;
                }
            }
        }

        if (next_node == -1) {
            child.nodes.push_back(goal_node);
        }
        else {
            child.nodes.push_back(next_node);
            used_nodes.insert(next_node);
        }
    }
    return child;
}

void GeneticAlgorithm::Mutate(Path& path) {
    if (path.nodes.size() <= 2) return;

    for (size_t i = 1; i < path.nodes.size() - 1; i++) {
        if ((rand() / double(RAND_MAX)) < MUTATION_RATE) {
            int current = path.nodes[i];
            vector<int> neighbors;

            for (int j = 0; j < NUM_NODE; j++) {
                if (graph[current][j] != INT_MAX && j != current &&
                    find(path.nodes.begin(), path.nodes.end(), j) == path.nodes.end()) {
                    neighbors.push_back(j);
                }
            }
            if (!neighbors.empty()) {
                int new_node = neighbors[rand() % neighbors.size()];
                path.nodes[i] = new_node;
            }
        }
    }
}


void GeneticAlgorithm::Run() {
    vector<Path> population;
    InitPopulation(population);

    if (population.empty()) {
        cout << "경로가 없습니다." << endl;
        return;
    }

    for (int generation = 0; generation < GENERATIONS; generation++) {
        EvalPopulation(population);

        vector<Path> newPopulation;
        for (int i = 0; i < POPULATION_SIZE / 2; i++) {
            Path parent1 = SelectParent(population);
            Path parent2 = SelectParent(population);
            Path child1 = Crossover(parent1, parent2);
            Path child2 = Crossover(parent2, parent1);
            Mutate(child1);
            Mutate(child2);
            newPopulation.push_back(child1);
            newPopulation.push_back(child2);
        }
        population = newPopulation;
    }

    EvalPopulation(population);
    Path bestPath = population[0];
    PrintResult(bestPath);
}

void GeneticAlgorithm::PrintResult(const Path& bestPath) const {
    cout << "최적 경로: ";
    for (int node : bestPath.nodes) {
        cout << node << " ";
    }
    cout << endl;
    cout << "최적 경로 길이: " << bestPath.fitness << endl;
    answer_ga.push_back(bestPath.fitness);

    int num = bestPath.nodes.size();
    for (int i = 0; i < num - 1; i++)
        cout << graph[bestPath.nodes[i]][bestPath.nodes[i + 1]] << " ";

}