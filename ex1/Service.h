#include <iostream>
#include <fstream>
#include <stdlib.h>

class service
{
  public:
    ~service(); //destroyer function
    service(std::string input_path); //will initialize the file_path.
    std::string* input(std::string input_path); //will return the string, will initialize the algorithm
    void output(std::string output_path, std::string output); //will write the single line data.
    int size=0;
    std::string algorithm ="none";
    std::string path;
};
