//Quinn Corcoran
//navigatingRiver

#include "graph.h"

using namespace std;

//constructor
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

//destructor
graph::~graph(){
    for(int i=0; i < numVerts; i++){
        delete verts[i];
    }
    delete[] verts;
    delete[] adj;
    delete[] numEdges;
    delete[] visited;
}

//resets the graph edges and nodes visited
void graph::reset(){
    for(int i=0; i < v; i++){
        numEdges[i] = 0;
        visited[i] = 0;
    }
}

//insert a new graph node
void graph::insert(point* p){
    graphNode* node = new graphNode(numVerts, p);
    verts[numVerts] = node;
    numVerts++;
}

//add an edge between nodes u and v
void graph::addEdge(int u, int v){
    if(u == v){
        return;
    }
    adj[u][numEdges[u]] = v;
    numEdges[u]++;
    adj[v][numEdges[v]] = u;
    numEdges[v]++;
}

//run recursive DFS on the graph
void graph::dfs(int index){
    visited[index] = 1;
    for(int i=0; i < numEdges[index]; i++){
        if(!visited[adj[index][i]]){
            dfs(adj[index][i]);
        }
    }
}

//print all graph edges for debugging
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
