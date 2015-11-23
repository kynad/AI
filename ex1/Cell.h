#include <iostream>
#include <assert.h>

//#define NUM_NEIGHBORS 10

class Cell
{
  private:
    Cell* neighbors[9];
    int cost;


  public:
  //    Cell* neighbors[NUM_NEIGHBORS];

    Cell* get_neighbor(const int); //gets the direction
    int get_cost();
    Cell(int cost);
    ~Cell();
    void set_neighbor(int dir, Cell* adress);
    void validateDirection(int direction);
};

