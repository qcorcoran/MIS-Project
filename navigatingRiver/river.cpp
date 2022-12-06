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
    cout<<"n "<<n<<endl;
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
        //cout<<"("<<points[numPoints]->getX()<<", "<<points[numPoints]->getY()<<")"<<endl;
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

    //sort and store into points array
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
        //cout<<"("<<points[i]->getX()<<", "<<points[i]->getY()<<")"<<endl;
        g->insert(points[i]);
    }
}

double river::distance(point* p1, point* p2){
    int x1 = p1->getX();
    int y1 = p1->getY();
    int x2 = p2->getX();
    int y2 = p2->getY();
    double distance = (pow((pow((x2 - x1), 2) + pow((y2 - y1), 2)), 0.5));
    //cout<<"distance "<<distance<<" ("<<p1->getX()<<", "<<p1->getY()<<") ("<<p2->getX()<<", "<<p2->getY()<<")"<<endl;
    return distance;
}

int river::findBestDiameter(){
    int bestDiameter = 0;
    int tryDiameter;
    int l = 0;
    int r = maxDiameter;
    while(l <= r){
        tryDiameter = (l + r) / 2;
        cout<<"\ntry "<<tryDiameter<<endl;
        buildGraphBrute(tryDiameter);
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
    int i = 1;
    splayNode* r;
    splayNode* inode = new splayNode(points[i], i);
    splayNode* jnode;
    for(int w=0; w<numPoints; w++){
        //cout<<"("<<points[w]->getX()<<", "<<points[w]->getY()<<") ";
    }
    cout<<endl;
    //check walls on i
    if((points[i]->getX() - a) < diameter){
        g->addEdge(0, i);
    }
    //cout<<i<<" i b-p: "<<b<<" "<<points[i]->getX()<<" "<<diameter<<" "<<(b - points[i]->getX())<<endl;
    if((b - points[i]->getX()) < diameter){
        g->addEdge(n+1, i);
    }
    //cout<<"inital wall check"<<endl;
    //g->printEdges();
    splay->splayInsert(inode, splay->getRoot());
    cout<<"inserted first"<<endl;
    for(int j=i+1; j <= n; j++){
        cout<<"for j "<<j<<":"<<points[j]->getX()<<" i "<<i<<":"<<points[i]->getX()<<" -dia "<<(points[j]->getX() - points[i]->getX())<<" > "<<diameter<<endl;
        //cout<<"inorder: ";
        //splay->inorderTraversal(splay->getRoot());
        //cout<<endl;
        //advance i
        while((points[j]->getX() - points[i]->getX()) > diameter){
            cout<<"while 1"<<endl;
            //cout<<"deleteing "<<inode->getIndex()<<" "<<j<<" "<<points[j]->getX()<<" "<<points[i]->getX()<<endl;
            splay->splayDelete(inode);
            i++;
            inode = new splayNode(points[i], i);
            splay->splayInsert(inode, splay->getRoot());
        }
        jnode = new splayNode(points[j], j);
        splay->splayInsert(jnode, splay->getRoot());
        r = splay->splayMin(jnode->getRightChild());
        while(r != NULL && (r->getKey() - points[j]->getY()) <= diameter){
            cout<<"while 2"<<endl;
            cout<<"min "<<r->getIndex()<<" "<<j<<endl;
            if(distance(r->getPoint(), points[j]) < diameter){
                cout<<"add edge "<<r->getIndex()<<" "<<j<<endl;
                g->addEdge(r->getIndex(), j);
            }
            cout<<"splayingMin"<<endl;
            r = splay->splayMin(r->getRightChild());
            cout<<"splayed"<<endl;
        }
        r = splay->strictMax(jnode->getLeftChild());
        /*
        cout<<"jnode "<<jnode->getIndex()<<endl;
        if(r != NULL){
            //cout<<jnode->getRightChild()->getIndex();
            cout<<" r "<<r->getIndex()<<endl;
        }
        else{
            cout<<"r NULL"<<endl;
        }
        */
        while(r != NULL && (points[j]->getY() - r->getKey()) <= diameter){
            cout<<"while 3"<<endl;
            if(distance(r->getPoint(), points[j]) < diameter){
                //cout<<"add edge "<<r->getIndex()<<" "<<j<<" end"<<endl;
                g->addEdge(r->getIndex(), j);
            }
            r = splay->strictMax(r->getLeftChild());
            if(r != NULL){
                splay->splay(r);
            }
        }
        cout<<"checking walls"<<endl;
        //check walls
        if((points[j]->getX() - a) < diameter){
            g->addEdge(0, j);
        }
        //cout<<j<<" j b-p: "<<b<<" "<<points[i]->getX()<<" "<<diameter<<" "<<(b - points[i]->getX())<<endl;
        if((b - points[j]->getX()) < diameter){
            g->addEdge(n+1, j);
            //g->printEdges();
        }
        //cout<<"walls checked"<<endl;
        //g->printEdges();
    }
    //dfs to check for a path from the left wall node to the right wall node
    cout<<"dfs"<<endl;
    g->dfs(0);
    delete splay;
}

void river::buildGraphBrute(int diameter){
    g->reset();
    for(int i=1; i <= n; i++){
        //check walls on i
        if((points[i]->getX() - a) < diameter){
            g->addEdge(0, i);
        }
        if((b - points[i]->getX()) < diameter){
            g->addEdge(n+1, i);
        }
        for(int j=1; j <= n; j++){
            if(distance(points[i], points[j]) < diameter){
                g->addEdge(i, j);
            }
        }
    }
    //g->printEdges();
    //dfs to check for a path from the left wall node to the right wall node
    g->dfs(0);
}
