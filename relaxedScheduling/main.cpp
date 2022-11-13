//Quinn Corcoran

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "graph.h"
#include "interval.h"

using namespace std;

int main(int argc, char** argv){
    //struct to time the algorithm
    struct timespec startTime, endTime; 
	
	//make graph object
	graph* g = new graph();

    //read from the input file
    g->readData();

    //timing starts here
    clock_gettime(CLOCK_REALTIME, &startTime);
    //sort the array using mergesort
    g->mergesort(0, g->getSize()-1);
    //run the actual MIS algorithm
    g->runMIS();
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

    //output the final result
    cout<<g->getMisSize()<<endl;

    return 0;
}
