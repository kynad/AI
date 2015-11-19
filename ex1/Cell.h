#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
#endif // CELL_H_INCLUDED

#include <iostream>
#include <assert.h>

//#define NUM_NEIGHBORS 10

class cell
{
  private:
    cell* neighbors[9];
    int cost;


  public:
  //    Cell* neighbors[NUM_NEIGHBORS];

    cell* get_neighbor(const int); //gets the direction
    int get_cost();
    cell(int cost);
    ~cell();
    void set_neighbor(int dir, cell* adress);
    void validateDirection(int direction);
};

