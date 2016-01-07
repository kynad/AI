/**  class Cluster:
     Should have an id and a list of contained Point* objects. 
     The id is expected to be the minimal point id of all points contained in the cluster.
     Should be able to merge between clusters, i.e. to have a "copy constructor" from two existing clusters.
     Need to update each point's clusterId once its id is updated
*/

#include "Point.h"

class Cluster
{
 private:
  int id;
  std::vector<Point*> points;
  void updateId();

 public:
  Cluster(Point* point, int id);
  Cluster(Cluster* one, Cluster* two);
  int getId() {return id;}
  std::vector<Point*> getPoints() { return points;};
  void decreaseId() {id--; updateId();};
  int size() {return points.size();};
};

void Cluster::updateId()
{
  for (std::vector<Point*>::iterator it = points.begin(); it != points.end(); it++)
    (*it)->clusterId = id;
}

Cluster::Cluster(Point* point, int id) : id(id)
{
  point->clusterId = id;
  points.push_back(point);
}

Cluster::Cluster(Cluster* one, Cluster* two)
{
  std::vector<Point*> onePoints = one->getPoints(); // This sucks.
  std::vector<Point*> twoPoints = two->getPoints(); // I should pass by reference here, to avoid extra copying.
  points.reserve(onePoints.size() + twoPoints.size());
  points.insert(points.end(), onePoints.begin(), onePoints.end());
  points.insert(points.end(), twoPoints.begin(), twoPoints.end());
  int oneId, twoId = two->getId();
  oneId = one->getId();
  id = (oneId < twoId) ? oneId : twoId;
  updateId();
}
