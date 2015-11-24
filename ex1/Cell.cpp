#include "Cell.h"
using namespace std;

/**
 * Constructor of the Cell class
 * Sets the cost and inits the neighbors array.
 *
 * @param cost - the cost of this cell (see ex definitions for more details)
 */
Cell::Cell(int cost) : cost(cost)
{
  for(int i = 1; i < NUM_NEIGHBORS; i++)
    setNeighbor(i, NULL);
}

/**
 * Input validation to avoid segfaults. Not really needed.
 *
 * @param direction - An integer that translates to direction.
 *                    The translation from int to an actual direction
 *                    is defined in the Definitions class.
 */
void Cell::validateDirection(int direction)
{
  assert(direction > 0 && direction < NUM_NEIGHBORS);
}

/**
 * Sets the i-th neighbor.
 * 
 * @param direction - the neighbor direction as int.
 * @param adress    - the pointer to the neighbor cell.
 */
void Cell::setNeighbor(int direction, Cell* adress)
{
  validateDirection(direction);
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
  validateDirection(direction);
  return neighbors[direction-1];
}
