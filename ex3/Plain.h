#include <vector>
#include <math.h>
#include "Cluster.h"

class Plain
{
private:
  std::vector<Point*> points;
  std::vector<Cluster*> clusters;
  double** distances;
  double metric(Point* one, Point* two);

public:
  static Plain* factory(std::string method);
  //  Plain();
  ~Plain();
  void addNewPoint(double x, double y);
  void executeHierarchicalClustering(int boundary) {};
  std::vector<Point*> getPoints() { return points;};
};

void Plain::addNewPoint(double x, double y)
{
  int id = points.size()+1;
  Point* point = new Point();
  point->id = id;
  point->x = x;
  point->y = y;
  points.push_back(point);
  Cluster* cluster = new Cluster(point); 
  clusters.push_back(cluster);
  // copy the distances table
  double** distances = new double*[id*sizeof(double)];
  for (int i=0; i < id-1; i++)
  {
    distances[i] = new double[id*sizeof(double)];
    for (int j=0; j < id-1; j++)
      distances[i][j] = this->distances[i][j];
    delete this->distances[i];
  }
  // add row and column to distance matrix and fill them up.
  distances[id-1] = new double[id*sizeof(double)];
  for (int j=0; j < id; j++)
  {
    double distance = metric(point, points[j]);
    distances[id-1][j] = distance;
    distances[j][id-1] = distance;
  }
  delete [] this->distances;
  this->distances = distances;

  // debug:
 /**
  for (int i = 0; i < id; i++) {
    for (int j = 0; j < id; j++)
      std::cout << this->distances[i][j] << " ";
    std::cout << std::endl;
  } */
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
  return sqrt(pow((one->x + two->x), 2) + pow((one->y + two->y), 2));
}

Plain* Plain::factory(std::string method)
{
  return new Plain();
}

