#include <sstream>

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
  return stream.str();
}
