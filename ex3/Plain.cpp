#include "Plain.h"

using namespace std;

/**
 * Factory method. Creates eithre SingleLinkPlain, or AverageLinkPlain objects, based on the given string
 * @return a pointer to the created object.
 */
Plain* Plain::factory(string method)
{
  char *prefix;
  sscanf(method.c_str(), "%s", prefix);
  // TODO: strip instead
  string word(prefix);
  if (word == "single") 
    return new SingleLinkPlain();
  else if (word == "average")
    return new AverageLinkPlain();
  cout << "Method '"  << method << "' is not supported." << endl;
  throw "";
}

/**
 * Constructs a new point from the given coordinates and a new cluster.
 * Adds that point to the list of points and to that new cluster. Also, adds the cluster to it's list of clusters
 * Adds a new row and column to the distance table and fills it 
 *  with distances to all points that were already part of this plain.
 */
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

/**
 * Basic dtor. Deletes the distances matrix.
 */
Plain::~Plain()
{
  for (int i = 0; i < clusters.size(); i++)
    delete distances;
  delete [] distances;
}

/**
 * An implementation of eucledian distance calculation.
 */
double Plain::metric(Point* one, Point* two)
{
  if (one->id == two->id)
    return 0;
  return sqrt(pow((one->x - two->x), 2) + pow((one->y - two->y), 2));
}

/**
 * Constructs a new cluster that contains all points from the given clusters.
 * Removes the given clusters from list of clusters, adds this cluster instead.
 * Updates the distance table.
 * @returns a pointer to the new cluster.
 */
Cluster* Plain::mergeClusters(int firstId, int secondId)
{
  if (firstId == secondId)
  {
    cout << "Error: trying to merge " << firstId << "th cluster with itself." << endl;
    throw "";
  }

  /*cout << "Debug: merging cluster " << firstId << " with cluster " << secondId << endl;*/

  // 0. get clusters by id from the vector
  Cluster* one = clusters[firstId];
  Cluster* two = clusters[secondId];
  // 1. merge the two clusters using the "copy ctor"
  Cluster* cluster = new Cluster(one, two);
  // 2. update the distances table
  int id = cluster->getId();
  int maxId = (firstId > secondId) ? firstId : secondId;
  for (vector<Cluster*>::iterator it = clusters.begin(); it != clusters.end(); it++)
  {
    int otherId = (*it)->getId();
    double distance = clusterDistance(one, two, (*it));
    this->distances[id][otherId] = distance;
    this->distances[otherId][id] = distance;
  }
  // 3. Replace the argmin(id) cluster in the vector and remove the argmax(id)
  clusters[id] = cluster;
  clusters.erase(clusters.begin() + maxId); // Note that erase is O(vector.size()).
  for (vector<Cluster*>::iterator it = clusters.begin() + maxId; it != clusters.end(); it++)
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
  return cluster;
}

/**
 * @return argmin{distances[i][j]}
 */
pair<int,int> Plain::findMinDistanceIndices()
{
  pair<int,int> result;
  double minDistance = DBL_MAX;
  for (int i = 0; i < clusters.size(); i++)
    for (int j = i+1; j < clusters.size(); j++)
      if (distances[i][j] < minDistance) {
	/* cout << "Debug: found new minimum: " << i << "," << j << endl; */
	minDistance = distances[i][j];
	result = make_pair(i,j);
      }
  return result;
}

/**
 * Performs Hierarchical Clustering on this plain.
 */
void Plain::executeHierarchicalClustering(int boundary)
{
  while (boundary < clusters.size())
  {
    pair<int,int> minIndices = findMinDistanceIndices();
    mergeClusters(minIndices.first, minIndices.second);
  }
}

/**
 * Implementation of the distance between cluster for single-link approach.
 * @returns min{d(one,target), d(two, target)}
 */
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

/**
 * Implementation of the distance between cluster for average-link approach.
 * @returns 
 *          d(one,target)*|one| + d(two, target)*|two|
 *          ------------------------------------------  
 *                        |one| + |two|
 */
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
