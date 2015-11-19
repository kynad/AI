#include "Board.h"
using namespace std;

/**
 * A constructor - sets _size and constructs _map, which is a matrix representation
 * of a map, where each cell is a character, with different meaning for each char.
 *
 * @param size - the size of the map given.
 * @param mapAsSingleString - the map as one long string, without any delimeters.
 */
Board::Board(int size, string mapAsSingleString) : _size(size)
{
  cout << "in ctor:" << "size is " << _size << ", map string is: " << mapAsSingleString << endl;
  checkInput(mapAsSingleString);

  // TODO: remove _map, it's not needed
  _map = new char*[_size];
  for (int i=0; i < _size; i++)
  {
    _map[i] = new char[_size];
    for (int j = 0; j < _size; j++)
      _map[i][j] = mapAsSingleString.at((i * _size) + j);
  }

  _graph = new cell*[_size*_size*sizeof(cell)];
  for (int i=0; i < _size*_size; i++)
    _graph[i] = new cell(costOf(mapAsSingleString.at(i)));

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
    cleanCellNeighbors(_graph[i]);
}

void Board::cleanCellNeighbors(cell *Cell)
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

//This method is for self-testing purposes, should be removed before submission.
void Board::print()
{
  cout << "in print:" << endl;
  for (int i=0; i < _size; i++)
  {
    for (int j=0; j < _size; j++)
      cout << _map[i][j] << " ";
    cout << endl;
  }

  for (int i=0; i < _size; i++)
  {
    for (int j=0; j < _size; j++)
      cout << _graph[i*_size+j] << " ";
    cout << endl;
  }
}

/**
 * A destructor - frees the memory for the _map member variable.
 */
Board::~Board()
{
  cout << "in dtor:" << endl;
  for (int i=0; i < _size; i++)
  {
    delete [] _map[i];
  }
  delete [] _map;

  delete [] _graph;
}

/**
 *
 */
int Board::costOf(char terrain)
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
    throw "Unknown terrain";
  }
}

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
void Board::checkInput(string mapAsSingleString)
{
  cout << "in checkInput" << endl;
  assert(_size > 0);
  assert(mapAsSingleString.length() == _size*_size);
  assert(mapAsSingleString.find_first_not_of(VALID_CHAR_SET) == string::npos);
}

/**
 * Finds the optimal path using one of the supported algorithms.
 * @param algorithmName - a selector of the algorithm to be used.
 * @return the string representation of a path, each char means one of Down,Up,Left,Right.
 */
string Board::findPath(string algorithmName)
{
  cout << "in findPath: " << "algorithm name is " << algorithmName << endl;

  // TODO: this idiotic language can't switch on strings.c++11 or c++14 can - make sure they can be used.
  if (algorithmName=="IDS")
    return IDS();
  else if (algorithmName=="UCS")
    return UCS();
  else
    throw "Wrong algorithm. Currently only IDS and UCS are supported";
}

string Board::convertPath(PriorityPath path)
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

string Board::DFS(int max_d, cell* where_the_f_am_i, int step, string s_string) //edited on 18.11 by thebeancounter. implemented assuming there is a function that returnes the neighbors.
{
  /*cout << "in IDS:" << endl;
  return "Blah!";*/
    int i;
    if(where_the_f_am_i == this->goal)
      return(s_string);
    if(step>=max_d)
        return "";
    for(i=firstNeighbor(); i != lastNeighbor(); i=nextNeighbor(i))
      if(RDir(i)!="" && (where_the_f_am_i->get_neighbor(i)))            //we are not refering to outself and we do have a neighbor
        if(DFS(max_d,where_the_f_am_i->get_neighbor(nextNeighbor(i)),step+1,s_string)!="") //the wierd modulo order is for the program spec given by the great t.a, if there is no path, we will get the horrible null and wont activate.
          return (s_string + "-" + RDir(i)); //if we do in fact find a path, we return in.
}

string Board::RDir(int dir)
{
    //string* temp = new string("");
    switch(dir) {
        case 1:
            return("LD");
        case 2:
            return("D");
        case 3:
            return("RD");
        case 4:
            return("L");
        case 5:
            return("");
        case 6:
            return("R");
        case 7:
            return("UL");
        case 8:
            return("U");
        case 9:
            return("UR");
        default:
            return("im rick james! enjoy yourself!");
            }

} //new by the bean counter

/**
 * An implementation of the UCS algorithm applied to _map
 * @return the string representation of a path, each char means one of Down,Up,Left,Right.
 */
string Board::UCS()
{
  cout << "in UCS:" << endl;
  priority_queue<PriorityPath> queue;
  PriorityPath path = PriorityPath(start);
  cell* parent = start;
  queue.push(path);
  while (!queue.empty())
  {
    path = queue.top();
    queue.pop();
    if (path.lastCell() == goal)
      return convertPath(path);
    else
      for (int i=firstNeighbor(); i != lastNeighbor(); i = nextNeighbor(i))
      {
        cell* child = (path.lastCell())->get_neighbor(i);
        if (child != NULL && child != path.lastCell() && child != parent && child != start)
          queue.push(PriorityPath(path, child, i));
      }
    parent = path.lastCell();
  }
  return convertPath(path);
}

/**
 * An implementation of the IDS algorithm applied to _map
 * @return the string representation of a path, each char means one of Down,Up,Left,Right.
 */
string Board::IDS()
{
  cout << "in IDS:" << endl;
  return "no path";
}

int Board::firstNeighbor()
{
  return 6;
}

int Board::nextNeighbor(int currentNeighbor)
{
  // TODO: optimize the shit out of this
  int nextNeighbor[10] = {-1,4,1,2,7,-1,3,8,9,-1};
  return nextNeighbor[currentNeighbor];
}

int Board::lastNeighbor()
{
  return -1;
}
