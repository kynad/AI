#include "Board.h"
#include "Service.h"
using namespace std;

int main()
{
    string shai = "input.txt";
    service* shai1;
    shai1 = new service(shai);
    cell* shai5;
    shai5 = new cell(4);
    cout << "my cost is " << shai5->get_cost();
    cout << "my adress is " << shai5->get_neighbor(5);

    cout << "Hello world!" << endl;
    shai1->input("input.txt");

    cout << "creating and initializing the board" << endl;
    Board board = Board(5,shai1->path);
    cout << "printing the board:" << endl;
    board.print();
    cout << "calling the " << shai1->algorithm << " algorithm" << endl;
    string res = board.findPath(shai1->algorithm);
    cout << "recieved the following result: " << res << endl << "compare that to output.txt" << endl;
    shai1->output("output.txt",res);
    delete(shai1);

  return 0;
}
