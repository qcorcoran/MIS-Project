//Quinn Corcoran
//circularArc

#ifndef circularArcGraph_H
#define circularArcGraph_H

#include "arc.h"

using namespace std;

class circularArcGraph{
	private:
        int n;
        int xc;
        int yc;
        int radius;
		arc** arcs; //this is an array
        int size;
		int mimSize;
	public:
		circularArcGraph() {n = 0; size = 0; mimSize = 0;} //Start with an empty graph
		void readData(); //reads in data from a text file and creates the arcs
        void intersection(arc* ark); //sets the intersection points of an arc using the quadratic formula
        void mergesort(int start, int end, string sortType);
        void merge(int start, int middle, int end, string sortType);
        void initNext();
        void createLineGraph();
        //getters
        int getSize() {return size;}
        int getMimSize() {return mimSize;}
        arc* getArc(int i) {return arcs[i];}
};

#endif /* circularArcGraph_H */
