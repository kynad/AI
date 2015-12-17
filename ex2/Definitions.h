//
// This class tries (not fully) to abstract away the exercise definitions.
// It contains the translation functions from the terrain to cost, the order of the neighbors
// the valid terrain chars, etc, etc...
//
// By the looks of it now, it probably shouldn't be a clss anymore, 
// but there should be a limit to every perfectionism.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "Path.h"

#define VALID_CHAR_SET "SGRDHW"
#define MAX_COST 11


class Definitions
{
public:
  static void checkInput(int size, std::string mapAsSingleString);
  static int costOf(char terrain);
  static std::string convertDirection(int);
  static int firstNeighbor();
  static int nextNeighbor(int currentNeighbor);
  static int lastNeighbor();
  static int prevNeighbor(int currentNeighbor);
  static void cleanCellNeighbors(Cell * cell);
  static std::string convertPath(PriorityPath path);
  static bool isDiagonal(int direction);
  static double probability(Cell* current, Cell* next, int actual, int action);
  static double discountFactor() {return 1.0;}
  static int reward(Cell* cell);
};
