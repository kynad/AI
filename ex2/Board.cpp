#include "Board.h"
using namespace std;


/**
 * An initializer - sets _size and constructs _map, which is a matrix representation
 * of a map, where each cell is a character, with different meaning for each char.
 *
 * @param size              - the size of the map given.
 * @param mapAsSingleString - the map as one long string, without any delimeters.
 */
int Board::init(int size, string mapAsSingleString)
{
  Definitions::checkInput(size, mapAsSingleString);

  _size = size;
  
  _graph = new Cell*[_size*_size*sizeof(Cell)];
  for (int i=0; i < _size*_size; i++)
    _graph[i] = new Cell(Definitions::costOf(mapAsSingleString.at(i)), i);

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
            _graph[i*_size + j]->setNeighbor((i-k+1)*3+(l-j+2), _graph[k*_size + l]);

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
 * @return the string representation of a path (see more info in the ex definition).
 */
string Board::findPath(string algorithmName)
{
  PriorityPath path;
  // TODO: this idiotic language can't switch on strings.c++11 or c++14 can - make sure they can be used.
  // P.S. They can't.
  if (algorithmName=="IDS")
    path = IDS();
  else if (algorithmName=="UCS")
    path = UCS();
  else
    throw "Wrong algorithm. Currently only IDS and UCS are supported";
  return Definitions::convertPath(path);
}

/**
 * Finds the optimal policy with value iteration.
 * For consistency and assuming that ew'll need to exapd this code, I'm still using algorithmName, as in findPath.
 *
 * @param algorithmName - a selector of the algorithm to be used.
 *
 * @return the string representation of a policy (see more info in the ex definition).
 */
string Board::findPolicy(string algorithmName)
{
  vector<int> policy;

  if (algorithmName=="Value Iteration")
    policy = ValueIteration();
  else
    throw "Wrong algorithm. Currently only Value Iteration is supported";

  return Definitions::convertPolicy(policy, _size);
}


/**
 * An implementation of the UCS algorithm applied to _graph
 *
 * @return PriorityPath object that contains info about the nodes of the path and it's total cost.
 */
PriorityPath Board::UCS()
{
  priority_queue<PriorityPath> queue;
  PriorityPath path = PriorityPath(start);
  Cell* parent = start;
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
        Cell* child = (path.lastCell())->getNeighbor(i);
        if (child != NULL && !path.visited(child))
          queue.push(PriorityPath(path, child, i));
      }
    parent = path.lastCell();
  }
  return PriorityPath(NULL);
}

/**
 * An implementation of the IDS algorithm applied to _graph
 *
 * @return PriorityPath object that contains info about the nodes of the path and it's total cost.
 */
PriorityPath Board::IDS()
{
  PriorityPath path;

  for(int level = 0; level < MAX_DFS_DEPTH; level++)
  {
    path = DFS(PriorityPath(start), level);
    if (path.length() > 0)
      return path;
  }
  return PriorityPath(NULL);  
}

/**
 * An implementation of the DFS with a max depth limit as required for the IDS algorithm.
 *
 * This is a recursive function that counts the number of nested calls.
 * 
 * @param path         - the accumulated path that is keeping the result.
 * @param stepsCounter - the depth limitation.
 *
 * @return PriorityPath object that contains info about the nodes of the path and it's total cost.
 */
PriorityPath Board::DFS(PriorityPath path, int stepsCounter)
{
  Cell* currentCell = path.lastCell();
  if (currentCell == goal)
    return path;
  if (stepsCounter >= 0)
    for(int cur_dir=Definitions::firstNeighbor(); 
        cur_dir != Definitions::lastNeighbor(); 
        cur_dir=Definitions::nextNeighbor(cur_dir))
    {
      Cell* child = currentCell->getNeighbor(cur_dir);
      if((child != NULL) && (child != currentCell) && (child != path.lastParent()))
      {
        PriorityPath currentPath = DFS(PriorityPath(path, child, cur_dir),stepsCounter-1);
        if (currentPath.lastCell() != NULL)
          return currentPath;
      }
    }
  return PriorityPath(NULL);
}

////////////// REMOVE printing functions ////////////////
void Board::printVector(vector<double> vec)
{
  for (int i = 0; i < _size; i++)
    for (int j = 0; j < _size; j++)
      cout << vec[i*_size+j] << ((_size - j > 1) ? " " : "\n");
}
void Board::printVector(vector<int> vec)
{
  for (int i = 0; i < _size; i++)
    for (int j = 0; j < _size; j++)
      cout << vec[i*_size+j] << ((_size - j > 1) ? " " : "\n");
}
///////////////////////////////////////////////////////


/**
 * Implementation of the Value Iteration algorithm.
 * Iterates over every neighbor of each vertex in _graph and finds the one
 * that maximizes that vertex Bellman equation.
 * Ends when the rewards begins to converge 
 * (i.e. the difference between each step becomes neglible)
 * 
 * @return the policy (best direction to go to for each vertex) as vector<int>
 */
vector<int> Board::ValueIteration()
{
  vector<double> utilityTag;
  for (int i = 0; i < _size*_size; i++)
    utilityTag.push_back(Definitions::reward(_graph[i]));

  vector<double> utility(utilityTag.size(), 0);
  int counter=0;
  do
  {
    utility = utilityTag;
    for (int i = 0; i < _size*_size - 1; i++)
    {
      if (Definitions::isWater(_graph[i]))
        continue;
      int argMax; // Not going to use that here, ignore.
      double max = maxExpectancy(_graph[i], utility, &argMax);
      utilityTag[i] = Definitions::reward(_graph[i]) + Definitions::discountFactor()*max;
    }

  } while (!Definitions::closeEnough(utility,utilityTag) && (counter++ < _size*_size));

  return calculatePolicy(utility);
}

/**
 * Returns the Sum(Probability(move from current cell to it's neighbor, using action)*value)
 */
double Board::expectancy(Cell* current, int action, vector<double> utility)
{
  double expectancy = 0.0;
  for(int dir  = Definitions::firstNeighbor(); 
      dir != Definitions::lastNeighbor(); 
      dir  = Definitions::nextNeighbor(dir))
  {
    Cell* neighbor = current->getNeighbor(dir);
    if (neighbor != NULL)
    {
      double oldValue = utility[neighbor->getId()];
      double prob = Definitions::probability(current, neighbor, dir, action);
      expectancy += prob * oldValue;
    }
  }
  return expectancy;
}

/**
 *
 */
double Board::maxExpectancy(Cell* current, vector<double> utility, int* argMax)
{
  double maxExpectancy = -MAX_REWARD;
  for(int action  = Definitions::firstNeighbor(); 
      action != Definitions::lastNeighbor(); 
      action  = Definitions::nextNeighbor(action))
  {
    double tempExp = expectancy(current, action, utility);
    if (tempExp != 0 && tempExp > maxExpectancy)
    {
      maxExpectancy = tempExp;
      *argMax = action;
    }
  }
  return maxExpectancy;
}

/**
 * Calculates the policy from the vertex values.
 *
 * @param utility - a vector of doubles that provides the value for every vertex
 *
 * @returns the policy - a list of directions to the highest-value neighbor for each vertex.
 */
vector<int> Board::calculatePolicy(vector<double> utility)
{
  vector<int> policy(_size*_size, -1);

  for (int i = 0; i < _size*_size-1; i++)
  {
    if (Definitions::isWater(_graph[i]))
      continue;

    int argMax;
    double maxExp = maxExpectancy(_graph[i], utility, &argMax);
    policy[i] = argMax;
  }
  return policy;
}
