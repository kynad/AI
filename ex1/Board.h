/**
 * Description - TODO:
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


class Board
{
  private:
    int _size;
    char **_map;
    cell **_graph;
    PriorityPath DFS(PriorityPath path, int stepsCounter);
    PriorityPath UCS();
    PriorityPath IDS();

  public:
    cell *start;
    cell *goal;
    int init(int size, std::string mapAsSingleString);
    ~Board();
    std::string findPath(std::string algorithmName);
    void print();
};
