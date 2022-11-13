//Quinn Corcoran

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <assert.h>
#include <time.h>

using namespace std;

int main(int argc, char** argv){
    //declare local variables
    ifstream myfile;
    stringstream isstream;
    isstream << "input878906.txt";
    string infile;
    isstream >> infile;
    stringstream asstream;
    asstream << "answer878906.txt";
    string ansfile;
    asstream >> ansfile;
    int numNodes = 878906;
    int mis[numNodes];
    int misSize = 0;

    //create and open input file
    ofstream iFile(infile.c_str());

    //write the number of nodes to the input file
    iFile << numNodes << "\n";

    mis[0] = 1;
    misSize++;
    int j = 2;
    int count = 0;
    int level = 2;
    int children = 5;
    int levelCheck = children;
    for(int i=1; i <= numNodes; i++){
        for(int k=1; k <= children; k++){
            iFile << i << " " << j << "\n";
            j++;
            count++;
            if(level % 2 != 0){
                mis[misSize] = j;
                misSize++;
            }
            if(j > numNodes){
                break;
            }
        }
        if(count == levelCheck){
            level++;
            if(level == 9){
                children = 10;
            }
            count = 0;
            levelCheck *= children;
        }
        if(j > numNodes){
                break;
        }
    }

    //close the input file
    iFile.close();

    //create and open answer file
    ofstream aFile(ansfile.c_str());

    //write the number of nodes to the answer file
    aFile << misSize << "\n";

    for(int i=misSize-1; i >= 0; i--){
        aFile << mis[i] << " ";
    }
    aFile << "\n";

    //close the answer file
    aFile.close();

    return 0;
}
