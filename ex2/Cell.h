#include <iostream>
#include <assert.h>

#define NUM_NEIGHBORS 10

class Cell
{
  private:
    Cell* neighbors[NUM_NEIGHBORS];
    int cost, id;

  public:
    Cell* getNeighbor(int);
    int getCost();
    Cell(int cost, int id);
    void setNeighbor(int dir, Cell* adress);
    void validateDirection(int direction);
    int getId();
};

