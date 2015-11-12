/**
 * Description - TODO:
 */

#include <iostream>

class Board 
{
  const std::string ALLOWED_CHARS="SGRDHW";

  private:
    int _size;
    char **_map;
    std::string IDS();
    std::string UCS();

  public:
    Board(int size, std::string mapAsSingleString);
    ~Board();
    std::string findPath(std::string algorithmName);
    void print();
};

