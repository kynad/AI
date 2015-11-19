#include "Cell.h"
using namespace std;

void cell::set_neighbor(int dir,cell* adress){ //takes the true natural visual direction and correct's it for the array.
    this->neighbors[dir-1] = adress;
}


cell::cell(const int cost){
    int i;
    this->cost = cost;
    for(i=0;i<9;i++)
        this->neighbors[i] = NULL;
    this->set_neighbor(5,this);
    cout <<endl << "end of the ctor" << endl;
}


cell::~cell(){
    cout<< "in the dctor nothing to free here"<<endl;
}

int cell::get_cost(){
    return(this->cost);
}


cell* cell::get_neighbor(const int dir){
    return(this->neighbors[dir-1]);
}
