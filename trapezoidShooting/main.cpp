//Quinn Corcoran

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "graph.h"
#include "trapezoid.h"
#include "point.h"
#include "splayTree.h"

using namespace std;

int main(int argc, char** argv){
    //struct to time the algorithm
    struct timespec startTime, endTime;

	//make the graph object
	graph* g = new graph();

    //read in data from the file
    g->readData();

    //timing starts here
    clock_gettime(CLOCK_REALTIME, &startTime);
    g->mergesort(0, g->getBoxesSize()-1);

    //runs the sweepline across the box representation
    g->sweepLine();        
    
    //timing ends here
    clock_gettime(CLOCK_REALTIME, &endTime);
    //calculate time to run the algorithm
    long seconds = endTime.tv_sec - startTime.tv_sec;
    long nanoseconds = endTime.tv_nsec - startTime.tv_nsec;
    double finalTime = seconds + nanoseconds*1e-9;

    //add runtime to times file
    ofstream timeStream;
    timeStream.open("times.txt", ios_base::app);
    timeStream<<"n="<<g->getSize()<<" time="<<finalTime<<"sec\n";
    timeStream.close();

    //output final result
    cout<<g->getMisSize()<<endl;

    return 0;
}
