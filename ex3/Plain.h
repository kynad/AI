#include <vector>
#include "Cluster.h"
#include "Definitions.h"

class Plain
{
private:
  std::string distanceMethod;
  int clusterBoundary;
  std::vector<Cluster*> clusters;
  int** distances;

public:
  void init(std::string method, int boundary) {distanceMethod = method; clusterBoundary = boundary;};
  void addNewPoint(double x, double y) {int id = Definitions::getPointId(); Point point(id, id, x,y); Cluster cluster(&point); clusters.push_back(&cluster);};
  void executeHierarchicalClustering() {};
  
  std::string getDistanceMethod() {return distanceMethod;};
  double getClusterBoundary() {return clusterBoundary;};
  int clusterNum() {return clusters.size();};
};
