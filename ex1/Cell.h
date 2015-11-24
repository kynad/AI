#include <iostream>
#include <assert.h>

#define NUM_NEIGHBORS 10

class Cell
{
  private:
    Cell* neighbors[NUM_NEIGHBORS];
    int cost;

  public:
    Cell* getNeighbor(int);
    int getCost();
    Cell(int cost);
    void setNeighbor(int dir, Cell* adress);
    void validateDirection(int direction);
};

