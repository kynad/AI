#include "Board.h"
#include "Service.h"
using namespace std;

int main()
{
  cout << "creating and initializing the board" << endl;
  Board board = Board(5,"SRWWWRRRDWRRRDWRRRDWDDRRG");
  cout << "printing the board:" << endl;
  board.print();
  cout << "calling the IDS algorithm" << endl;
  string res = board.findPath("IDS");
  cout << "recieved the following result: " << res << endl;
    string shai = "input.txt";
    service* shai1;
    shai1 = new service(shai);
    cell* shai5;
    shai5 = new cell(4);
    cout << "my cost is " << shai5->get_cost();
    cout << "my adress is " << shai5->get_neighbor(5);

    cout << "Hello world!" << endl;
    shai1->input("input.txt");
    shai1->output("output.txt","shai the king \n\n\n\n shai the king 2q");
    delete(shai1);

  return 0;
}
