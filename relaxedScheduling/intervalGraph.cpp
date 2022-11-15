//Quinn Corcoran
//relaxedScheduling

#include "intervalGraph.h"

using namespace std;

//destructor
intervalGraph::~intervalGraph(){
    for(int i=0; i < n; i++){
        delete intervals[i];
    }
    delete[] intervals;
}

//read from an input file and create the intervals
void intervalGraph::readData(){
    //declare local variables
    string input = "";
    int intendedSize = 0;
    int start = 0;
    int end = 0;
    
    //read first line of input should be number of nodes
    cin>>input;
    istringstream issn(input);
    issn >> intendedSize;
    n = intendedSize;

    //dynamic array allocation
    intervals = new interval*[n];

    //read the rest of the input
    while(size < intendedSize){
        //set startPoint as first number and endPoint as second number
        cin>>input;
        istringstream isss(input);
        isss >> start;
        cin>>input;
        istringstream isse(input);
        isse >> end;
        //create the new interval
        interval* inter = new interval(start, end);
        //insert the interval into the intervals array
        intervals[size] = inter;
        size++;
    }
}

//run MIS algorithm for an interval graph
void intervalGraph::runMIS(){
    for(int i=0; i < size; i++){
        misSize++;
        i += conflictCheck(i);
    }
}

//checks for intervals that overlap the chosen interval and marks them as removed
int intervalGraph::conflictCheck(int index){
    int conflicts = 0;
    for(int i=index+1; i < size; i++){
        if(intervals[index]->endPoint >= intervals[i]->startPoint){
            conflicts++;
            continue;
        }
        break;
    }
    return conflicts;
}

//recursive mergesort
void intervalGraph::mergesort(int start, int end){
    //base case
    if(start >= end){
        return;
    }

    //set mid point of array
    int middle = start + (end - start)/2;

    //recursive calls to mergesort
    mergesort(start, middle);
    mergesort(middle+1, end);
    merge(start, middle, end);    
}

//merge helper function for mergesort
void intervalGraph::merge(int start, int middle, int end){
    //initialize local variables
    int sizeFirst = middle - start + 1;
    int sizeSecond = end - middle;
    int indexFirst = 0;
    int indexSecond = 0;
    int indexFull = start;

    //create temporary arrays
    interval** first = new interval*[sizeFirst];
    interval** second = new interval*[sizeSecond];
    //fill temporary arrays
    for(int i = 0; i < sizeFirst; i++){
        first[i] = intervals[start + i];
    }
    for(int i = 0; i < sizeSecond; i++){
        second[i] = intervals[middle + 1 + i];
    }

    //sort and store into intervals array
    while(indexFirst < sizeFirst && indexSecond < sizeSecond){
        if(first[indexFirst]->endPoint <= second[indexSecond]->endPoint) {
            intervals[indexFull] = first[indexFirst];
            indexFirst++;
        }
        else {
            intervals[indexFull] = second[indexSecond];
            indexSecond++;
        }
        indexFull++;
    }
    while (indexFirst < sizeFirst) {
        intervals[indexFull] = first[indexFirst];
        indexFirst++;
        indexFull++;
    }
    while (indexSecond < sizeSecond) {
        intervals[indexFull] = second[indexSecond];
        indexSecond++;
        indexFull++;
    }
    delete[] first;
    delete[] second;
}
