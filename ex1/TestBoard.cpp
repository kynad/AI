#include "Board.h"
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
  return 1;
}
