/**
 * Description - TODO:
 */

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <assert.h>
#include "Cell.h"
#include <vector>
#include <queue>


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define VALID_CHAR_SET "SGRDHW"

class PriorityPath
{
public:
  std::vector<int> directions;
  std::vector<cell*> cells;
  int priority;
  void append(cell* Cell, int direction) {directions.push_back(direction); priority += (Cell->get_cost()); cells.push_back(Cell);};
  PriorityPath() {priority=0;};
  PriorityPath(PriorityPath parent, cell* child, int direction) {cells=parent.cells; directions=parent.directions; priority=parent.priority; append(child, direction);};
  PriorityPath(cell *Cell) {cells.push_back(Cell); priority=0;};

  cell* lastCell() { return cells.back();};

  bool operator<(const PriorityPath& other) const 
  { 
    if (priority==other.priority)
    {
      int length = MIN(directions.size(), other.directions.size());
      int rainbow[10] = {-1,4,3,2,5,-1,1,6,7,8};
      for (int i=0; i < length; i++)
        if (rainbow[directions[i]] != rainbow[other.directions[i]])
          return rainbow[directions[i]] > rainbow[other.directions[i]];
    }
    return priority > other.priority; 
  };
  
  void print() {  
    std::vector<int>::const_iterator memcell;
    std::cout << "path is: ";
    for (memcell=directions.begin(); memcell != directions.end(); ++memcell)
      std::cout << (*memcell) << "-";
    std::cout << " and priority is " << priority << std::endl;
  };
 
};


class Board
{
  private:
    int _size;
    char **_map;
    cell **_graph;
    void checkInput(std::string mapAsSingleString);
    int costOf(char terrain);
    std::string DFS(int,cell* where_the_f_am_i,int step,std::string s_string);
    std::string UCS();
    std::string IDS();
    std::string RDir(int); //new by the bean counter
    int firstNeighbor();
    int nextNeighbor(int currentNeighbor);
    int lastNeighbor();
    void cleanCellNeighbors(cell * Cell);
    std::string convertPath(PriorityPath path);

  public:
    cell *start;
    cell *goal;
    Board(int size, std::string mapAsSingleString);
    ~Board();
    std::string findPath(std::string algorithmName);
    void print();
};
