//Quinn Corcoran
//navigatingRiver

#include "river.h"

//destructor
river::~river(){
    for(int i=0; i < n; i++){
        delete points[i];
    }
    delete[] points;
}

//read from an input file
void river::readData(){
    //declare local variables
    string input = "";
    int xi = 0;
    int yi = 0;
    
    //read first line of input should be values for a, b, c, d, and n
    cin>>input;
    istringstream issa(input);
    issa >> a;
    cin>>input;
    istringstream issb(input);
    issb >> b;
    cin>>input;
    istringstream issc(input);
    issc >> c;
    cin>>input;
    istringstream issd(input);
    issd >> d;
    cin>>input;
    istringstream issn(input);
    issn >> n;

    //initialize the maximum possible diameter based on a and b
    initMaxDiameter();

    //dynamic array allocation
    points = new point*[n];

    //read the rest of the input
    while(size < n){
        //set the obstacle location
        cin>>input;
        istringstream issx(input);
        issx >> xi;
        cin>>input;
        istringstream issy(input);
        issy >> yi;
        //create the new point
        point* p = new point(xi, yi);
        //insert the point into the points array
        points[size] = p;
        size++;
    }
}

//recursive mergesort
void river::mergesort(int start, int end){
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
void river::merge(int start, int middle, int end){
    //initialize local variables
    int sizeFirst = middle - start + 1;
    int sizeSecond = end - middle;
    int indexFirst = 0;
    int indexSecond = 0;
    int indexFull = start;

    //create temporary arrays
    point** first = new point*[sizeFirst];
    point** second = new point*[sizeSecond];
    //fill temporary arrays
    for(int i = 0; i < sizeFirst; i++){
        first[i] = points[start + i];
    }
    for(int i = 0; i < sizeSecond; i++){
        second[i] = points[middle + 1 + i];
    }

    //sort and store into intervals array
    while(indexFirst < sizeFirst && indexSecond < sizeSecond){
        if(first[indexFirst]->x <= second[indexSecond]->x) {
            points[indexFull] = first[indexFirst];
            indexFirst++;
        }
        else {
            points[indexFull] = second[indexSecond];
            indexSecond++;
        }
        indexFull++;
    }
    while (indexFirst < sizeFirst) {
        points[indexFull] = first[indexFirst];
        indexFirst++;
        indexFull++;
    }
    while (indexSecond < sizeSecond) {
        points[indexFull] = second[indexSecond];
        indexSecond++;
        indexFull++;
    }
    delete[] first;
    delete[] second;
}

void river::buildGraph(int diameter){
    splayTree* splay = new splayTree();
    int i = 0;
    int j = 1;
    splayNode* inode = new splayNode(points[i]);
    splay->splayInsert(inode, splay->getRoot());
    splay->splayInsert(new splayNode(points[j]), splay->getRoot());
    
}
