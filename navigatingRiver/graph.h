//Quinn Corcoran
//navigatingRiver

#ifndef graph_H
#define graph_H

#include "graphNode.h"

using namespace std;

class graph{
	private:
        int maxVert;
        int** adj; //this is an array adjacency list
        int* numEdges; //this is an array
		int size;		
	public:
		graph(int n) {maxVert = n; size = 0; adj = new int*[maxVert]; numEdges = (int*)calloc(maxVert, sizeof(int));}
        ~graph();
        void addEdge(graphNode* u, graphNode* v);
};

#endif /* graph_H */
