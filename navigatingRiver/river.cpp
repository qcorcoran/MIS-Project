//Quinn Corcoran
//navigatingRiver

#include "river.h"

//destructor
river::~river(){
    for(int i=0; i < numPoints; i++){
        delete points[i];
    }
    delete[] points;
    delete g;
}

//read from an input file
void river::readData(){
    //declare local variables
    string input = "";
    int xi = 0;
    int yi = 0;
    
    //read first line of input should be values for a, b, c, d, and n
    cin>>input;
    istringstream issa(input);
    issa >> a;
    cin>>input;
    istringstream issb(input);
    issb >> b;
    cin>>input;
    istringstream issc(input);
    issc >> c;
    cin>>input;
    istringstream issd(input);
    issd >> d;
    cin>>input;
    istringstream issn(input);
    issn >> n;

    //create the graph object
    g = new graph(n);

    //dynamically allocate points array
    points = new point*[n+2];

    //initialize the maximum possible diameter based on a and b
    initMaxDiameter();

    //insert left wall
    point* p = new point(a, c);
    points[numPoints] = p;
    numPoints++;

    //read the rest of the input
    while(numPoints <= n){
        //set the obstacle location
        cin>>input;
        istringstream issx(input);
        issx >> xi;
        cin>>input;
        istringstream issy(input);
        issy >> yi;
        //create the new point
        p = new point(xi, yi);
        //insert the point into the points array
        points[numPoints] = p;
        numPoints++;
    }
    //insert right wall
    p = new point(b, d);
    points[numPoints] = p;
    numPoints++;
    cout<<"numPoints "<<numPoints<<endl;
}

//recursive mergesort
void river::mergesort(int start, int end){
    //base case
    if(start >= end){
        return;
    }

    //set mid point of array
    int middle = start + (end - start)/2;

    //recursive calls to mergesort
    mergesort(start, middle);
    mergesort(middle+1, end);
    merge(start, middle, end);    
}

//merge helper function for mergesort
void river::merge(int start, int middle, int end){
    //initialize local variables
    int sizeFirst = middle - start + 1;
    int sizeSecond = end - middle;
    int indexFirst = 0;
    int indexSecond = 0;
    int indexFull = start;

    //create temporary arrays
    point** first = new point*[sizeFirst];
    point** second = new point*[sizeSecond];
    //fill temporary arrays
    for(int i = 0; i < sizeFirst; i++){
        first[i] = points[start + i];
    }
    for(int i = 0; i < sizeSecond; i++){
        second[i] = points[middle + 1 + i];
    }

    //sort and store into intervals array
    while(indexFirst < sizeFirst && indexSecond < sizeSecond){
        if(first[indexFirst]->x <= second[indexSecond]->x) {
            points[indexFull] = first[indexFirst];
            indexFirst++;
        }
        else {
            points[indexFull] = second[indexSecond];
            indexSecond++;
        }
        indexFull++;
    }
    while (indexFirst < sizeFirst) {
        points[indexFull] = first[indexFirst];
        indexFirst++;
        indexFull++;
    }
    while (indexSecond < sizeSecond) {
        points[indexFull] = second[indexSecond];
        indexSecond++;
        indexFull++;
    }
    delete[] first;
    delete[] second;
}

void river::initGraph(){
    cout<<"numpoints "<<numPoints<<endl;
    for(int i=0; i < numPoints; i++){
        g->insert(points[i]);
    }
}

double river::distance(point* p1, point* p2){
    int x1 = p1->getX();
    int y1 = p1->getY();
    int x2 = p2->getX();
    int y2 = p2->getY();
    double distance = (pow((pow((x2 - x1), 2) + pow((y2 - y1), 2)), 0.5));
    cout<<"distance "<<distance<<" "<<p1->getX()<<" "<<p2->getX()<<endl;
    return distance;
}

int river::findBestDiameter(){
    int bestDiameter = 0;
    int tryDiameter;
    int l = 0;
    int r = maxDiameter;
    while(l <= r){
        tryDiameter = (l + r) / 2;
        cout<<"try "<<tryDiameter<<endl;
        buildGraph(tryDiameter);
        //g->printEdges();
        if(g->getVisited(g->getNumVerts()-1)){
            r = tryDiameter - 1;
        }
        else{
            bestDiameter = tryDiameter;
            l = tryDiameter + 1;
        }
    }
    return bestDiameter;
}

void river::buildGraph(int diameter){
    g->reset();
    splayTree* splay = new splayTree();
    //sudo code goes here
    int i = 1;
    splayNode* r;
    splayNode* inode = new splayNode(points[i], i);
    splayNode* jnode;
    splay->splayInsert(inode, splay->getRoot());
    for(int j=i+1; j <= n; j++){
        //advance i
        while((points[j]->getX() - points[i]->getX()) > diameter){
            splay->splayDelete(inode);
            i++;
            inode = new splayNode(points[i], i);
            splay->splayInsert(inode, splay->getRoot());
        }
        jnode = new splayNode(points[j], j);
        r = splay->getSuccessor(jnode);
        while(r != NULL && (r->getKey() - points[j]->getY()) <= diameter){
            if(distance(r->getPoint(), points[j]) > diameter){
                g->addEdge(r->getIndex(), j);
            }
            r = splay->getSuccessor(r);
        }
        r = splay->getPredecessor(jnode);
        while(r != NULL && (points[j]->getY() - r->getKey()) <= diameter){
            if(distance(r->getPoint(), points[j]) > diameter){
                g->addEdge(r->getIndex(), j);
            }
            r = splay->getPredecessor(r);
        }
        //check walls
        if((points[j]->getX() - a) < diameter){
            g->addEdge(0, j);
        }
        if((b - points[j]->getX()) < diameter){
            g->addEdge(n+1, j);
        }
        splay->splayInsert(jnode, splay->getRoot());
    }
    //dfs to check for a path from the left wall node to the right wall node
    g->dfs(0);
    delete splay;
}
