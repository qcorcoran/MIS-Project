//Quinn Corcoran
//giftsGiving

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <assert.h>
#include <time.h>

using namespace std;

int main(int argc, char** argv){
    //declare local variables
    string infile = "input.txt";
    ifstream myfile;
    int maxChildren = 5;
    int nodes = 0;
    int nodesRem = 0;
    int children = 0;
    int parent = 0;
    int index = 2;

    //initialize random seed
    srand(time(NULL));

    //prompt user for input
    cout<<"Enter name of input file to create: ";
    cin>>infile;
    cout<<"Enter maximum number of children a node can have: ";
    cin>>maxChildren;
    cout<<"Enter number of nodes to create: ";
    cin>>nodes;

    //create and open input file
    ofstream iFile(infile.c_str());

    //write the number of nodes to the input file
    iFile << nodes << "\n";

    //initialize arrays to keep track of the parents and number of children
    int parents[nodes+1];
    for(int i=1; i <= nodes; i++){
        parents[i] = 0;
    }
    int numChildren[nodes+1];
    for(int i=1; i <= nodes; i++){
        numChildren[i] = 0;
    }

    //create the given number of nodes//

    //subtract out the root
    nodesRem = nodes-1;
    //set a number of children for the root
    //must be at least 1
    if(maxChildren > nodesRem){
        children = 1 + (rand() % nodesRem);
    }
    else{
       children = 1 + (rand() % maxChildren);
    }
    //set parent of root to itsself
    parents[1] = 1;
    //asserts for correctness
    assert(children > 0);
    assert(children <= nodesRem);
    assert(children <= maxChildren);
    for(int i=1; i <= nodes; i++){
        //make sure that the node has a parent so that the tree is connected
        if(parents[i] == 0){
            //set a random parent from among eligible existing nodes
            parent = 1 + (rand() % (index - 1));
            //if chosen parent cannot have anymore children choose another one
            while(numChildren[parent] >= maxChildren){
                parent = 1 + (rand() % (index - 1));
            }
            //asserts for correctness
            assert(parent > 0);
            assert(index <= nodes);
            assert((index-1) < i);
            assert(parent <= (index - 1));
            assert(numChildren[parent] < maxChildren);
            //write the parent and its child to the file
            iFile << parent << " " << i << "\n";
            //set the counters
            numChildren[parent]++;
            parents[i] = parent;
            index++;
            nodesRem--;
        }
        //add the children to the tree
        for(int j=0; j < children; j++){
            //check if children can still be added
            if(nodesRem == 0){
                break;
            }
            //write the parent and its child to the file
            iFile << i << " " << index << "\n";
            //set the counters
            parents[index] = i;
            numChildren[i]++;
            index++;
            nodesRem--;
        }
        //set the number of children for the next node
        //must be less than the remaing nodes to assign
        //and less than the maximum number of children a node can have
        if(maxChildren > nodesRem && nodesRem > 0){
            children = (rand() % nodesRem);
        }
        else if(nodesRem > 0){
            children = (rand() % maxChildren);
        }
        else{
            children = 0;
        }
        //asserts for correctness
        assert(children <= nodesRem);
        assert(children <= maxChildren);
    }
    //close the input file
    iFile.close();

    return 0;
}
