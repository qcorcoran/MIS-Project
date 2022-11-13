//Quinn Corcoran

#ifndef graph_H
#define graph_H

#include "permutation.h"
#include "splayTree.h"

using namespace std;

class graph{
	private:
		permutation* permutations[1000000];
        int size;
		int misSize;
		splayTree* splay;
	public:
		graph() {size = 0; misSize = 0; splay = new splayTree();} //Start with an empty graph
		void readData();
		void mergesort(int start, int end);
		void merge(int start, int middle, int end);
		void sweepLine();
		//getters
		int getMisSize() {return misSize;}
		int getSize() {return size;}
};

#endif /* graph_H */
