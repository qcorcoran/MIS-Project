//Quinn Corcoran
//circularArc

#include "circularArcGraph.h"

using namespace std;

//destructor
circularArcGraph::~circularArcGraph(){
    for(int i=0; i < n; i++){
        delete arcs[i];
    }
    delete[] arcs;
}

void circularArcGraph::readData(){
    //declare local variables
    string input = "";
    stringstream ssi;
    //line attributes
    int a = 0;
    int b = 0;
    int c = 0;
    int i = 1;

    //read first line of input should be number of nodes followed by the center cordinates and the radius
    cin>>input;
    istringstream issn(input);
    issn >> n;
    cin>>input;
    istringstream issx(input);
    issx >> xc;
    cin>>input;
    istringstream issy(input);
    issy >> yc;
    cin>>input;
    istringstream issr(input);
    issr >> radius;

    //dynamic array allocation
    arcs = new arc*[n];

    //read the rest of the file
    while (size < n){
        //set a as first number b as second number, and c as the third number
        cin>>input;
        istringstream issa(input);
        issa >> a;
        cin>>input;
        istringstream issb(input);
        issb >> b;
        cin>>input;
        istringstream issc(input);
        issc >> c;
        //create the new arc
        ssi.str("");
        ssi << i;
        arc* ark = new arc(ssi.str(), a, b, c);
        intersection(ark);
        //insert the arc into the arcs array
        arcs[size] = ark;
        size++;
        //increment the line number
        i++;
    }
}

//check intersections of a line with the circle and set the arc start and endpoint
void circularArcGraph::intersection(arc* ark){
    //get slope intercept form
    double slope = ark->ai / (ark->bi*-1);
    double yinter = ark->ci / (ark->bi*-1);

    //get A, B, and C for quadratic form
    double a = 1 + pow(slope, 2);
    double b = 2 * (slope*yinter - slope*yc - xc);
    double c = pow(yc, 2) - pow(radius, 2) + pow(xc, 2) - 2*yinter*yc + pow(yinter, 2);

    //quadratic equation
    double x1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    double x2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);

    //plug in x values for y
    double y1 = slope * x1 + yinter;
    double y2 = slope * x2 + yinter;

    //set the intersection points
    ark->setIntersect1(x1, y1);
    ark->setIntersect2(x2, y2);
    //find cross product of the points to determine if origin is to the left or the right
    ark->setCrossProduct();

    //set start and endpoint based off the sign of the cross product
    if(ark->crossProduct >= 0){
        ark->setStartTheta(ark->intersect2);
        ark->setEndTheta(ark->intersect1);
    }
    else{
        ark->setStartTheta(ark->intersect1);
        ark->setEndTheta(ark->intersect2);
    }
}

//check if two arcs are overlapping
int circularArcGraph::overlapping(arc* i, arc* j){
    if((j->startTheta < j->endTheta) && (i->endTheta > M_PI)){
        return 1;
    }
    if(j->startTheta < i->endTheta){
        return 0;
    }
    else{
        return 1;
    }
}

//this is the next function that sets the next for each arc
void circularArcGraph::initNext(){
    int i = 0;
    int j = 1;
    //run until the next is set for all arcs
    while(i < size){
        while(overlapping(arcs[i], arcs[j])){
            //advance j if it overlaps i
            j++;
            //make array circular
            if(j >= size){
                j = 0;
            }
        }
        //set next if i and j do not overlap
        arcs[i]->setNext(arcs[j]);
        i++;
        if(i == j){
            j++;
        }
        //make array circular
        if(j >= size){
            j = 0;
        }
    }
}

//run MIS algorithm for an circular-arc graph
void circularArcGraph::runMis(){
    arc* goodArc = NULL;
    arc* currentArc = arcs[0];
    while(1){
        currentArc->visited = 1;
        currentArc = currentArc->next;
        //check if we found a good arc
        if(currentArc->visited){
            goodArc = currentArc;
            break;
        }
    }
    while(1){
        misSize++;
        currentArc = currentArc->next;
        //once we have completed the directed cycle we are done
        if(currentArc == goodArc){
            break;
        }
    }
}

//recursive mergesort
void circularArcGraph::mergesort(int start, int end, string sortType){
    //base case
    if(start >= end){
        return;
    }

    //set mid point of array
    int middle = start + (end - start)/2;

    //recursive calls to mergesort
    mergesort(start, middle, sortType);
    mergesort(middle+1, end, sortType);
    merge(start, middle, end, sortType);    
}

//merge helper function for mergesort
void circularArcGraph::merge(int start, int middle, int end, string sortType){
    //initialize local variables
    int sizeFirst = middle - start + 1;
    int sizeSecond = end - middle;
    int indexFirst = 0;
    int indexSecond = 0;
    int indexFull = start;

    //create temporary arrays
    arc** first = new arc*[sizeFirst];
    arc** second = new arc*[sizeSecond];
    //fill temporary arrays
    for(int i = 0; i < sizeFirst; i++){
        first[i] = arcs[start + i];
    }
    for(int i = 0; i < sizeSecond; i++){
        second[i] = arcs[middle + 1 + i];
    }

    //sort and store into angles array
    while(indexFirst < sizeFirst && indexSecond < sizeSecond){
        if(sortType == "end"){
            if(first[indexFirst]->endTheta >= second[indexSecond]->endTheta) {
                arcs[indexFull] = first[indexFirst];
                indexFirst++;
            }
            else{
                arcs[indexFull] = second[indexSecond];
                indexSecond++;
            }
            indexFull++;
        }
        else if(sortType == "start"){
            if(first[indexFirst]->startTheta >= second[indexSecond]->startTheta) {
                arcs[indexFull] = first[indexFirst];
                indexFirst++;
            }
            else {
                arcs[indexFull] = second[indexSecond];
                indexSecond++;
            }
            indexFull++;
        }        
    }
    while (indexFirst < sizeFirst) {
        arcs[indexFull] = first[indexFirst];
        indexFirst++;
        indexFull++;
    }
    while (indexSecond < sizeSecond) {
        arcs[indexFull] = second[indexSecond];
        indexSecond++;
        indexFull++;
    }
    delete[] first;
    delete[] second;
}
