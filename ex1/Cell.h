#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
#endif // CELL_H_INCLUDED

#include <iostream>
#include <assert.h>

//#define NUM_NEIGHBORS 10

class cell
{

  public:
  //    Cell* neighbors[NUM_NEIGHBORS];
    cell* neighbors[9];
    int cost;

    cell* get_neighbor(const int); //gets the direction
    int get_cost();
    cell(int cost);
    ~cell();
    void set_neighbor(int dir, cell* adress);
    void clean_neighbors();
    void validateDirection(int direction);
};

