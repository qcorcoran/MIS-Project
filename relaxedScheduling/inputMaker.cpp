//Quinn Corcoran
//relaxedScheduling

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <assert.h>

#define RANDMAX 32767

using namespace std;

int main(int argc, char** argv){
    //declare local variables
    string infile = "input.txt";
    string ansfile = "answer.txt";
    ifstream myfile;
    int intervals = 0;
    int currentStartpoint = -1;
    int currentEndpoint = -1;
    int start = 0;
    int end = 0;
    int mis = 0;
    int jMax = 0;
    int range = 0;

    //initialize random seed
    //srand(time(NULL));
    srand(0);

    //prompt user for input
    /*
    cout<<"Enter name of input file to create: ";
    cin>>infile;
    cout<<"Enter name of answer file to create: ";
    cin>>ansfile;
    */
    cout<<"Enter number of intervals to create: ";
    cin>>intervals;

    //create and open input file
    ofstream iFile(infile.c_str());

    //write the number of intervals to the input file
    iFile << intervals << "\n";

    //create the given number of intervals
    for(int i=0; i < intervals; i++){
        //set currentStartpoint to be greater than currentEndpoint
        currentStartpoint = (rand() % RANDMAX) + (currentEndpoint+1);
        assert(currentStartpoint > currentEndpoint);
        //set currentEndpoint to be greater than currentStartpoint
        currentEndpoint = (rand() % RANDMAX) +(currentStartpoint+1);
        assert(currentEndpoint > currentStartpoint);
        //write the MIS interval to the input file
        iFile << currentStartpoint << " " << currentEndpoint << "\n";
        //increase the MIS
        mis++;
        //set jMax to a random number less than intervals
        jMax = rand() % (intervals-1);
        assert(jMax < intervals);
        for(int j=0; j < jMax && j+i+1 < intervals; j++){
            //set start to be greater than currentStartpoint and less than currentEndpoint
            range = (currentEndpoint-1) - (currentStartpoint+1) + 1;
            start = (rand() % range) + (currentStartpoint+1);
            //set end to be greater than currentEndpoint
            end = (rand() % RANDMAX) + (currentEndpoint+1);
            //write the nonMIS interval to the input file
            iFile << start << " " << end << "\n";
            //asserts for correctness
            assert(start < currentEndpoint);
            assert(start > currentStartpoint);
            assert(end > currentEndpoint);
            //increment i because we have made a new interval
            i++;
        }
    }
    //close the input file
    iFile.close();

    //create and open answer file
    ofstream aFile(ansfile.c_str());

    //write the solution to the answer file
    aFile << mis << "\n";

    //close the answer file
    aFile.close();

    return 0;
}
