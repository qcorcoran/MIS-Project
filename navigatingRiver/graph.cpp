//Quinn Corcoran
//navigatingRiver

#include "graph.h"

using namespace std;

graph::graph(int n){
    v = n+2;
    verts = new graphNode*[v];
    numVerts = 0;
    adj = new int*[v];
    for(int i=0; i < v; i++){
        adj[i] = new int[v];
    }
    numEdges = (int*)calloc(v, sizeof(int));
    visited = (int*)calloc(v, sizeof(int));
}

graph::~graph(){
    for(int i=0; i < numVerts; i++){
        delete verts[i];
    }
    delete[] verts;
    delete[] adj;
    free(numEdges);
    free(visited);
}

void graph::reset(){
    for(int i=0; i < numVerts; i++){
        numEdges[i] = 0;
        visited[i] = 0;
    }
}

void graph::insert(point* p){
    graphNode* node = new graphNode(numVerts, p);
    verts[numVerts] = node;
    numVerts++;
}

void graph::addEdge(int u, int v){
    adj[u][numEdges[u]] = 1;
    numEdges[u]++;
    adj[v][numEdges[v]] = 1;
    numEdges[v]++;
}

void graph::dfs(int index){
    visited[index] = 1;
    //cout <<index<<" ";
    for(int i=0; i < numEdges[index]; i++){
        if(adj[index][i]){
            if(!visited[i]){
                dfs(i);
            }
        }
    }
}
