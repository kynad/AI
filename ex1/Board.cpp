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

