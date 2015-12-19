#include "Cell.h"
using namespace std;

/**
 * Constructor of the Cell class
 * Sets the cost and an id and inits the neighbors array.
 *
 * @param cost - the cost of this cell (see ex definitions for more details)
 * @param id - the id of this cell (because it's an adult cell and deserves an id)
 */
Cell::Cell(int cost, int id) : cost(cost), id(id)
{
  for(int i = 1; i < NUM_NEIGHBORS; i++)
    setNeighbor(i, NULL);
}

/**
 * Just an input validator, shouldn't ever be needed after a working solution phase.
 */
void Cell::validateNeighbor(int neighbor)
{
  assert(neighbor > 0 && neighbor < 10);
}

/**
 * Sets the i-th neighbor.
 * 
 * @param direction - the neighbor direction as int.
 * @param adress    - the pointer to the neighbor cell.
 */
void Cell::setNeighbor(int direction, Cell* adress)
{
  validateNeighbor(direction);
  neighbors[direction-1] = adress;
}

/**
 * Gets the cost of this cell.
 */
int Cell::getCost()
{
  return cost;
}

/**
 * Gets the i-th neighbor adress
 *
 * @param direction - the neighbor direction in an integer representation.
 */
Cell* Cell::getNeighbor(int direction)
{
  validateNeighbor(direction);
  return neighbors[direction-1];
}

/**
 * @return that cell's id
 */
int Cell::getId()
{
  return id;
}
