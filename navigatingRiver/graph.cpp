//Quinn Corcoran
//navigatingRiver

#include "graph.h"

using namespace std;

graph::~graph(){
    delete[] adj;
    free(numEdges);
}

void graph::addEdge(graphNode* u, graphNode* v){
    adj[u->nodeNum][numEdges[u->nodeNum]] = 1;
    numEdges[u->nodeNum]++;
    adj[v->nodeNum][numEdges[v->nodeNum]] = 1;
    numEdges[v->nodeNum]++;
}
