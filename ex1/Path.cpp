#include "Path.h"

PriorityPath::PriorityPath(PriorityPath parent, cell* child, int direction) : directions(parent.directions),
                                                      cells(parent.cells),
                                                      priority(parent.priority)
{
  append(child, direction);
}

PriorityPath::PriorityPath(cell* startCell)
{
  priority = 0;
  cells.push_back(startCell);
}

PriorityPath::PriorityPath()
{
  priority = 0;
}

void PriorityPath::append(cell* newCell, int direction)
{
  directions.push_back(direction);
  cells.push_back(newCell);
  priority += newCell->get_cost();
}

cell* PriorityPath::lastParent()
{
  if (cells.size() > 1)
  {
    return cells[cells.size()-2];
  }
  return NULL;
}

cell* PriorityPath::lastCell()
{
  return cells.back();
}

int PriorityPath::length()
{
  return directions.size();
}

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
