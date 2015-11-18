#include "Service.h"
using namespace std;

service::service(std::string input_path){cout<<"made";}
service::~service(){cout<<"dest";} //destroyer function
void service::output(std::string output_path, std::string output){
    FILE* f = fopen(output_path.c_str(),"w");
    int i = 0;
    if(f)
        while(output[i])
            fputc(output[i++],f);
   fclose(f);




}

string* service::input(std::string input_path){
    //FILE* f = fopen(input_path.c_str(),"r");
    //if(!f) return(NULL); //in case of error.
    string st = "";
    ifstream fi ("input.txt");
    //char* temp = input_path.c_str();
    const char* c = input_path.c_str(); //ifstream takes const char* and we need to convert
    ifstream fi1 (c);
    const char* num;
    string* path = new string("");
    string r_string("");
    //char* shaitest = "bar ilan loves kfia datit";
    //cout << shaitest;
    //cout << shaitest;
    //ostream os;

    //while (std::getline(f,st))
    //    cout<<st;

    if(fi1.is_open())
    {
        getline(fi,st);
        cout<<"first line is " <<st<<endl;
        if  (st=="ids")
            algorithm = "ids";
        else
            algorithm = "dfs";


        getline(fi,st); //gets the second line of file assuming it's the size
        cout<<"second line is "<<st<<endl; //check
        num = st.c_str(); //convert to char* in order to use atoi
        this->size = atoi(num); //convert to int by atoi

        while (getline(fi,st))
        {

            st = st.substr(0,this->size);
            (*path).append(st);
            fflush(stdout);
        }
    }
    else
        cout<<"somthing went wrong with the file boss.";



    //cout << *path << endl; //just a check for the full matrix path.
    this->path = *path;
    cout << "full map as single string:" << endl << this->path << endl; //check that the path was entered correctly to the member path
    return(path);

}; //will return the string, will initialize the algorithm

