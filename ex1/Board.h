/**
 * Description - TODO:
 */

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <assert.h>
#include "Cell.h"
#include <vector>

#define VALID_CHAR_SET "SGRDHW"

class Board 
{

  private:
    int _size;
    char **_map;
    cell **_graph;
    void checkInput(std::string mapAsSingleString);
    int costOf(char terrain);
    std::string IDS();
    std::string UCS();

  public:
    Board(int size, std::string mapAsSingleString);
    ~Board();
    std::string findPath(std::string algorithmName);
    void print();
};

