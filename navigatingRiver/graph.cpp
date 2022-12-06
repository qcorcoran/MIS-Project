//Quinn Corcoran
//navigatingRiver

#include "graph.h"

using namespace std;

graph::graph(int n){
    v = n+2;
    verts = new graphNode*[v];
    numVerts = 0;
    adj = new int*[v];
    cout<<"v "<<v<<endl;
    for(int i=0; i < v; i++){
        cout<<"in "<<i<<endl;
        adj[i] = new int[v];
    }
    numEdges = new int[v];
    visited = new int[v];
    reset();
}

graph::~graph(){
    cout<<"here"<<endl;
    for(int i=0; i < numVerts; i++){
        delete verts[i];
    }
    cout<<"there "<<v<<endl;
    for(int i=0; i < v; i++){
        cout<<i<<" "<<adj[i][0]<<endl;
        delete[] adj[i];
        cout<<"HAH"<<endl;
    }
    cout<<"this"<<endl;
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
    cout <<index<<" ";
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
