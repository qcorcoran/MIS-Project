//Quinn Corcoran
//permutation

#include "permutationGraph.h"

using namespace std;

//destructor
permutationGraph::~permutationGraph(){
    for(int i=0; i < n; i++){
        delete permutations[i];
    }
    delete[] permutations;
}

void permutationGraph::readData(){
    //declare local variables
    string input = "";
    int intendedSize = 0;
    //permutation attributes
    int p = 0;
    int i = 1;

    //read first line of input should be number of permutations
    cin>>input;
    istringstream issn(input);
    issn >> intendedSize;
    n = intendedSize;

    //dynamic array allocation
    permutations = new permutation*[n];

    //read the rest of the file
    while (size < intendedSize){
        //set p based on the number on that line
        cin>>input;
        istringstream issp(input);
        issp >> p;
        //create the new permutation
        permutation* perm = new permutation(i, p);
        //insert the permutation into the permutations array
        permutations[size] = perm;
        size++;
        //increment the line number
        i++;
    }
}

void permutationGraph::sweepLine(){
    permutation* perm;
    //iterate over the set of permutations
    for(int i=0; i < size; i++){
        perm = permutations[i];
        node* permNode = new node(perm);
        //insert and splay the current permutation
        splay->splayInsert(permNode, splay->getRoot());
        //check if the newly splayed node has children on its left and right
        //then initialize its LIS and LISMax
        if(permNode->getLeftChild() != NULL && permNode->getRightChild() != NULL){
            perm->lis = permNode->getLeftChild()->getPermutation()->lisMax + 1;
            perm->lisMax = max(perm->lis, permNode->getRightChild()->getPermutation()->lisMax);
        }
        else if(permNode->getLeftChild() != NULL){
           perm->lis = permNode->getLeftChild()->getPermutation()->lisMax + 1;
        }
        else if(permNode->getRightChild() != NULL){
            perm->lisMax = max(perm->lis, permNode->getRightChild()->getPermutation()->lisMax);
        }
        //splay->preorderTraversal(splay->getRoot());
        //cout<<endl<<endl;
    }
    //get the final result
    misSize = splay->getRoot()->getPermutation()->lisMax;
}
