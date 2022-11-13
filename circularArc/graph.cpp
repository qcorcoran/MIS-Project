//Quinn Corcoran

#include "graph.h"

using namespace std;

void graph::readData(){
    //declare local variables
    string input = "";
    int intendedSize = 0;
    stringstream ssi;
    //line attributes
    int a = 0;
    int b = 0;
    int c = 0;
    int i = 1;

    //read first line of input should be number of nodes followed by the center cordinates and the radius
    cin>>input;
    istringstream issn(input);
    issn >> intendedSize;
    cin>>input;
    istringstream issx(input);
    issx >> xc;
    cin>>input;
    istringstream issy(input);
    issy >> yc;
    cin>>input;
    istringstream issr(input);
    issr >> radius;

    //read the rest of the file
    while (size < intendedSize){
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

void graph::intersection(arc* ark){
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

//recursive mergesort
void graph::mergesort(int start, int end, string sortType){
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
void graph::merge(int start, int middle, int end, string sortType){
    //initialize local variables
    int sizeFirst = middle - start + 1;
    int sizeSecond = end - middle;
    int indexFirst = 0;
    int indexSecond = 0;
    int indexFull = start;

    //create temporary arrays
    arc* first[sizeFirst];
    arc* second[sizeSecond];
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
}

//this is the next function that sets the next for each arc
void graph::initNext(){
    int i = 0;
    int j = 1;
    int set = 0;
    int looped = 0;
    double iend;
    double jend;
    double jstart;

    //run until the next is set for all arcs
    while(set < size){        
        //make array circular
        if(j >= size){
            j = 0;
            //set for when you have looped back
            looped = 1;
        }

        iend = arcs[i]->endTheta;
        jend = arcs[j]->endTheta;
        jstart = arcs[j]->startTheta;

        //check if j is stradling
        if(arcs[j]->startTheta < arcs[j]->endTheta){
            //do we need to check if these are above x-axis?
            iend -= 2*M_PI;
            jend -= 2*M_PI;
        }
        else if(looped == 1){ //if it has looped back and j does not stradle
            //do we need to check if these are above x-axis?
            jend -= 2*M_PI;
            jstart -= 2*M_PI;
        }
        if(iend <= jstart && iend >= jend){ //check if it overlaps and move j if it does
            j++;
        }
        else{ //set next if i and j do not overlap
            arcs[i]->setNext(arcs[j]);
            set++;
            i++;
            if(i == j){
                j++;
            }
        }
    }
}

//this function creates the L(G)^2 and sets it as the set of arcs in our graph object
void graph::createLineGraph(){
    stack<arc*> arcStack;
    arc* topArc;
    arc* lineGraph[1000000];
    int lineGraphSize = 0;
    string lable = "";
    double arcsEnd = 0;
    double topEnd = 0;

    //this is all based off of the sudocode from the paper
    //loop over all of our arcs
    for(int i=0; i < size; i++){
        //this loop checks if the arcs[i] is completely inside of the topArc
        while(!arcStack.empty()){
            //set topArc as the top of the stack
            topArc = arcStack.top();


            arcsEnd = arcs[i]->endTheta;
            topEnd = topArc->endTheta;

            //check if topArc is stradling
            if(topArc->startTheta < topArc->endTheta){
                //do we need to check if these are above x-axis?
                arcsEnd -= 2*M_PI;
                topEnd -= 2*M_PI;
            }
            if(arcs[i]->startTheta >= topArc->startTheta&& arcsEnd <= topEnd){ //check if the arcs[i] is completely inside of the topArc
                //create a new arc with lable that combines the two arcs
                //and has the same start and end as the arc that completely consumes the other
                //set the new arc as the optimum arc for topArc
                lable = topArc->lineNum + "," + arcs[i]->lineNum;
                topArc->next = new arc(lable, topArc);
            }
            else{ //if topArc does not completely consume arcs[i] then break
                //this break is not in the paper
                break;
            }
            //pop topArc if it had its optimum arc was set
            //if we are keeping the else break maybe this should go inside the if
            arcStack.pop();
        }

        //this checks it topArc and arcs[i] overlap and sets a likely optimum for topArc
        if(!arcStack.empty()){
            //set topArc as the top of the stack
            topArc = arcStack.top();

            arcsEnd = arcs[i]->endTheta;
            topEnd = topArc->endTheta;

            //check if topArc is stradling
            if(topArc->startTheta < topArc->endTheta){
                //do we need to check if these are above x-axis?
                arcsEnd -= 2*M_PI;
                topEnd -= 2*M_PI;
            }
            if(arcs[i]->startTheta >= topEnd){ //check if topArc and arcs[i] overlap
                //create a new arc with lable that combines the two arcs
                //and has the earliest start point and the furthest end point between the two arcs
                //set the new arc as the likely optimum arc for topArc
                lable = topArc->lineNum + "," + arcs[i]->lineNum;
                topArc->next = new arc(lable, topArc->startTheta, arcs[i]->endTheta);
            }
        }
        //push the current arc to the stack
        arcStack.push(arcs[i]);
    }
    //add all of the optimum arcs to the linegraph
    for(int i=0; i < size; i++){
        if(arcs[i]->next != NULL){
            lineGraph[lineGraphSize] = arcs[i]->next;
            lineGraphSize++;
        }
    }
    //set the arc set for the graph as the linegraph
    for(int i=0; i < lineGraphSize; i++){
        arcs[i] = lineGraph[i];
    }
    size = lineGraphSize;
}
