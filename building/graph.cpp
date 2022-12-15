//Quinn Corcoran
//building

#include "graph.h"

using namespace std;

//constructor
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

//destructor
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

//insert a new graph node
void graph::insert(box* b){
    graphNode* node = new graphNode(numVerts, b);
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

//non-recursive DFS modified to check for bridges
void graph::dfs(int i, int p){
    int min_d[v];
    stack<pair<int, int> > stack1;
    stack<pair<int, int> > stack2;
    pair<int, int> stackPair(i, p);
    stack1.push(stackPair);
    while(!stack1.empty()){
        i = stack1.top().first;
        p = stack1.top().second;
        stack1.pop();
        stackPair.first = i;
        stackPair.second = p;
        stack2.push(stackPair);
        visited[i] = 1;
        d[i] = dfsCount;
        dfsCount++;
        min_d[i] = d[i];
        for(int j=0; j < numEdges[i]; j++){
            //do not check predecessor
            if(adj[i][j] == p){
                continue;
            }
            if(visited[adj[i][j]]){
                min_d[i] = min(min_d[i], d[adj[i][j]]);
            }
            else{
                stackPair.first = adj[i][j];
                stackPair.second = i;
                stack1.push(stackPair);
            }
        }
    }
    //min_d values for all neighbors of i should be computed
    //iterate through all neighbors j again, and check for bridges based on the min_d values
    //compute and store min_d for node i
    while(!stack2.empty()){
        i = stack2.top().first;
        p = stack2.top().second;
        stack2.pop();
        for(int j=0; j < numEdges[i]; j++){
            //do not check predecessor
            if(adj[i][j] == p){
                continue;
            }
            min_d[i] = min(min_d[i], min_d[adj[i][j]]);
            if(min_d[adj[i][j]] > d[i]){
                //store path and update path number
                stringstream ssi;
                string ipath = "";
                ssi << i+1;
                ssi >> ipath;
                stringstream ssj;
                string jpath = "";
                ssj << adj[i][j]+1;
                ssj >> jpath;
                paths[numPaths] = ipath + " " + jpath + "\n";
                numPaths++;
            }
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
