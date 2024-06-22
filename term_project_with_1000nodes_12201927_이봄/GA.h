#pragma once
// GA.h
#ifndef GA_H
#define GA_H

#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>

using namespace std;


extern const int MAX_WEIGHT;
extern const long long NUM_NODE;
extern const int POPULATION_SIZE;
extern const int GENERATIONS;
extern const double MUTATION_RATE;
extern int start_node;
extern int goal_node;

extern vector<long long> answer_ga;

struct Path {
    vector<int> nodes;
    long long fitness;

    bool operator<(const Path& other) const {
        return fitness < other.fitness;
    }
};

class GeneticAlgorithm {
private:
    vector<vector<long long>> graph;
    vector<int> nodeList;

    void InitPopulation(vector<Path>& population);
    long long CalFitness(const Path& path);
    void EvalPopulation(vector<Path>& population);
    Path SelectParent(const vector<Path>& population);
    Path Crossover(const Path& parent1, const Path& parent2);
    void Mutate(Path& path);

public:
    GeneticAlgorithm(const vector<vector<long long>>& g);
    void Run();
    void PrintResult(const Path& bestPath) const;
};


#endif // GA_H