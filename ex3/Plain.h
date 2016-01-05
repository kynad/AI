#include <vector>
#include "Cluster.h"

class Plain
{
private:
  std::string distanceMethod;
  int clusterBoundary;
  std::vector<Cluster*> clusters;
  int** distances;

public:
  void init(std::string method, int boundary) {distanceMethod = method; clusterBoundary = boundary;};
  void addNewPoint(double x, double y);
  void executeHierarchicalClustering() {};
  
  std::string getDistanceMethod() {return distanceMethod;}; //TODO: remove, it's for debugging only
  double getClusterBoundary() {return clusterBoundary;}; //TODO: remove, it's for debugging only
  int clusterNum() {return clusters.size();}; //TODO: remove, it's for debugging only
  std::vector<Cluster*>::iterator begin() { return clusters.begin();};
  std::vector<Cluster*>::iterator end() { return clusters.end();};
};

void Plain::addNewPoint(double x, double y)
{
  int id = clusters.size();
  Point* point = new Point();
  point->id = id;
  point->clusterId = id;
  point->x = x;
  point->y = y;
  Cluster* cluster = new Cluster(point); 
  clusters.push_back(cluster);
}
