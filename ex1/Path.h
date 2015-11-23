#include <vector>
#include <iostream>
#include <sstream>
#include "Cell.h"
class PriorityPath
{
private:
  std::vector<cell*> cells;

public:
  std::vector<int> directions;
  int priority;

  PriorityPath(PriorityPath parent, cell* child, int direction);
  PriorityPath(cell* newCell);
  PriorityPath();

  void append(cell* newCell, int direction);
  cell* lastCell();
  cell* lastParent();
  int length();

  bool operator<(const PriorityPath& other) const;
};
