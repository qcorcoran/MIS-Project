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
#include "bst.h"
#include "node.h"

using namespace std;

int main(int argc, char** argv){
    //struct to time the algorithm
    struct timespec startTime, endTime; 
	
	//make graph object
	river* r = new river();

    //read from the input file
    r->readData();

    //timing starts here
    clock_gettime(CLOCK_REALTIME, &startTime);
    //sort the array using mergesort
    r->mergesort(0, r->getSize()-1);

    bst* b = new bst();
    for(int i=0; i < r->getSize(); i++){
        cout<<"("<<r->getPoint(i)->getX()<<", "<<r->getPoint(i)->getY()<<")"<<" | ";
        b->insert(new node(r->getPoint(i)), b->getRoot());
    }
    cout<<endl;
    b->preorderTraversal(b->getRoot());
    cout<<endl;


    
    //timing ends here
    clock_gettime(CLOCK_REALTIME, &endTime);
    //calculate time to run the algorithm
    long seconds = endTime.tv_sec - startTime.tv_sec;
    long nanoseconds = endTime.tv_nsec - startTime.tv_nsec;
    double finalTime = seconds + nanoseconds*1e-9;

    //add runtime to times file
    ofstream timeStream;
    timeStream.open("times.txt", ios_base::app);
    timeStream<<"n="<<r->getSize()<<" time="<<finalTime<<"sec\n";
    timeStream.close();

    //output the final result

    //deallocate the river
    delete r;

    return 0;
}
