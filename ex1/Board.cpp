#include "Board.h"
using namespace std;

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

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
  for (int i=0; i < _size; i++)
    for (int j=0; j < _size; j++)
      for (int k=MAX((i-1),0); k < MIN((i+2),_size); k++)
        for (int l=MAX((j-1),0); l < MIN((j+2),_size); l++)
          _graph[i*_size + j]->set_neighbor((i-k+1)*3+(l-j+2), _graph[k*_size + l]);
  for (int i=0; i < _size*_size; i++)
    _graph[i]->clean_neighbors();
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

  // TODO: this idiotic language can't switch on strings, but c++11 or c++14 can, need to make sure.
  if (algorithmName=="IDS")
    return IDS();
  else if (algorithmName=="UCS")
    return UCS();
  else
    throw "Wrong algorithm. Currently only IDS and UCS are supported";
}

string Board::DFS(int max_d, cell* where_the_f_am_i, int step, string s_string) //edited on 18.11 by thebeancounter. implemented assuming there is a function that returnes the neighbors.
{
  /*cout << "in IDS:" << endl;
  return "Blah!";*/
    int i;
    //if(where_the_f_am_i == this->destination_cell)
        //return(s_string)
    if(step>=max_d)
        return "";
    for(i=2;i<11;i++)
        if(RDir(i)!="" && (where_the_f_am_i->get_neighbor((i%9)+1)))            //we are not refering to outself and we do have a neighbor
            if(DFS(max_d,where_the_f_am_i->get_neighbor((i%9)+1),step+1,s_string)!="") //the wierd modulo order is for the program spec given by the great t.a, if there is no path, we will get the horrible null and wont activate.
                return (s_string +"-" + RDir(i)); //if we do in fact find a path, we return in.
}

string Board::RDir(int dir)
{
    //string* temp = new string("");
    switch(dir) {
        case 1:
            return("ld");
        case 2:
            return("d");
        case 3:
            return("rd");
        case 4:
            return("l");
        case 5:
            return("");
        case 6:
            return("r");
        case 7:
            return("ul");
        case 8:
            return("u");
        case 9:
            return("ur");
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
  return "Blah blah!";
}

/**
 * An implementation of the IDS algorithm applied to _map
 * @return the string representation of a path, each char means one of Down,Up,Left,Right.
 */
string Board::IDS()
{
  cout << "in IDS:" << endl;
  return "Blah blah!";
}

