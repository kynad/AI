#include "Policy.h"

using namespace std;

Policy::Policy(int size) : _size(size) 
{
  _policy = new double*[_size];
  for (int i=0; i<_size; i++)
  {
    _policy[i] = new double[_size];
    for (int j=0; j<_size; j++) 
      _policy[i][j]=Definitions::costOf('W');
  }
}

Policy::~Policy() 
{
  for (int i=0; i<_size; i++)
    delete _policy[i];
  delete [] _policy;
}

Policy::Policy(const Policy& other) : _size(other._size)
{
  _policy = new double*[_size];
  for (int i=0; i<_size; i++) 
  {
    _policy[i] = new double[_size];
    for (int j=0; j<_size; j++) 
      _policy[i][j]=other[i][j];
  }
}

double* Policy::operator[](int i) const
{
  return _policy[i];
}

bool Policy::operator!=(const Policy& other) const
{
  if (_size != other._size)
    return true;
  for (int i=0; i<_size; i++) 
    for (int j=0; j<_size; j++) 
      if (_policy[i][j] != other[i][j])
        return true;
  return false;
}
 
bool Policy::operator==(const Policy& other) const
{
  return !(*this != other);
}
