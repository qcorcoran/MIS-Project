//Quinn Corcoran
//building

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "neighborhood.h"
#include "graph.h"
#include "graphNode.h"

using namespace std;

int main(int argc, char** argv){
    //struct to time the algorithm
    //struct timespec startTime, endTime; 

	//make graph object
	neighborhood* nb = new neighborhood();

    //read from the input file
    nb->readData();
    cout<<"read"<<endl;

    //timing starts here
    //clock_gettime(CLOCK_REALTIME, &startTime);
    //sort the array using mergesort
    nb->mergesort(0, nb->getNumBoxes()-1);
    cout<<"sorted"<<endl;
    
    //initialize the graph nodes
    nb->buildGraph();
    cout<<"graph built"<<endl;

    nb->getGraph()->dfs(0);
    cout<<"ran dfs"<<endl;

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
    delete nb;

    return 0;
}
