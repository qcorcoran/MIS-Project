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
    struct timespec startTime, endTime; 

	//make neighborhood object
	neighborhood* nb = new neighborhood();

    //read from the input file
    nb->readData();

    //timing starts here
    clock_gettime(CLOCK_REALTIME, &startTime);

    //sort the array using mergesort
    nb->mergesort(0, nb->getNumBoxes()-1);

    //create the graph nodes and edges
    nb->buildGraph();

    //run modified dfs
    nb->getGraph()->dfs(0, -1);

    //timing ends here
    clock_gettime(CLOCK_REALTIME, &endTime);
    //calculate time to run the algorithm
    long seconds = endTime.tv_sec - startTime.tv_sec;
    long nanoseconds = endTime.tv_nsec - startTime.tv_nsec;
    double finalTime = seconds + nanoseconds*1e-9;

    //add runtime to times file
    ofstream timeStream;
    timeStream.open("times.txt", ios_base::app);
    timeStream<<"n="<<nb->getNumBoxes()<<" time="<<finalTime<<"sec\n";
    timeStream.close();

    //output the final result
    cout<<nb->getGraph()->getNumPaths()<<"\n";
    for(int i=0; i < nb->getGraph()->getNumPaths(); i++){
        cout<<nb->getGraph()->getPath(i);
    }

    //deallocate the river
    delete nb;

    return 0;
}
