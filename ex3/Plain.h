#include <iostream>
#include <math.h>
#include <float.h>
#include <stdio.h>
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
  virtual ~Plain();
  void addNewPoint(double x, double y);
  void executeHierarchicalClustering(int boundary);
  std::vector<Point*> getPoints() { return points;};
  Cluster* mergeClusters(int firstId, int secondId);
  virtual double clusterDistance(Cluster* one, Cluster* two, Cluster* target) = 0;
  std::pair<int,int> findMinDistanceIndices();
};

class SingleLinkPlain : public Plain
{
public:
  virtual double clusterDistance(Cluster* one, Cluster* two, Cluster* target);
  virtual ~SingleLinkPlain() {};
};

class AverageLinkPlain : public Plain
{
public:
  virtual double clusterDistance(Cluster* one, Cluster* two, Cluster* target);
  virtual ~AverageLinkPlain() {};
};

