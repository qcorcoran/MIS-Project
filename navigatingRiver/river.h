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
#include "point.h"
#include "bst.h"

using namespace std;

class river{
    private:
        int n;
        int a;
        int b;
        int c;
        int d;
        point** points; //this is an array
        int size;

    public:
        river() {a = 0; b = 0; c = 0; d = 0; n = 0; size = 0;}
        ~river();
        void readData();
        void mergesort(int start, int end);
		void merge(int start, int middle, int end);
        int getSize() {return size;}
        point* getPoint(int i) {return points[i];}
};

#endif /* river_H */