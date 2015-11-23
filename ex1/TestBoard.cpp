#include "Board.h"
#include "Service.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    string shai = "input.txt";
    service* shai1;
    shai1 = new service(shai);
    shai1->input("input.txt");

    cout << "creating and initializing the board" << endl;
    Board board = Board();
    board.init(shai1->size, shai1->path);
    string res = board.findPath(shai1->algorithm);
    cout << "recieved the following result: " << res << endl << "compare that to output.txt" << endl;
    shai1->output("output.txt",res);
    delete(shai1);

  return 0;
}
