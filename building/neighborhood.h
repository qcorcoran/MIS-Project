//Quinn Corcoran
//building

#ifndef neighborhood_H
#define neighborhood_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <string>
#include <math.h>
#include "box.h"
#include "graph.h"

using namespace std;

class neighborhood{
    private:
        int n;
        int numPaths;
        box** boxes; //this is an array
        int numBoxes;
        graph* g;

    public:
        neighborhood() {n = 0; numPaths = 0; numBoxes = 0;};
        ~neighborhood();
        void readData();
        void mergesort(int start, int end);
		void merge(int start, int middle, int end);
        int intersecting(box* b1, box* b2);
        void initGraph();
        void buildGraph();
        //getters
        int getNumBoxes() {return numBoxes;}
        graph* getGraph() {return g;}
};

#endif /* neighborhood_H */