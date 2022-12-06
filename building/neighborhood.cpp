//Quinn Corcoran
//building

#include "neighborhood.h"

//destructor
neighborhood::~neighborhood(){
    for(int i=0; i < n; i++){
        delete boxes[i];
    }
    delete boxes;
}

//read from an input file
void neighborhood::readData(){
    //declare local variables
    string input = "";
    int li = 0;
    int ri = 0;
    int bi = 0;
    int ti = 0;
    
    //read first line of input should be n
    cin>>input;
    istringstream issn(input);
    issn >> n;

    //create the graph object
    g = new graph(n);

    //dynamically allocate boxes array
    boxes = new box*[n];

    //read the rest of the input
    while(numBoxes < n){
        //set the building location
        cin>>input;
        istringstream issl(input);
        issl >> li;
        cin>>input;
        istringstream issr(input);
        issr >> ri;
        cin>>input;
        istringstream issb(input);
        issb >> bi;
        cin>>input;
        istringstream isst(input);
        isst >> ti;

        box* build = new box(numBoxes+1, li, ri, bi, ti);

        boxes[numBoxes] = build;

        numBoxes++;
    }
    //initalize graph
    initGraph();
}

//recursive mergesort
void neighborhood::mergesort(int start, int end){
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
void neighborhood::merge(int start, int middle, int end){
    //initialize local variables
    int sizeFirst = middle - start + 1;
    int sizeSecond = end - middle;
    int indexFirst = 0;
    int indexSecond = 0;
    int indexFull = start;

    //create temporary arrays
    box** first = new box*[sizeFirst];
    box** second = new box*[sizeSecond];
    //fill temporary arrays
    for(int i = 0; i < sizeFirst; i++){
        first[i] = boxes[start + i];
    }
    for(int i = 0; i < sizeSecond; i++){
        second[i] = boxes[middle + 1 + i];
    }

    //sort and store into boxes array
    while(indexFirst < sizeFirst && indexSecond < sizeSecond){
        if(first[indexFirst]->l <= second[indexSecond]->l) {
            boxes[indexFull] = first[indexFirst];
            indexFirst++;
        }
        else {
            boxes[indexFull] = second[indexSecond];
            indexSecond++;
        }
        indexFull++;
    }
    while (indexFirst < sizeFirst) {
        boxes[indexFull] = first[indexFirst];
        indexFirst++;
        indexFull++;
    }
    while (indexSecond < sizeSecond) {
        boxes[indexFull] = second[indexSecond];
        indexSecond++;
        indexFull++;
    }
    delete[] first;
    delete[] second;
}

int neighborhood::intersecting(box* b1, box* b2){
    if((b1->r == b2->l) && (b2->b >= b1->b && b2->b <= b1->t)){
        return 1;
    }
    else if((b1->r == b2->l) && (b2->t >= b1->b && b2->t <= b1->t)){
        return 1;
    }
    else if((b1->t == b2->b) && (b2->l >= b1->l && b2->l <= b1->r)){
        return 1;
    }
    else if((b1->t == b2->b) && (b2->r >= b1->l && b2->r <= b1->r)){
        return 1;
    }
    else if((b1->b == b2->t) && (b2->l >= b1->l && b2->l <= b1->r)){
        return 1;
    }
    else if((b1->b == b2->t) && (b2->r >= b1->l && b2->r <= b1->r)){
        return 1;
    }
    return 0;
}

void neighborhood::initGraph(){
    for(int i=0; i < numBoxes; i++){
        g->insert(boxes[i]);
    }
}

void neighborhood::buildGraph(){
    for(int i=0; i < numBoxes; i++){
        for(int j=i+1; j < numBoxes; j++){
            if(intersecting(boxes[i], boxes[j]) && i != j){
                g->addEdge(boxes[i]->index-1, boxes[j]->index-1);
            }
        }
    }
    g->printEdges();
}
