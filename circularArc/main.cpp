//Quinn Corcoran
//circularArc

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "circularArcGraph.h"
#include "arc.h"

using namespace std;

int main(int argc, char** argv){
    //struct to time the algorithm
    struct timespec startTime, endTime;

	//make the graph object
	circularArcGraph* g = new circularArcGraph();

    //read the file and create the arcs
    g->readData();

    //timing starts here
    clock_gettime(CLOCK_REALTIME, &startTime);

    //now sort the arcs by their endpoints for the next function
    g->mergesort(0, g->getSize()-1, "end");

    //set the next values for each arc
    g->initNext();
    
    //run MIS algorithm
    g->runMis();

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

    //deallocate the graph
    delete g;

    return 0;
}
