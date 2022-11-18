//Quinn Corcoran
//navigatingRiver

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "river.h"
#include "point.h"
#include "graph.h"
#include "graphNode.h"
#include "splayTree.h"
#include "splayNode.h"

using namespace std;

int main(int argc, char** argv){
    //struct to time the algorithm
    //struct timespec startTime, endTime; 
	
	//make graph object
	river* r = new river();

    //read from the input file
    r->readData();
    cout<<"read"<<endl;

    //timing starts here
    //clock_gettime(CLOCK_REALTIME, &startTime);
    //sort the array using mergesort
    r->mergesort(0, r->getNumPoints()-1);
    cout<<"sorted"<<endl;
    
    //initialize the graph nodes
    r->initGraph();
    cout<<"graph nodes made"<<endl;

    r->findBestDiameter();
    cout<<"found diameter"<<endl;

    /*
    //timing ends here
    clock_gettime(CLOCK_REALTIME, &endTime);
    //calculate time to run the algorithm
    long seconds = endTime.tv_sec - startTime.tv_sec;
    long nanoseconds = endTime.tv_nsec - startTime.tv_nsec;
    double finalTime = seconds + nanoseconds*1e-9;

    //add runtime to times file
    ofstream timeStream;
    timeStream.open("times.txt", ios_base::app);
    timeStream<<"n="<<r->getNumPoints()<<" time="<<finalTime<<"sec\n";
    timeStream.close();
    */

    //output the final result

    //deallocate the river
    delete r;

    return 0;
}
