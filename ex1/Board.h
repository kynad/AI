/**
 * Description - TODO:
 */

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <assert.h>

class Board 
{

  private:
    int _size;
    char **_map;
    void checkInput(std::string mapAsSingleString);
    std::string IDS();
    std::string UCS();

  public:
    Board(int size, std::string mapAsSingleString);
    ~Board();
    std::string findPath(std::string algorithmName);
    void print();
};

