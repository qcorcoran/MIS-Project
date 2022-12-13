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
    numEdges = new int[v];
    visited = new int[v];
    reset();
}

graph::~graph(){
    for(int i=0; i < numVerts; i++){
        delete verts[i];
    }
    delete[] verts;
    delete[] adj;
    delete[] numEdges;
    delete[] visited;
}

void graph::reset(){
    for(int i=0; i < v; i++){
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
    if(u == v){
        return;
    }
    adj[u][numEdges[u]] = v;
    numEdges[u]++;
    adj[v][numEdges[v]] = u;
    numEdges[v]++;
}

void graph::dfs(int index){
    visited[index] = 1;
    //cout <<index<<" ";
    for(int i=0; i < numEdges[index]; i++){
        if(!visited[adj[index][i]]){
            dfs(adj[index][i]);
        }
    }
}

void graph::printEdges(){
    cout<<"printing "<<numEdges[0]<<" "<<numVerts<<endl;
    for(int i=0; i < numVerts; i++){
        cout<<i<<": ";
        for(int j=0; j < numEdges[i]; j++){
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }
}
