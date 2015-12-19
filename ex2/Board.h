/**
 * The Board class is representing the map.
 * It is composed of a list of pointers to cell objects that keep lists of neighbors
 * And implements the IDS and the UCS algorithms on the resulted graph.
 */

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <queue>
#include "Definitions.h"


#ifndef MIN_MAX
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#endif

#define MAX_DFS_DEPTH 18

class Board
{
  private:
    int _size;
    Cell **_graph;
    PriorityPath DFS(PriorityPath path, int stepsCounter);
    PriorityPath UCS();
    PriorityPath IDS();
    std::vector<int> ValueIteration();
    std::vector<int> calculatePolicy(std::vector<double> utility);
    double expectancy(Cell* current, int action, std::vector<double> utility);
    double maxExpectancy(Cell* current, std::vector<double> utility, int* argMax);
    //debug
    void printVector(std::vector<double> vec);
    void printVector(std::vector<int> vec);

  public:
    Cell *start;
    Cell *goal;
    int init(int size, std::string mapAsSingleString);
    ~Board();
    std::string findPath(std::string algorithmName);
    std::string findPolicy(std::string algorithmName);
};
