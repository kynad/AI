#include <sstream>
#include "Plain.h"

class Definitions
{
public:
  static std::string plainDivisionToString(Plain& plain);
};

std::string Definitions::plainDivisionToString(Plain& plain)
{
  std::stringstream stream;
  stream << plain.getDistanceMethod() << std::endl << plain.getClusterBoundary() << std::endl;
  stream << "number of points: " << plain.clusterNum() << std::endl;
  for (std::vector<Cluster*>::iterator it = plain.begin(); it != plain.end(); it++)
    stream << (*it)->getId() << std::endl;
  return stream.str();
}
