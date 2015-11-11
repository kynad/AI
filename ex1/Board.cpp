//#include the h file here - TODO:
#include <iostream>
#include <map>
using namespace std;


// class definition needs to move to an h file - TODO:
class Board 
{
  const string ALLOWED_CHARS="SGRDHW";

  private:
    int _size;
    char **_map;
    string IDS();
    string UCS();

  public:
    Board(int size, string mapAsSingleString);
    ~Board();
    string findPath(string algorithmName);
    void print();
};

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
  // first do some sort of input validation here, then parse:
  // input validation should check that:
  // 1. _size is a natural number
  // 2. mapAsSingleString length is divisable by _size
  // 3. mapAsSingleString contains only valid characters 
  // TODO: find out how to use regex in C++ pre 2011/14 or ask Ariel if C++11/14 can be used.
  _map = new char*[_size];
  for (int i=0; i < _size; i++)
  {
    _map[i] = new char[_size];
    for (int j = 0; j < _size; j++)
      _map[i][j] = mapAsSingleString.at((i * _size) + j);
  }
}

//This method is for self-testing purposes, should be removed before submission.
void Board::print()
{
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

/**
 * An implementation of the IDS algorithm applied to _map
 * @return the string representation of a path, each char means one of Down,Up,Left,Right.
 */
string Board::IDS()
{
  cout << "in IDS:" << endl;
  return "Blah!";
}

/**
 * An implementation of the UCS algorithm applied to _map
 * @return the string representation of a path, each char means one of Down,Up,Left,Right.
 */
string Board::UCS()
{
  cout << "in UCS:" << endl;
  return "Blah blah!";
}

// will move to TestBoard.cpp file for self/unit tests - TODO:
int main()
{
  cout << "creating and initializing the board" << endl;
  Board board = Board(5,"SRWWWRRRDWRRRDWRRRDWDDRRG");
  cout << "printing the board:" << endl;
  board.print();
  cout << "calling the IDS algorithm" << endl;
  string res = board.findPath("IDS");
  cout << "recieved the following result: " << res << endl;
  return 1;
}
