//Quinn Corcoran
//building

#ifndef graph_H
#define graph_H

#include "graphNode.h"

using namespace std;

class graph{
    private:
        int v;
        int numVerts;
        int numPaths;
        int dfsCount;
        string* paths; //this is an array
        graphNode** verts; //this is an array
        int** adj; //this is an array adjacency list
        int* numEdges; //this is an array
        int* visited; //this is an array
        int* d; //this is an array
    public:
        graph(int n);
        ~graph();
        void insert(box* b);
        void addEdge(int u, int v);
        int dfs(int i, int p);
        void printEdges();
        //getters
        int getNumPaths() {return numPaths;}
        string getPath(int i) {return paths[i];}
};

#endif /* graph_H */
