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
    string st;
    ifstream fi ("input.txt");
    //char* temp = input_path.c_str();
    const char* c = input_path.c_str(); //ifstream takes const char* and we need to convert
    ifstream fi1 (c);
    const char* num;
    string* path = new string;


    //while (std::getline(f,st))
    //    cout<<st;

    if(fi1.is_open())
    {
        getline(fi1,st);
        cout<<st<<endl;
        if  (st=="ids")
            algorithm = "ids";
        else
            algorithm = "dfs";


        getline(fi1,st); //gets the second line of file assuming it's the size
        cout<<st<<endl; //check
        num = st.c_str(); //convert to char* in order to use atoi
        this->size = atoi(num); //convert to int by atoi


        while(!fi1.eof())
        {
            getline(fi1,st);
            cout<<st<<endl;
            *path += st; //we will keep this path in order to load the matrix.
        }
    }
    else
        cout<<"somthing went wrong with the file boss.";



    cout << *path << endl; //just a check for the full matrix path.
    this->path = *path;
    cout << this->path; //check that the path was entered correctly to the member path
    return(path);

}; //will return the string, will initialize the algorithm
//void service_class::output(std::string output_path, std::vector<string> output){}; //will write the data to the output file.
