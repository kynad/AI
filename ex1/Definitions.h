#include <stdio.h>
#include <iostream>
#include <sstream>
#include "Path.h"

#define VALID_CHAR_SET "SGRDHW"


class Definitions
{
public:
  static void checkInput(int size, std::string mapAsSingleString);
  static int costOf(char terrain);
  static std::string RDir(int);
  static int firstNeighbor();
  static int nextNeighbor(int currentNeighbor);
  static int lastNeighbor();
  static void cleanCellNeighbors(cell * Cell);
  static std::string convertPath(PriorityPath path);
};
