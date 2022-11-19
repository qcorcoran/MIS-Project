//Quinn Corcoran
//navigatingRiver

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
    public:
        graph(int n);
        ~graph();
        void reset();
        void insert(point* p);
        void addEdge(int u, int v);
        void dfs(int index);
        void printEdges();
        //getters
        int getNumVerts() {return numVerts;}
        int getVisited(int i) {return visited[i];}
};

#endif /* graph_H */
