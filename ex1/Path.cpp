#include "Path.h"

/**
 * Constructor from another path and a new node.
 * Basically a copy constructor that adds the new node after construction.
 *
 * @param parent    - the path to copy
 * @param child     - the new cell to be added to the path
 * @param direction - the direction this path advanced to
 *                    in other words, the direction that one had to take to advance from
 *                    the last node in parent to the new node "child".
 */
PriorityPath::PriorityPath(PriorityPath parent, 
                           Cell* child, 
                           int direction) : cells(parent.cells),
                                            priority(parent.priority),
                                            directions(parent.directions)                                                                             
{
  append(child, direction);
}

/**
 * "default" constructor
 * Constructs a path with the first cell, since empty path is rarely used.
 * 
 * @param startCell - the first cell of the path.
 */
PriorityPath::PriorityPath(Cell* startCell)
{
  priority = 0;
  if (startCell)
    priority = startCell->getCost();
  cells.push_back(startCell);
}

/**
 * default constructor
 * probably can do without it. TODO: if time permits.
 */
PriorityPath::PriorityPath()
{
  priority = 0;
}

/**
 * adds the new cell to this path
 *
 * @param newCell   - the cell to be added to the path
 * @param direction - the direction from the last cell to this new cell
 */
void PriorityPath::append(Cell* newCell, int direction)
{
  directions.push_back(direction);
  cells.push_back(newCell);
  priority += newCell->getCost();
}

/**
 * ugly last minute hack to get the parent of the last cell in path.
 * this is used in DFS for duplicate pruning i.e. to avoid cycles of length 2 or less.
 *
 * @return the one before last cell in the path.
 */
Cell* PriorityPath::lastParent()
{
  if (cells.size() > 1)
  {
    return cells[cells.size()-2];
  }
  return NULL;
}

/**
 * @return the last cell in the path
 */
Cell* PriorityPath::lastCell()
{
  return cells.back();
}

/**
 * returns the number of steps from first cell to last cell 
 * (which is basically the number of cells minus one).
 */
int PriorityPath::length()
{
  return directions.size();
}

/**
 * Implementation of the smaller-then comperator that is required by the priority queue
 */
bool PriorityPath::operator<(const PriorityPath& other) const
{
  if (priority != other.priority)
    return priority > other.priority;
  int rainbow[10] = {-1,4,3,2,5,-1,1,6,7,8};
  for (int i=0; i < directions.size() && i < other.directions.size(); i++)
    if (rainbow[directions[i]] != rainbow[other.directions[i]])
      return rainbow[directions[i]] > rainbow[other.directions[i]];
  return false;
}

/**
 * Checks if the given cell is already part of a path.
 * 
 * @param cell - the cell in question
 *
 * @return true if the given cell was found in cells, false otherwise. 
 */
bool PriorityPath::visited(Cell* cell)
{
  return find(cells.begin(), cells.end(), cell) != cells.end();
}
