#include <vector>

struct Point
{
  int id, clusterId;
  double x,y;
};

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


