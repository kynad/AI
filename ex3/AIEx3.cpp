#include <iostream>
#include <fstream>
#include <iostream>
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
   A: Average-link is Sum(Sum(d(pi,pj)))/(|C1|*|C2|). You can hold for every p, the Sp = Sum_i(d(pi,p))/|C| for pi in C, then to obtain the distance between C1, C2, you just need to calculate Sum(Sp)/|C2| for p in C2.
  
   Q: Should clusters have their own matrices with distance to all the other clusters, or should they derive these distances from the points distance table?
   A: This is time-space tradeoff. I prefer to save memory at this point.



   high-level:
   1. Main class will contain the usual: input parser and output writer, Point struct/class definition and the main function
   2. Definitions class will hold everything that is exercise dependand - distance between points, distance between clusters, single-link, average-link, points id assigner.
   3. Point class/struct will represent a point
   3. Cluster class will represent a cluster
   4. Plane class will represent the plain - an array of clusters and their distance table (matrix)


   class/struct Point:
     should have id and cluster id. both initialized to the same (given) value
     holds it's x and y coordinates.
   class Cluster:
     should have an id and a list of contained Point* objects. The id is expected to be the minimal point id of all points contained in the cluster 
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
void readAndParseInput(const char* inputPath, Plain& plain)
{
  ifstream input(inputPath);

  if(input.is_open())
  {
    string line, method;
    
    // get the distance calculation method
    getline(input, method);

    // get the number of clusters
    getline(input, line);
    int clusterNum = atoi(line.c_str());

    // init the plain object
    plain.init(method, clusterNum);

    // parse the rest of the lines, construct points from each and add them to the plain
    while (getline(input, line))
    {
      double x,y;
      sscanf(line.c_str(), "%lf,%lf", &x, &y);
      plain.addNewPoint(x,y);
    }
  }
  else
  {
    cout << "Couldn't open the input file, aborting" << endl;
    throw "";
  }  
}


int main()
{
  Plain plain;
  readAndParseInput("input.txt", plain);
  plain.executeHierarchicalClustering();
  string result = Definitions::plainDivisionToString(plain);
  writeResults("output.txt", result);
  return 1;
}
