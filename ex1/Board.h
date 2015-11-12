/**
 * Description - TODO:
 */

#include <iostream>
#include <boost/regex.hpp>

class Board 
{
  const char* ALLOWED_CHARS="SGRDHW";

  private:
    int _size;
    char **_map;
    boost::regex validationRegex;
    void checkInput(std::string mapAsSingleString);
    std::string IDS();
    std::string UCS();

  public:
    Board(int size, std::string mapAsSingleString);
    ~Board();
    std::string findPath(std::string algorithmName);
    void print();
};

