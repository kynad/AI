#include "Board.h"
using namespace std;

/**
 * An initializer - sets _size and constructs _map, which is a matrix representation
 * of a map, where each cell is a character, with different meaning for each char.
 *
 * @param size - the size of the map given.
 * @param mapAsSingleString - the map as one long string, without any delimeters.
 */
int Board::init(int size, string mapAsSingleString)
{
  Definitions::checkInput(size, mapAsSingleString);

  _size = size;
  
  _graph = new cell*[_size*_size*sizeof(cell)];
  for (int i=0; i < _size*_size; i++)
    _graph[i] = new cell(Definitions::costOf(mapAsSingleString.at(i)));

  start = _graph[0];
  goal = _graph[_size*_size - 1];

  // This is where all the meat is:
  // We looop over i and j from 0 to _size, as if we actually had a square matrix here.
  // The function that converts i,j to array position is (i*_size+j).
  // We the loop over k and l, both running from (i-1) to (i+1) and from (j-1) to (j+1) respectively,
  // while skipping out of boud values s.a. -1 (e.g. when i=0) or _size (e.g. when j=(_size-1)).
  // That way we obtain all possible neighbors of every cell in the map.
  // The function that converts the neighbor position in the map (k,l) 
  // to the the neighbor ID of current node (i,j in the map) is (3*(i-k+1) + (l-j+2)).
  // That way neighbors are assigned with the ID as if we were looking at the numpad keyboard,
  // i.e. the cell that is directly above you is of ID 8, your left neighbor has ID 4,
  // the neighbor that is down-right from you is 3, etc, etc.
  for (int i=0; i < _size; i++)
    for (int j=0; j < _size; j++)
      for (int k=MAX((i-1),0); k < MIN((i+2),_size); k++)
        for (int l=MAX((j-1),0); l < MIN((j+2),_size); l++)
            _graph[i*_size + j]->set_neighbor((i-k+1)*3+(l-j+2), _graph[k*_size + l]);

  // finally, we instruct all cells to clean up.
  for (int i=0; i < _size*_size; i++)
    Definitions::cleanCellNeighbors(_graph[i]);
}

/**
 * A destructor - frees the memory for the _graph member variable.
 */
Board::~Board()
{
  delete [] _graph;
}

/**
 * Finds the optimal path using one of the supported algorithms.
 *
 * @param algorithmName - a selector of the algorithm to be used.
 *
 * @return the string representation of a path, each char means one of Down,Up,Left,Right.
 */
string Board::findPath(string algorithmName)
{
  PriorityPath path;
  // TODO: this idiotic language can't switch on strings.c++11 or c++14 can - make sure they can be used.
  if (algorithmName=="IDS")
    path = IDS();
  else if (algorithmName=="UCS")
    path = UCS();
  else
    throw "Wrong algorithm. Currently only IDS and UCS are supported";
  return Definitions::convertPath(path);
}

/**
 * An implementation of the UCS algorithm applied to _map
 * @return the string representation of a path, each char means one of Down,Up,Left,Right.
 */
PriorityPath Board::UCS()
{
  priority_queue<PriorityPath> queue;
  PriorityPath path = PriorityPath(start);
  cell* parent = start;
  queue.push(path);
  while (!queue.empty())
  {
    path = queue.top();
    queue.pop();
    if (path.lastCell() == goal)
      return path;
    else
      for (int i=Definitions::firstNeighbor(); i != Definitions::lastNeighbor(); i = Definitions::nextNeighbor(i))
      {
        cell* child = (path.lastCell())->get_neighbor(i);
        if (child != NULL && child != path.lastCell() && child != parent && child != start)
          queue.push(PriorityPath(path, child, i));
      }
    parent = path.lastCell();
  }
  return path;
}

/**
 * An implementation of the IDS algorithm applied to _map
 * @return the string representation of a path, each char means one of Down,Up,Left,Right.
 */
PriorityPath Board::IDS()
{
  PriorityPath path;

  //TODO: fix th ehard-coded limit here.
  for(int k = 0; k < 18; k++)
  {
    path = DFS(PriorityPath(start),k);
    cout << "try " << k << " ";
    if (path.length() > 0)
      return path;
  }
  return path;  
}


PriorityPath Board::DFS(PriorityPath path, int stepsCounter)
{
  cell* currentCell = path.lastCell();
  if (currentCell == goal)
    return path;
  if (stepsCounter >= 0)
    for(int cur_dir=Definitions::firstNeighbor(); 
        cur_dir != Definitions::lastNeighbor(); 
        cur_dir=Definitions::nextNeighbor(cur_dir))
    {
      cell* child = currentCell->get_neighbor(cur_dir);
      if((child != NULL) && (child != currentCell) && (child != path.lastParent()))
      {
        PriorityPath currentPath = DFS(PriorityPath(path, child, cur_dir),stepsCounter-1);
        if (currentPath.lastCell() != NULL)
          return currentPath;
      }
    }
  return PriorityPath(NULL);
}
