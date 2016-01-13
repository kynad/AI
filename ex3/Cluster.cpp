#include "Cluster.h"

using namespace std;

/**
 * updates the clusterId field of all the points in the cluster (to be this cluster's id)
 */
void Cluster::updateId()
{
  for (vector<Point*>::iterator it = points.begin(); it != points.end(); it++)
    (*it)->clusterId = id;
}

/**
 * Basic ctor
 */
Cluster::Cluster(Point* point, int id) : id(id)
{
  points.push_back(point);
  updateId();
}

/**
 * Kind of like copy ctor, this ctor constructs a cluster by merging two given clusters.
 */
Cluster::Cluster(Cluster* one, Cluster* two)
{
  vector<Point*> onePoints = one->getPoints(); // This sucks.
  vector<Point*> twoPoints = two->getPoints(); // I should pass by reference here, to avoid extra copying.
  points.reserve(onePoints.size() + twoPoints.size());
  points.insert(points.end(), onePoints.begin(), onePoints.end());
  points.insert(points.end(), twoPoints.begin(), twoPoints.end());
  int oneId, twoId = two->getId();
  oneId = one->getId();
  id = (oneId < twoId) ? oneId : twoId;
  updateId();
}
