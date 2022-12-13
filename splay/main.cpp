//Quinn Corcoran
//splay

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "point.h"
#include "splayTree.h"
#include "splayNode.h"

using namespace std;

int main(int argc, char** argv){
    splayTree* s = new splayTree();
    
    int n = 6;
    splayNode* nodeArray[n];
    point* pointArray[n];
    point* p1 = new point(0, 7);
    pointArray[0] = p1;
    point* p2 = new point(4, 5);
    pointArray[1] = p2;
    point* p3 = new point(6, 9);
    pointArray[2] = p3;
    point* p4 = new point(3, 9);
    pointArray[3] = p4;
    point* p5 = new point(1, 2);
    pointArray[4] = p5;
    point* p6 = new point(2, 3);
    pointArray[5] = p6;

    for(int i=0; i < n; i++){
        splayNode* sp = new splayNode(pointArray[i], i+1);
        nodeArray[i] = sp;
    }

    cout<<"begin inserting"<<endl;
    for(int i=0; i < n; i++){
        int ins = i;
        if(ins >= n){
            break;
        }
        cout<<"inserting: "<<nodeArray[ins]->getPoint()->toString()<<endl;
        s->splayInsert(nodeArray[ins], s->getRoot());
        s->preorderTraversal(s->getRoot());
        cout<<"\npre "<<i<<endl;
    }
    s->inorderTraversal(s->getRoot());
    cout<<endl;

    cout<<"-----------------------------------------------------------------------------"<<endl;

    cout<<"begin deleting"<<endl;
    for(int i=0; i < n; i++){
        int del = i;
        if(del >= n){
            break;
        }
        cout<<"deleting: "<<nodeArray[del]->getPoint()->toString()<<endl;
        s->splayDelete(nodeArray[del]);
        s->preorderTraversal(s->getRoot());
        cout<<"\npre "<<i<<endl;
        if(s->getRoot() != NULL){
            cout<<"MIN: "<<s->splayMin(s->getRoot())->getPoint()->toString()<<endl;
            cout<<"MAX: "<<s->splayMax(s->getRoot())->getPoint()->toString()<<endl;
        }
    }

    //deallocate the splay tree
    delete s;

    cout<<"DONE"<<endl;

    return 0;
}
