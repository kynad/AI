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

  public:
  Cluster(Point* point) {points.push_back(point); id = point->clusterId;};
};
