//Quinn Corcoran
//permutation

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char** argv){
    //check that correct number of arguments was passed in
    if(argc < 3){
        cout<<"usage: verify file1 file2"<<endl;
        return 1;
    }

    //initialize variables
    fstream fs;
    string fileName1 = argv[1];
    string fileName2 = argv[2]; 
    string answer1 = "";
    string answer2 = "";

    //read first file into a string
    fs.open(fileName1.c_str());
    if(!fs.is_open()){
        cout<<"file "<<fileName1<<" does not exist"<<endl;
        return 1;
    }
    else{
        fs >> answer1;
    }
    fs.close();

    //read second file into a string
    fs.open(fileName2.c_str());
    if(!fs.is_open()){
        cout<<"file "<<fileName2<<" does not exist"<<endl;
        return 1;
    }
    else{
        fs >> answer2;
    }
    fs.close();

    //compare the two answers
    if(answer1 == answer2){
        cout<<"VERIFIED"<<endl;
    }
    else{
        cout<<"ANSWERS ARE NOT THE SAME"<<endl;
    }

    return 0;
}
