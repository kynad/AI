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
string Definitions::RDir(int dir)
{
  assert(dir > 0 && dir < 10);
  string directions[11] = {"", "LD", "D", "RD", "L", "", "R", "UL", "U", "UR"};
  return directions[dir];
}

int Definitions::firstNeighbor()
{
  return 6;
}

int Definitions::nextNeighbor(int currentNeighbor)
{
  assert(currentNeighbor > 0 && currentNeighbor < 10);
  // TODO: optimize the shit out of this
  int nextNeighbor[10] = {-1,4,1,2,7,-1,3,8,9,-1};
  return nextNeighbor[currentNeighbor];
}

int Definitions::lastNeighbor()
{
  return -1;
}

void Definitions::cleanCellNeighbors(cell *Cell)
{
  int prev = lastNeighbor();
  for(int i=firstNeighbor(); i != lastNeighbor(); i=nextNeighbor(i))
    if(Cell->get_neighbor(i) != NULL && (Cell->get_neighbor(i))->get_cost() == costOf('W'))
    {
      Cell->set_neighbor(i,NULL);
      if(!(i%2))
      {
        Cell->set_neighbor(nextNeighbor(i),NULL);
        Cell->set_neighbor(prev,NULL);
      }
      prev = i;
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
  stream << RDir(*memcell);
  for (memcell++; memcell != (path.directions).end(); memcell++)
    stream << "-" << RDir(*memcell);
  stream << " " << path.priority;

  return stream.str();
}
