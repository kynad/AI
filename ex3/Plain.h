#include <vector>
#include <math.h>
#include <float.h>
#include "Cluster.h"

class Plain
{
protected:
  std::vector<Point*> points;
  std::vector<Cluster*> clusters;
  double** distances;
  double metric(Point* one, Point* two);

public:
  static Plain* factory(std::string method);
  ~Plain();
  void addNewPoint(double x, double y);
  void executeHierarchicalClustering(int boundary);
  std::vector<Point*> getPoints() { return points;};
  Cluster* mergeClusters(int firstId, int secondId);
  virtual double clusterDistance(Cluster* one, Cluster* two, Cluster* target) = 0;
  std::pair<int,int> findMinDistanceIndices();
  void printDistances();
};

class SingleLinkPlain : public Plain
{
public:
  double clusterDistance(Cluster* one, Cluster* two, Cluster* target);
};

class AverageLinkPlain : public Plain
{
public:
  double clusterDistance(Cluster* one, Cluster* two, Cluster* target);
};

Plain* Plain::factory(std::string method)
{
  char *prefix;
  sscanf(method.c_str(), "%s", prefix);
  std::cout << prefix << std::endl;
  // TODO: strip instead
  std::string word(prefix);
  if (word == "single") 
    return new SingleLinkPlain();
  else if (word == "average")
    return new AverageLinkPlain();
  std::cout << "Method '"  << method << "' is not supported." << std::endl;
  throw "";
}

void Plain::addNewPoint(double x, double y)
{
  int id = points.size();
  Point* point = new Point();
  point->id = id;
  point->x = x;
  point->y = y;
  points.push_back(point);
  Cluster* cluster = new Cluster(point, id); 
  clusters.push_back(cluster);
  // copy the distances table
  double** distances = new double*[id*sizeof(double)];
  for (int i=0; i < id; i++)
  {
    distances[i] = new double[id*sizeof(double)];
    for (int j=0; j < id; j++)
      distances[i][j] = this->distances[i][j];
    delete this->distances[i];
  }
  // add row and column to distance matrix and fill them up.
  distances[id] = new double[id*sizeof(double)];
  for (int j=0; j < id+1; j++)
  {
    double distance = metric(point, points[j]);
    distances[id][j] = distance;
    distances[j][id] = distance;
  }
  delete [] this->distances;
  this->distances = distances;

}

void Plain::printDistances()
{
  // debug:
  for (int i = 0; i < clusters.size(); i++) {
    for (int j = 0; j < clusters.size(); j++)
      std::cout << this->distances[i][j] << "\t";
    std::cout << std::endl;
  }
}

Plain::~Plain()
{
  for (int i = 0; i < clusters.size(); i++)
    delete distances;
  delete [] distances;
}

double Plain::metric(Point* one, Point* two)
{
  if (one->id == two->id)
    return 0;
  return sqrt(pow((one->x - two->x), 2) + pow((one->y - two->y), 2));
}

Cluster* Plain::mergeClusters(int firstId, int secondId)
{
  if (firstId == secondId)
  {
    std::cout << "Error: trying to merge " << firstId << "th cluster with itself." << std::endl;
    throw "";
  }
  std::cout << "Debug: merging cluster " << firstId << " with cluster " << secondId << std::endl;
  // 0. get clusters by id from the vector
  Cluster* one = clusters[firstId];
  Cluster* two = clusters[secondId];
  // 1. merge the two clusters using the "copy ctor"
  Cluster* cluster = new Cluster(one, two);
  // 2. update the distances table
  int id = cluster->getId();
  int maxId = (firstId > secondId) ? firstId : secondId;
  for (std::vector<Cluster*>::iterator it = clusters.begin(); it != clusters.end(); it++)
  {
    int otherId = (*it)->getId();
    double distance = clusterDistance(one, two, (*it));
    this->distances[id][otherId] = distance;
    this->distances[otherId][id] = distance;
  }
  // 3. Replace the argmin(id) cluster in the vector and remove the argmax(id)
  clusters[id] = cluster;
  clusters.erase(clusters.begin() + maxId); // Note that erase is O(vector.size()).
  for (std::vector<Cluster*>::iterator it = clusters.begin() + maxId; it != clusters.end(); it++)
    (*it)->decreaseId();
  // 4. remove a row and a column in the distance 
  int size = clusters.size();
  double** distances = new double*[size*sizeof(double)];
  // copy until maxId
  for (int i=0; i < maxId; i++)
  {
    distances[i] = new double[size*sizeof(double)];
    for (int j=0; j < maxId; j++)
      distances[i][j] = this->distances[i][j];
    for (int j = maxId; j < size; j++)
      distances[i][j] = this->distances[i][j+1];
    delete this->distances[i];
  }
  // copy from maxId+1
  for (int i=maxId; i < size; i++)
  {
    distances[i] = new double[size*sizeof(double)];
    for (int j=0; j < maxId; j++)
      distances[i][j] = this->distances[i+1][j];
    for (int j=maxId; j < size; j++)
      distances[i][j] = this->distances[i+1][j+1];
    delete this->distances[i];
  }
  delete [] this->distances;
  this->distances = distances;
  // 5. delete the old clusters
  delete one;
  delete two;
  printDistances();
  return cluster;
}

std::pair<int,int> Plain::findMinDistanceIndices()
{
  std::pair<int,int> result;
  double minDistance = DBL_MAX;
  for (int i = 0; i < clusters.size(); i++)
    for (int j = i+1; j < clusters.size(); j++)
      if (distances[i][j] < minDistance) {
	std::cout << "Debug: found new minimum: " << i << "," << j << std::endl;
	minDistance = distances[i][j];
	result = std::make_pair(i,j);
      }
  return result;
}

void Plain::executeHierarchicalClustering(int boundary)
{
  while (boundary < clusters.size())
  {
    std::pair<int,int> minIndices = findMinDistanceIndices();
    mergeClusters(minIndices.first, minIndices.second);
  }
}

double SingleLinkPlain::clusterDistance(Cluster* one, Cluster* two, Cluster* target)
{
  int firstId = one->getId();
  int secondId = two->getId();
  int targetId = target->getId();
  if (firstId == targetId || secondId == targetId)
    return 0;
  double distance1 = distances[firstId][targetId];
  double distance2 = distances[secondId][targetId];
  return (distance1 < distance2) ? distance1 : distance2;
}

double AverageLinkPlain::clusterDistance(Cluster* one, Cluster* two, Cluster* target)
{
  int firstId = one->getId();
  int secondId = two->getId();
  int firstSize = one->size();
  int secondSize = two->size();
  int targetId = target->getId();
  if (firstId == targetId || secondId == targetId)
    return 0;
  double distance1 = distances[firstId][targetId];
  double distance2 = distances[secondId][targetId];
  return (distance1*firstSize + distance2*secondSize)/(firstSize + secondSize);
}
