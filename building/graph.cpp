//Quinn Corcoran
//building

#include "graph.h"

using namespace std;

graph::graph(int n){
    v = n;
    numVerts = 0;
    numPaths = 0;
    dfsCount = 0;
    paths = new string[v];
    verts = new graphNode*[v];
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
    delete[] d;
    delete[] paths;
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

int graph::dfs(int i, int p){
    stack<pair<int, int>> indexStack;
    pair<int, int> stackPair(i, p);
    // stack<pair<int, int>> indexStack;
    // If x is a pair object, then x.first will be the first element, x.second will be the second element.
    indexStack.push(stackPair); // push a tuple (i, p) STL pair
    int min_d[] = ;
    while(!indexStack.empty()){
        i = indexStack.top().first; // x.first where x is the top of the stack, set p to x.second
        p = indexStack.top().second;
        indexStack.pop();
        visited[i] = 1;
        d[i] = dfsCount;
        dfsCount++;
        min_d[i] = d[i];
        for(int j=0; j < numEdges[i]; j++){
            //do not check predecessor
            if(adj[i][j] == p){
                continue;
            }
            if(!visited[adj[i][j]]){
                //recursive call
                //int min_j = dfs(adj[i][j], i);
                min_d = min(min_j, min_d);
                //if there is a bridge
                if(min_j > d[i]){
                    //store path and update path number
                    stringstream ssi;
                    string ipath = "";
                    ssi << verts[i]->index;
                    ssi >> ipath;
                    stringstream ssj;
                    string jpath = "";
                    ssj << verts[adj[i][j]]->index;
                    ssj >> jpath;
                    paths[numPaths] = ipath + " " + jpath + "\n";
                    numPaths++;
                }
                stackPair.first = adj[i][j];
                stackPair.second = p;
                indexStack.push(stackPair);
            }
            else{
                min_d = min(min_d, d[adj[i][j]]);
            }
        }
        // min_d values for all neighbors of i should be computed.
        // iterate through all neighbors j again, and check for bridges based on the min_d values.
        // Compute and store min_d for node i
        for(int j=0; j < numEdges[i]; j++){
            
        }
    }
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
