#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "Plain.h"

using namespace std;

/**
 *  Helping struct that represents the input file structure
 */
struct inputParser
{
  string method;
  int boundary;
  vector< pair<double, double> > points;
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
 * Reads the given input file and parses the results.
 * Constructs the plain based on the parsed info.
 * 
 * @param inputPath - the path of the input file to read from.
 */
inputParser readAndParseInput(const char* inputPath)
{
  ifstream input(inputPath);
  inputParser parser;

  if(input.is_open())
  {
    string line;

    // get the distance calculation method
    getline(input, parser.method);

    // get the number of clusters
    getline(input, line);
    parser.boundary = atoi(line.c_str());

    // parse the rest of the lines, construct points from each and add them to the plain
    while (getline(input, line))
    {
      double x,y;
      sscanf(line.c_str(), "%lf,%lf", &x, &y);
      parser.points.push_back(make_pair(x, y));
    }
  }
  else
  {
    cout << "Couldn't open the input file, aborting" << endl;
    throw "";
  }  
  return parser;
}

// should be part of definitions
string convertPlainToOutputStr(Plain* plain)
{
  vector<Point*> points(plain->getPoints());
  stringstream stream;
  for (vector<Point*>::iterator it = points.begin(); it != points.end(); it++)
    stream << (*it)->clusterId + 1 << endl;
  return stream.str();
}

int main()
{
  inputParser parser = readAndParseInput("input.txt");
  Plain* plain = Plain::factory(parser.method);
  for (vector< pair<double,double> >::iterator it=parser.points.begin(); it != parser.points.end(); it++)
    plain->addNewPoint((*it).first, (*it).second);
  plain->executeHierarchicalClustering(parser.boundary);
  string result = convertPlainToOutputStr(plain);
  writeResults("output.txt", result);
  return 1;
}
