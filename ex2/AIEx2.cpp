#include <iostream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "Board.h"

using namespace std;

/**
 * Basic helper struct to return the results of parsing input.txt
 */
struct input
{
  int size;
  string algorithm;
  string mapAsSingleString;
};

/**
 * Writes a given string to a file.
 *
 * @param outputPath - the path of the file to write to.
 * @param outputStr  - the string to write to the file.
 */
void writeResults(const char* outputPath, string outputStr)
{
  ofstream output;
  output.open(outputPath);
  output << outputStr;
  output.close();
}

/**
 * Reads the given input file and parses the results to the input helper struct.
 * 
 * @param inputPath - the path of the input file to read from.
 */
input readAndParseInput(const char* inputPath, bool skipFirstLine=false)
{
  input parsedRes;

  ifstream input (inputPath);
  string line;

  if(input.is_open())
  {
    if (!skipFirstLine)
    {
      // in ex1 the first line holds the name of the algorithm to use
      getline(input, line);
      parsedRes.algorithm = line.substr(0,3);
    }
    else
      parsedRes.algorithm = "Value Iteration";
    
    // get the board size
    getline(input, line); 
    parsedRes.size = atoi(line.c_str());
    
    // parse the rest of the lines and concat them to a single string
    for (int i=0; i < parsedRes.size && getline(input, line); i++)
      (parsedRes.mapAsSingleString).append(line.substr(0, parsedRes.size));
  }
  else
  {
    cout << "Couldn't open the input file, aborting" << endl;
    throw "";
  }
  
  return parsedRes;
}


int main()
{
  Board board;
  input specs = readAndParseInput("input.txt", true);
  board.init(specs.size, specs.mapAsSingleString);
  string result = board.findPolicy(specs.algorithm);
  writeResults("output.txt", result);
  return 1;
}
