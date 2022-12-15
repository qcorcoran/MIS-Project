//Quinn Corcoran
//relaxedScheduling

#ifndef intervalGraph_H
#define intervalGraph_H

#include "interval.h"

using namespace std;

class intervalGraph{
	private:
		int n;
		interval** intervals; //this is an array
		int size;
		int misSize;
	public:
		intervalGraph() {n = 0; size = 0; misSize = 0;} //Start with an empty graph
		~intervalGraph();
		void readData();
		void runMIS();
		int conflictCheck(int index);
		void mergesort(int start, int end);
		void merge(int start, int middle, int end);
		//getters
		int getSize() {return size;}
		int getMisSize() {return misSize;}
};

#endif /* intervalGraph_H */
