#include "Definitions.h"

using namespace std;

/**
 * Will validate input and assert if it is not as expected.
 * Currently will test that _size is a natural positive number,
 * that the string map is of length _size^2
 * and that it doesn't contain illegal characters.
 *
 * @param mapAsSingleString - the string to validate
 *                            (the member variable _size will be validated too,
 *                             but is not expected to be passed to this function).
 */
void Definitions::checkInput(int size, string mapAsSingleString)
{
  assert(size > 0);
  assert(mapAsSingleString.length() == size*size);
  assert(mapAsSingleString.find_first_not_of(VALID_CHAR_SET) == string::npos);
}

/**
 * Converts character terrain representation to graph edge weight (int).
 * 
 * @param terrain - the char that represents this terrain. Can be one of: {S,G,R,D,H,W}
 *
 * @return int - the weight of this map cell.
 */
int Definitions::costOf(char terrain)
{
  switch(terrain)
  {
  case 'S':
  case 'G':
    return 0;
  case 'R':
    return 1;
  case 'D':
    return 3;
  case 'H':
    return 10;
  case 'W':
    return -1;
  default:
    cout << "Unknown terrain" << terrain << endl; 
    throw ""; //TODO: Make proper exceptions
  }
}

/**
 * Converts direction as int to its string "compas" representation. 
 * See ex definitions for more details.
 *
 * @param dir - The direction as int. 
 *              Each digit is taken as the direction associated with this int in a numpad keyboard, 
 *              i.e. 3 means Right-Down (diagonal).
 *
 * @return THe abbrevation of this direction, e.g. Right-Down --> "RD"
 */
string Definitions::convertDirection(int dir)
{
  assert(dir > 0 && dir < 10);
  string directions[11] = {"", "LD", "D", "RD", "L", "", "R", "UL", "U", "UR"};
  return directions[dir];
}

/**
 * @return the first neighbor by the order that was defined in the ex.
 */
int Definitions::firstNeighbor()
{
  return 6;
}

/**
 * @return the next neighbor by the order that was defined in the ex.
 */
int Definitions::nextNeighbor(int currentNeighbor)
{
  assert(currentNeighbor > 0 && currentNeighbor < 10);
  // TODO: optimize the shit out of this
  int nextNeighbor[10] = {-1,4,1,2,7,-1,3,8,9,-1};
  return nextNeighbor[currentNeighbor];
}

/**
 * returns -1 to signal that no more neighbors left to process.
 * basically, all 4 functions were supposed to replace a full iterator.
 */
int Definitions::lastNeighbor()
{
  return -1;
}

/**
 * @return the previous neighbor by the order that was defined in the ex.
 */
int Definitions::prevNeighbor(int currentNeighbor)
{
  if (currentNeighbor == -1)
    return 9;
  assert(currentNeighbor > 0 && currentNeighbor < 10);
  // TODO: optimize the shit out of this
  int prevNeighbor[10] = {-1,2,3,6,1,-1,9,4,7,8};
  return prevNeighbor[currentNeighbor];
}

/**
 * Detaching the neighbors of the given cell, if their terrain is water.
 * In addition, as required, will detach adjacent diagonal neighbors,
 * if the non-diagonal neighbor is water.
 *
 * @param cell - the cell that needs to be cleaned up.
 */
void Definitions::cleanCellNeighbors(Cell *cell)
{
  // 5 should always be NULL, it should not be used.
  cell->setNeighbor(5, NULL);
  for(int i=firstNeighbor(); i != lastNeighbor(); i=nextNeighbor(i))
    if(cell->getNeighbor(i) != NULL && (cell->getNeighbor(i))->getCost() == costOf('W'))
    {
      cell->setNeighbor(i,NULL);
      if(!isDiagonal(i))
      {
        cell->setNeighbor(nextNeighbor(i),NULL);
        cell->setNeighbor(prevNeighbor(i),NULL);
      }
    }
}

/**
 * Converts the Path object to a string representation defined in the ex.
 *
 * @param path - the Path object to be converted.
 * 
 * @return the string representation of the path.
 */
string Definitions::convertPath(PriorityPath path)
{
 
  if (path.priority == 0)
    return "no path";

  ostringstream stream;
  vector<int>::const_iterator memcell=(path.directions).begin();
  stream << convertDirection(*memcell);
  for (memcell++; memcell != (path.directions).end(); memcell++)
    stream << "-" << convertDirection(*memcell);
  stream << " " << path.priority;

  return stream.str();
}

/**
 * @return true if the direction is diagonal and false otherwise
 */
bool Definitions::isDiagonal(int direction)
{
  return (bool)(direction % 2);
}

/**
 * Calculates the probability to get from one cell to another with the chosen direction.
 * Basically, answers the question: what is the probability that if I move from one cell
 * in a given direction (which is my action), I will get to the cell I want to get to.
 *
 * @param current - the cell to move from (current state)
 * @param next    - the cell to move to (desired state)
 * @param actual - the actual direction which connects current to next (should be -1 if they aren't connected)
 * @param action - the direction we query about 
 */
double Definitions::probability(Cell* current, Cell* next, int actual, int action)
{
  if (actual == -1)
    return 0.0;
  if (isDiagonal(action))
  {
    if (actual == prevNeighbor(action) || action == prevNeighbor(actual))
      return 0.15;
    else if (actual == action)
      return 0.7;
  }
  else if (actual == action)
    return 1.0;
  return 0.0;
}

/**
 * Finds the reward for transition from one cell to another.
 * Since this only depends on the target cell (assuming it is reachable), we ignore the current cell.
 *
 * @param current - the cell we are at
 * @param next    - the cell we want to go to
 *
 * @return the expected reward for the transition, which is the cost of the next cell.
 */
int Definitions::reward(Cell* current, Cell* next)
{
  return next->getCost();
}
