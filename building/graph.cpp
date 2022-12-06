//Quinn Corcoran
//building

#include "graph.h"

using namespace std;

graph::graph(int n){
    v = n;
    dfsCount = 0;
    verts = new graphNode*[v];
    numVerts = 0;
    adj = new int*[v];
    for(int i=0; i < v; i++){
        adj[i] = new int[v];
    }
    numEdges = new int[v];
    visited = new int[v];
    d = new int[v];
    for(int i=0; i < v; i++){
        numEdges[i] = 0;
        visited[i] = 0;
        d[i] = 0;
    }
}

graph::~graph(){
    for(int i=0; i < numVerts; i++){
        delete verts[i];
    }
    for(int i=0; i < v; i++){
        delete[] adj[i];
    }
    delete[] verts;
    delete[] adj;
    delete[] numEdges;
    delete[] visited;
}

void graph::insert(box* b){
    graphNode* node = new graphNode(numVerts, b);
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

int graph::dfs(int i){
    visited[i] = 1;
    d[i] = dfsCount;
    dfsCount++;
    int min_d = d[i];
    cout <<i<<" "<<min_d<<endl;
    for(int j=0; j < numEdges[i]; j++){
        int min_j = d[j];
        if(!visited[adj[i][j]]){
            min_j = dfs(adj[i][j]);
            //cout <<i<<" "<<adj[i][j]<<" "<<min_j<<" "<<min_d<<endl;
            if(min_j < d[i]){
                cout<<"bridge "<<i<<" "<<adj[i][j]<<endl;
                //cout<<min_j<<" "<<d[i]<<endl;
            }
            else{
                //cout<<"NO bridge "<<i<<" "<<j<<endl;
            }
        }
        //cout<<"j "<<j<<" "<<i<<" "<<min_d<<endl;
        min_d = min(min_j, min_d);
        cout<<"j "<<adj[i][j]<<" "<<i<<" "<<min_d<<endl;
        //cout<<"j "<<j<<" "<<i<<" "<<min_d<<endl;
    }
    cout<<"returning min_d "<<min_d<<" "<<i<<endl;
    return min_d;
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
