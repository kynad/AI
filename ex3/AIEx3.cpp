#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "Plain.h"

/**
   Third exersize plan:
   We will need a directed tree (easy), where each node is a cluster. A cluster simply holds one or more points.
   We should also be using a distance matrix between all points.
   The algorithm will start with cluster for each point and will merge two closests cluster until the number of cluster equals or smaller than the boundary
   
   req:
   1. System must be configurable to work with average link and single link methods.
   2. System must parse input file and maintain the order of points.
   3. System must implement hierarchical clustering method bound by an integer k, taken from input file
   4. System must output the cluster id (from 1 to k) of the cluster that holds the point (for every point, by the order they appeared in the input file)

   main decisions:
   Q: Is there a way to optimize cluster distance calculation. E.g. for single-link which is the shortest distance between all pairs, it's MIN(MIN(Cluster, point from another cluster)), which can be broken into pieces.
   A: Assume you have two clusters C1 and C2 and you want to merge them into C. Let's consider d(C,C3), when d(C1,C3) and d(C2,C3) are known. In single link, d(C,C3) = MIN{d(C1,C3),d(C2,C3)}. In average link, d(C,C3) = (|C1|*d(C1,C3) + |C2|*d(C2,C3))/(|C1|+|C2|). 
   Conclusion: If optimized, the distance function must have access to the distance matrix.
  
   Q: Should clusters have their own matrices (well, vectors) with distance to all the other clusters, or should they derive these distances from the points distance table?
   A1: This is time-space tradeoff. I prefer to save memory at this point.
   A2: Once you merge two clusters, you need to update the distances for all the other clusters, which creates a mess. Better keep all distances in one place.
   Conclusion: There can (ok, should) be only one!

   Q. How do you implement the algorithm with different cluster metrics?
   A1. Pointers to functions. Given the above, the functions will have to have access to the distance matrix.
   A2. Inheritance: Two classes inherit from the same base class, where only the distance between clusters method is implemented in the children. Plus factory to create the classes.
   A3. If's. Ugly-ass if's everywhere.
   Conclusion: A2 is preferred (also by kiss principle).



   high-level:
   1. Main class will contain the usual: input parser and output writer, Point struct/class definition and the main function. Parser should not be aware of the data structures, it should return a separate struct and main should construct the plain (in this case) from that one.
   2. I don't think there is a need for definitions class in this case, there only two funcitons that really belong there - the toString and points enumerator, which is just dumb. So, for toString alone - I'd spare it.
   3. Point struct will represent a point - x,y,id, clusterId
   3. Cluster class will represent a cluster - it will hold a list of points, the lowest point id, will support merging and will have it's own id.
   4. Plane class will represent the plain - an array of clusters and their distance table (matrix). Will have a pure virtual method that calculates distances between clusters with size > 1. Will recalculate the custer IDs from their least point ID and reassign all clusterIds (which will trigger cluster to reassing point's clusterId). Plain might benefit from getting a pointer to function that calculates eucledian distance, but it's out of scope atm.
   5. SingleLinkPLain and AverageLinkPlain that will inherit Plain and will implement the cluster distance virtual method.


   class/struct Point:
     should have id and cluster id. both initialized to the same (given) value
     holds it's x and y coordinates.
   class Cluster:
     should have an id and a list of contained Point* objects. Also, should hold the lowestPointId, which is expected to be the minimal point id of all points contained in the cluster.
     should be able to merge between clusters, i.e. to have a "copy" constructor from two existing clusters.
     need to update each point's clusterId once its id is updated
   class Utils/Definitions:
     should have the Eucledian distance function (Point1, Point2) (private?)
     should have the Cluster distance function (Cluster1, Cluster2)
     should provide the single_link/average_link functions that will be passed as pointers to the Cluster distance function
     should have the point id function
     should have the cluster id function (that will reassign cluster id's for all clusters in the plain)
   class Plane:
     holds Cluster objects and a matrix of distances between them.
     able to merge two clusters and update the distance matrix
     implements the algorithm
 */

using namespace std;

struct inputParser
{
  string method;
  int boundary;
  vector< std::pair<double, double> > points;
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
      parser.points.push_back(std::make_pair(x, y));
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
    stream << (*it)->clusterId << endl;
  return stream.str();
}

int main()
{
  inputParser parser = readAndParseInput("input.txt");
  Plain* plain = Plain::factory(parser.method);
  for (vector< std::pair<double,double> >::iterator it=parser.points.begin(); it != parser.points.end(); it++)
    plain->addNewPoint((*it).first, (*it).second);
  plain->executeHierarchicalClustering(parser.boundary);
  string result = convertPlainToOutputStr(plain);
  writeResults("output.txt", result);
  return 1;
}
