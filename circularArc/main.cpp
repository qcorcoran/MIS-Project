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
    //struct timespec startTime, endTime;

	//make the graph object
	circularArcGraph* g = new circularArcGraph();

    //read the file and create the arcs
    g->readData();

    //timing starts here
    //clock_gettime(CLOCK_REALTIME, &startTime);

    //now sort based on angel theta
    //sort by start points for the L(G)^2 function
    g->mergesort(0, g->getSize()-1, "start");

    //then create L(G)^2
    g->createLineGraph();

    //now sort the L(G)^2 by the endpoints for the MIS function
    g->mergesort(0, g->getSize()-1, "end");

    //set the next values for each arc
    g->initNext();

    //debug print of the current ordered set of arcs with their start point, end point, and their next values
    for(int i=0; i < g->getSize(); i++){
        cout<<g->getArc(i)->getLineNum()<<":"<<g->getArc(i)->getStartTheta()<<":"<<g->getArc(i)->getEndTheta()<<":"<<g->getArc(i)->getNext()->getLineNum()<<" ";
    }
    cout<<endl<<endl;
    
    //TODO run MIS algorithm

    //timing ends here
    /*clock_gettime(CLOCK_REALTIME, &endTime);
    //calculate time to run the algorithm
    long seconds = endTime.tv_sec - startTime.tv_sec;
    long nanoseconds = endTime.tv_nsec - startTime.tv_nsec;
    double finalTime = seconds + nanoseconds*1e-9;*/

    //add runtime to times file
    /*
    ofstream timeStream;
    timeStream.open("times.txt", ios_base::app);
    timeStream<<"n="<<g->getN()<<" time="<<finalTime<<"sec\n";
    timeStream.close();
    */

    //output final result
    //cout<<g->getMimSize()<<endl;

    return 0;
}
