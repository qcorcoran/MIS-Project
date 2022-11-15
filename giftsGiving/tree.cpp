//Quinn Corcoran
//giftsGiving

#include "tree.h"

using namespace std;

//destructor
tree::~tree(){
    for(int i=0; i < n; i++){
        delete nodes[i];
    }
    delete[] mis;
    delete[] nodes;
}

//read from an input file and create the tree
void tree::readData(){
    //declare local variables
    string input = "";
    int intendedSize = 0;
    int parent = 0;
    int child = 0;

    //read first line of input should be number of nodes
    cin>>input;
    istringstream issn(input);
    issn >> intendedSize;
    n = intendedSize;

    //dynamic array allocation
    mis = new int[n];
    nodes = new node*[n];

    //create the root node with label 1 and itself as a parent
    node* rootNode = new node(1, n);
    rootNode->setParent(rootNode);
    root = rootNode;
    size++;
    saved = rootNode;
    nodes[0] = saved;

    //read the rest of the input
    while(size < intendedSize){
        //set parent as first number and child as second number
        cin>>input;
        istringstream issp(input);
        issp >> parent;
        cin>>input;
        istringstream issc(input);
        issc >> child;
        //takes advantage of the input file giving parents in order
        if(saved->label != parent){
            saved = nodes[parent - 1];
        }
        //insert child into tree with parent as its parent
        insert(parent, child, saved);
    }
}

//inserts child node into the tree
void tree::insert(int parentLabel, int childLabel, node* curNode){
    //ensure that the saved node is correct
    assert(curNode->label == parentLabel);
    node* child = new node(childLabel, n);
    nodes[childLabel - 1] = child;
    curNode->addChild(child);
    child->setParent(curNode);
    size++;
}

//marks a leaf node and its parent as removed
void tree::trim(node* leaf){
    leaf->kill();
    leaf->parent->kill();   
}

//adds leaf nodes to the MIS and then removes them and their parent node
void tree::computeMIS(node* curNode){
    if(curNode->mark == 1){
        mis[misSize] = curNode->label;
        misSize++;
        trim(curNode);
    }
}

//runs a postorder traversal on the tree
void tree::postorderSearch(node* curNode, string job){
    for(int i=0; i < curNode->numChildren; i++){
        postorderSearch(curNode->children[i], job);
    }
    if(visit(curNode, job)) { return; }
}

//performs a function at the chosen node
int tree::visit(node* curNode, string job){
    if(job == "MIS"){
        computeMIS(curNode);
    }
    if(job == "brute"){
        brute[bruteSize] = curNode;
        bruteSize++;
    }
    if(job == "traverse"){
        cout<<curNode->label<<endl;
    }
    return 0;
}

//recursive mergesort
void tree::mergesort(int start, int end, string job){
    //base case
    if(start >= end){
        return;
    }

    //set mid point of array
    int middle = start + (end - start)/2;

    //recursive calls to mergesort
    mergesort(start, middle, job);
    mergesort(middle+1, end, job);
    merge(start, middle, end, job);    
}

//merge helper function for mergesort
void tree::merge(int start, int middle, int end, string job){
    //initialize local variables
    int sizeFirst = middle - start + 1;
    int sizeSecond = end - middle;
    int indexFirst = 0;
    int indexSecond = 0;
    int indexFull = start;

    if(job == "mis"){
        //create temporary arrays
        int* first = new int[sizeFirst];
        int* second = new int[sizeSecond];
        //fill temporary arrays
        for(int i = 0; i < sizeFirst; i++){
            first[i] = mis[start + i];
        }
        for(int i = 0; i < sizeSecond; i++){
            second[i] = mis[middle + 1 + i];
        }

        //sort and store into intervals array
        while(indexFirst < sizeFirst && indexSecond < sizeSecond){
            if(first[indexFirst] >= second[indexSecond]) {
                mis[indexFull] = first[indexFirst];
                indexFirst++;
            }
            else {
                mis[indexFull] = second[indexSecond];
                indexSecond++;
            }
            indexFull++;
        }
        while(indexFirst < sizeFirst) {
            mis[indexFull] = first[indexFirst];
            indexFirst++;
            indexFull++;
        }
        while(indexSecond < sizeSecond) {
            mis[indexFull] = second[indexSecond];
            indexSecond++;
            indexFull++;
        }
        delete[] first;
        delete[] second;
    }
    else{
        //create temporary arrays
        node** first = new node*[sizeFirst];
        node** second = new node*[sizeSecond];
        //fill temporary arrays
        for(int i = 0; i < sizeFirst; i++){
            first[i] = brute[start + i];
        }
        for(int i = 0; i < sizeSecond; i++){
            second[i] = brute[middle + 1 + i];
        }

        //sort and store into intervals array
        while(indexFirst < sizeFirst && indexSecond < sizeSecond){
            if(first[indexFirst] >= second[indexSecond]) {
                brute[indexFull] = first[indexFirst];
                indexFirst++;
            }
            else {
                brute[indexFull] = second[indexSecond];
                indexSecond++;
            }
            indexFull++;
        }
        while(indexFirst < sizeFirst) {
            brute[indexFull] = first[indexFirst];
            indexFirst++;
            indexFull++;
        }
        while(indexSecond < sizeSecond) {
            brute[indexFull] = second[indexSecond];
            indexSecond++;
            indexFull++;
        }
        delete[] first;
        delete[] second;
    }
}

void tree::bruteForce(){
    brute = new node*[n];
    postorderSearch(root, "brute");
    root->setParent(NULL);
    node* subset[100000];
    int subsetSize = 0;
    mergesort(0, getMisSize()-1, "brute");
    findSubsets(subset, subsetSize, bruteSize-1);
    delete[] brute;
    return;
}

void tree::findSubsets(node* subset[], int subsetSize, int index){
    if(index < 0){
        if(subsetSize > misSize){
            if(validate(subset, subsetSize)){
                for(int i=0; i < subsetSize; i++){
                    mis[i] = subset[i]->label;
                }
                misSize = subsetSize;
            }
        }
        return;
    }
    subset[subsetSize] = brute[index];
    subsetSize++;
    findSubsets(subset, subsetSize, index-1);

    subsetSize--;

    findSubsets(subset, subsetSize, index-1);
}

int tree::validate(node* arry[], int arrySize){
    for(int i=0; i < arrySize; i++){
        for(int j=0; j < arrySize; j++){
            if(arry[i]->parent == arry[j]){
                return 0;
            }
        }
    }
    return 1;
}
