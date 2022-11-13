//Quinn Corcoran

#include "graph.h"

using namespace std;

void graph::readData(){
    //declare local variables
    string input = "";
    int intendedSize = 0;
    //trapezoid attributes
    int ui = 0;
    int vi = 0;
    int wi = 0;
    int zi = 1;
    int i = 1;

    //read first line of input should be number of trapezoids
    cin>>input;
    istringstream issn(input);
    issn >> intendedSize;

    //read the rest of the file
    while (size < intendedSize){
        //set u as first number, v as second number, w as the third number, and z as the fourth number
        cin>>input;
        istringstream issu(input);
        issu >> ui;
        cin>>input;
        istringstream issv(input);
        issv >> vi;
        cin>>input;
        istringstream issw(input);
        issw >> wi;
        cin>>input;
        istringstream issz(input);
        issz >> zi;
        //create the new trapezoid
        trapezoid* trap = new trapezoid(i, ui, vi, wi, zi);
        //insert the trapezoid into the trapezoids array
        trapezoids[size] = trap;
        size++;
        //insert the box representation into the boxes array
        boxes[boxesSize] = new point(trap->bottomLeft[0], trap->bottomLeft[1], trap);
        boxesSize++;
        boxes[boxesSize] = new point(trap->topRight[0], trap->topRight[1], trap);
        boxesSize++;
        //increment the line number
        i++;
    }
}

//recursive mergesort
void graph::mergesort(int start, int end){
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
void graph::merge(int start, int middle, int end){
    //initialize local variables
    int sizeFirst = middle - start + 1;
    int sizeSecond = end - middle;
    int indexFirst = 0;
    int indexSecond = 0;
    int indexFull = start;

    //create temporary arrays
    point* first[sizeFirst];
    point* second[sizeSecond];
    //fill temporary arrays
    for(int i = 0; i < sizeFirst; i++){
        first[i] = boxes[start + i];
    }
    for(int i = 0; i < sizeSecond; i++){
        second[i] = boxes[middle + 1 + i];
    }

    //sort and store into angles array
    while(indexFirst < sizeFirst && indexSecond < sizeSecond){
        if(first[indexFirst]->getX() <= second[indexSecond]->getX()) {
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
}

int graph::checkLeft(trapezoid* trap, point* p){
    if(trap->bottomLeft[0] == p->getX() && trap->bottomLeft[1] == p->getY()){
        return 1;
    }
    return 0;
}

int graph::checkRight(trapezoid* trap, point* p){
    if(trap->topRight[0] == p->getX() && trap->topRight[1] == p->getY()){
        return 1;
    }
    return 0;
}

void graph::sweepLine(){
    trapezoid* trap;
    point* p;
    node* successor;
    int sucLisMax;
    for(int i=0; i < boxesSize; i++){
        p = boxes[i];
        trap = p->getTrap();
        if(checkLeft(trap, p)){
            successor = splay->getSuccessor(p->getY());
            if(successor != NULL){
                splay->splay(successor);
                sucLisMax = splay->getRoot()->getTrapezoid()->lisMax;
                trap->lisMax = sucLisMax;
                if(successor->getLeftChild() != NULL){
                    trap->lis = successor->getLeftChild()->getTrapezoid()->lis + 1;
                }
            }
            else if(splay->getRoot() != NULL){
                successor = splay->splayMax();
                if(successor->getLeftChild() != NULL){
                    trap->lis = max(successor->getLeftChild()->getTrapezoid()->lisMax, successor->getTrapezoid()->lis) + 1;
                }
                else{
                    trap->lis = successor->getTrapezoid()->lis + 1;
                }
            }
        }
        else if(checkRight(trap, p)){
            splay->splayInsert(new node(trap), splay->getRoot());
        }
    }
    
    misSize = splay->getRoot()->getTrapezoid()->lisMax;
}
