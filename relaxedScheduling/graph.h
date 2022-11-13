//Quinn Corcoran

#ifndef graph_H
#define graph_H

#include "interval.h"

using namespace std;

class graph{
	private:
		interval* intervals[1000000];
		int size;
		int misSize;
	public:
		graph() {size = 0; misSize = 0;} //Start with an empty graph
		void readData();
		void runMIS();
		int conflictCheck(int index);
		void mergesort(int start, int end);
		void merge(int start, int middle, int end);
		int getSize() {return size;}
		int getMisSize() {return misSize;}
};

#endif /* graph_H */
