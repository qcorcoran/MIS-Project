//Quinn Corcoran
//giftsGiving

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "tree.h"
#include "node.h"

using namespace std;

int main(int argc, char** argv){
    //struct to time the algorithm
    struct timespec startTime, endTime; 
	
	//make tree object
	tree* t = new tree();

    //read from the input file
    t->readData();

    //timing starts here
    clock_gettime(CLOCK_REALTIME, &startTime);

    //this runs the brute force algorithm
    t->bruteForce();
    
    //timing ends here
    clock_gettime(CLOCK_REALTIME, &endTime);
    //calculate time to run the algorithm
    long seconds = endTime.tv_sec - startTime.tv_sec;
    long nanoseconds = endTime.tv_nsec - startTime.tv_nsec;
    double finalTime = seconds + nanoseconds*1e-9;

    //add runtime to times file
    ofstream timeStream;
    timeStream.open("bruteTimes.txt", ios_base::app);
    timeStream<<"n="<<t->getSize()<<" time="<<finalTime<<"sec\n";
    timeStream.close();
    
    //sort MIS list from greatest to least
    t->mergesort(0, t->getMisSize()-1, "mis");
    //output the final result
    cout<<t->getMisSize()<<endl;
    for(int i=0; i < t->getMisSize(); i++){
        cout<<t->getMis(i)<<" ";
    }
    cout<<"\n";

    //free up memory
    delete t;

    return 0;
}