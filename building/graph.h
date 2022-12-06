//Quinn Corcoran
//building

#ifndef graph_H
#define graph_H

#include "graphNode.h"

using namespace std;

class graph{
    private:
        int v;
        graphNode** verts; //this is an array
        int numVerts;
        int** adj; //this is an array adjacency list
        int* numEdges; //this is an array
        int* visited; //this is an array
        int* d; //this is an array
        int dfsCount;
    public:
        graph(int n);
        ~graph();
        void insert(box* b);
        void addEdge(int u, int v);
        int dfs(int index);
        void printEdges();
        //getters
        int getNumVerts() {return numVerts;}
        int getVisited(int i) {return visited[i];}
};

#endif /* graph_H */
