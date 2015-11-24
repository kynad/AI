//
// PriorityPath represents a costed path of cells.
// It contains an ordered list (well, a vector) of cells
// and a similar list of directions (which are the transitions 
// between one cell and the next one in path).
// 
// By tracking the cells (or the directions) from first to last, one can recreate the path.
// 
// In additoin, the path is counting the total path cost 
// (which is the combined cost of all the cell in that path)
// and automagically updates the total cost on each new cell insertion.
// N.B. the reason it's called "priority", rather than "totalCost" or something
// is because it made more sense at first, when I only considered UCS.
//

#include <vector>
#include <iostream>
#include <sstream>
#include "Cell.h"

class PriorityPath
{
  private:
    std::vector<Cell*> cells;

  public:
    std::vector<int> directions;
    int priority;

    PriorityPath(PriorityPath parent, Cell* child, int direction);
    PriorityPath(Cell* newCell);
    PriorityPath();

    void append(Cell* newCell, int direction);
    Cell* lastCell();
    Cell* lastParent();
    int length();

    bool operator<(const PriorityPath& other) const;
};
