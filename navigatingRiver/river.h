//Quinn Corcoran
//navigatingRiver

#ifndef river_H
#define river_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <string>
#include <math.h>
#include "point.h"
#include "splayTree.h"
#include "graph.h"

using namespace std;

class river{
    private:
        int n;
        int a;
        int b;
        int c;
        int d;
        int maxDiameter;
        point** points; //this is an array
        int numPoints;
        graph* g;

    public:
        river() {a = 0; b = 0; c = 0; d = 0; n = 0; numPoints = 0;}
        ~river();
        void readData();
        void initMaxDiameter() {maxDiameter = b - a;}
        void initGraph();
        double distance(point* p1, point* p2);
        int findBestDiameter(string alg);
        void buildGraph(int diameter);
        void buildGraphBrute(int diameter);
        void mergesort(int start, int end);
		void merge(int start, int middle, int end);
        //getters
        int getNumPoints() {return numPoints;}
        point* getPoint(int i) {return points[i];}
};

#endif /* river_H */