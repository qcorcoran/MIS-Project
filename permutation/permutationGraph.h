//Quinn Corcoran
//permutation

#ifndef permutationGraph_H
#define permutationGraph_H

#include "permutationGraph.h"
#include "splayTree.h"

using namespace std;

class permutationGraph{
	private:
		int n;
		permutation** permutations; //this is an array
        int size;
		int misSize;
		splayTree* splay;
	public:
		permutationGraph() {n=0; size = 0; misSize = 0; splay = new splayTree();} //Start with an empty graph
		~permutationGraph();
		void readData();
		void sweepLine();
		//getters
		int getMisSize() {return misSize;}
		int getSize() {return size;}
};

#endif /* permutationGraph_H */
