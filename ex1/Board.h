/**
 * Description - TODO:
 */

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <assert.h>
#include "Cell.h"

#define VALID_CHAR_SET "SGRDHW"

using namespace std;

class Board
{

  private:
    int _size;
    char **_map;
    cell **_graph;
    void checkInput(std::string mapAsSingleString);
    int costOf(char terrain);
    std::string DFS(int,cell* where_the_f_am_i,int step,std::string s_string);
    std::string UCS();
    std::string IDS();
    std::string RDir(int); //new by the bean counter

  public:
    Board(int size, std::string mapAsSingleString);
    ~Board();
    std::string findPath(std::string algorithmName);
    void print();
};

