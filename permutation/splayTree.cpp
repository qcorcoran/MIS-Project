//Quinn Corcoran
//permutation

#include "splayTree.h"

using namespace std;

//destructor
splayTree::~splayTree(){
    /*
    while(root != NULL){
        splayDelete(root);
    }
    */
}

//recursive insert
void splayTree::insert(node* n, node* current){
    //if the tree is empty set the inserted node as the root
    if(root == NULL){
        root = n;
        return;
    }
    if(n->key < current->key){
        //traverseLeft
        if(current->leftChild == NULL){
            current->setLeftChild(n);
        }
        else{
            //recursive call
            insert(n, current->leftChild);
        }
    }
    else{
        //traverseRight
        if(current->rightChild == NULL){
            current->setRightChild(n);
        }
        else{
            //recursive call
            insert(n, current->rightChild);
        }
    }
}

//calls recursive insert and then splays the inserted node to the root
void splayTree::splayInsert(node* n, node* r){
    insert(n, r);
    size++;
    splay(n);
}

//single right rotation
void splayTree::zigRotate(node* pivot){
    node* lc = pivot->leftChild;
    node* lcrc;
    if(lc != NULL){
        lcrc = lc->rightChild;
    }
    else{
        lcrc = NULL;
    }

    if(lc != NULL){
        lc->rightChild = pivot;
        pivot->leftChild = lcrc;

        lc->parent = pivot->parent;
        if(pivot->parent != NULL){
            if(pivot->parent->leftChild == pivot){
                pivot->parent->leftChild = lc;
            }
            else{
                pivot->parent->rightChild = lc;
            }
        }
        pivot->parent = lc;
        if(pivot->leftChild != NULL){
            pivot->leftChild->parent = pivot;
        }

        if(lc->parent == NULL){
            root = lc;
        }

        updateLis(pivot);
        updateLis(lc);
    }
}

//single left rotation
void splayTree::zagRotate(node* pivot){
    node* rc = pivot->rightChild;
    node* rclc;
    if(rc != NULL){
        rclc = rc->leftChild;
    }
    else{
        rclc = NULL;
    }

    if(rc != NULL){
        rc->leftChild = pivot;
        pivot->rightChild = rclc;

        rc->parent = pivot->parent;
        if(pivot->parent != NULL){
            if(pivot->parent->leftChild == pivot){
                pivot->parent->leftChild = rc;
            }
            else{
                pivot->parent->rightChild = rc;
            }
        }
        pivot->parent = rc;
        if(pivot->rightChild != NULL){
            pivot->rightChild->parent = pivot;
        }

        if(rc->parent == NULL){
            root = rc;
        }

        updateLis(pivot);
        updateLis(rc);
    }
}

//update the LIS for the node n
void splayTree::updateLis(node* n){
    n->perm->lisMax = max(n->perm->lis, n->perm->lisMax);
    if(n->rightChild != NULL && n->leftChild != NULL){
        n->perm->lisMax = max(n->perm->lis, n->rightChild->perm->lisMax);
        n->perm->lisMax = max(n->perm->lisMax, n->leftChild->perm->lisMax);
    }
    else if(n->rightChild != NULL){
        n->perm->lisMax = max(n->perm->lis, n->rightChild->perm->lisMax);
    }
    else if(n->leftChild != NULL){
        n->perm->lisMax = max(n->perm->lis, n->leftChild->perm->lisMax);
    }
}

//move node x to the root while maintaining binary search property
void splayTree::splay(node* x){
    while(x->parent != NULL){
        if(root->leftChild == x){ //zig rotation
            zigRotate(x->parent);
        }
        else if(root->rightChild == x){ //zag rotation
            zagRotate(x->parent);
        }
        else if(x->parent->leftChild == x && x->parent->parent->leftChild == x->parent){ //zig-zig rotation
            zigRotate(x->parent->parent);
            zigRotate(x->parent);
        }
        else if(x->parent->rightChild == x && x->parent->parent->rightChild == x->parent){ //zag-zag rotation
            zagRotate(x->parent->parent);
            zagRotate(x->parent);
        }
        else if(x->parent->rightChild == x && x->parent->parent->leftChild == x->parent){ //zig-zag rotation
            zigRotate(x->parent);
            zagRotate(x->parent);
        }
        else { //zag-zig rotation
            zagRotate(x->parent);
            zigRotate(x->parent);
        }
    }
    //set x as the new root
    root = x;
}

//move the max value in the tree to the root
node* splayTree::splayMax(){  
    //loop down to the rightmost leaf
    node* current = root;
    while(current->rightChild != NULL){
        current = current->rightChild;
    }
    splay(current);
    return current;
}

//split the tree into two seperate trees
//node x will be the root of the left tree
//and the right child of x will be the root of the right tree
//split is used for delete
node** splayTree::split(node* x){
    static node* leftRight[2];
    node* rightSide = NULL;
    splay(x);
    if(x->rightChild != NULL){
        rightSide = x->rightChild;
        rightSide->parent = NULL;
    }
    node* leftSide = x;
    leftSide->rightChild = NULL;
    x = NULL;
    leftRight[0] = leftSide;
    leftRight[1] = rightSide;
    return leftRight;
}

//joins two trees together into one tree
//join is used for delete
node* splayTree::join(node* leftSide, node* rightSide){
    if(leftSide == NULL){
        return rightSide;
    }
    if(rightSide == NULL){
        return leftSide;
    }
    node* x = splayMax();
    x->rightChild = rightSide;
    rightSide->parent = x;
    return x;
}

//deletes node x from the tree
void splayTree::splayDelete(node* x){
    //split the tree on x
    node** s = split(x);
    if(s[0]->leftChild != NULL){
        //set the left child of x as the root of the left tree
        //since x was previously the root this effectively deletes x
        s[0]->leftChild->parent = NULL;
        root = s[0]->leftChild;
    }
    //rejoin the two halves of the tree now without x
    join(s[0]->leftChild, s[1]);
    //decrement the size of the tree
    size--;
    //if x was the last node in the tree set root to NULL
    if(root == x){
        root = NULL;
    }
    //free up x from memory
    delete x;
}

//recursively searches the tree for the given key and returns the node
node* splayTree::search(int k, node* r){
    if(r->key == k){
        return r;
    }
    else if(r->key < k){
        //recursive call
        search(k, r->leftChild);
    }
    else{
        //recursive call
        search(k, r->rightChild);
    }
    return r;
}

//calls recursive search on key k and then moves the returned node to the root
node* splayTree::splaySearch(int k){
    node* x = search(k, root);
    if(x != NULL){
        splay(x);
    }
    return x;
}

//returns the successor node of the node with the key k
node* splayTree::getSuccessor(int k){
    node* current = root;
    if (current == NULL){
        return current;
    }
    node* successor = NULL;
    while(1){
        //go left
        if(current != NULL && k < current->key){
            //update successor
            successor = current;
            current = current->leftChild;
        }
        //go right
        else if(current != NULL && k > current->key){
            current = current->rightChild;
        }
        else{
            if(current != NULL && current->rightChild != NULL){
                current = current->rightChild;
                while(current->leftChild != NULL){
                    current = current->leftChild;
                }
                successor = current;
            }
            break;
        }
    }
    return successor;
}

//inoder traversal function for debugging
void splayTree::inorderTraversal(node* n){
    if(n == NULL){
        return;
    }
 
    //recurse on left child
    inorderTraversal(n->leftChild);
 
    //print the key
    cout<<n->key<<" ";
 
    //recurse on right child
    inorderTraversal(n->rightChild);
}

//preorder traversal function for debugging
void splayTree::preorderTraversal(node* n){
    if (n == NULL)
        return;

    //print the key
    if(n->leftChild != NULL && n->rightChild != NULL){
        cout<<n->key<<":L"<<n->leftChild->key<<":R"<<n->rightChild->key<<":LIS"<<n->perm->lis<<":LISMAX"<<n->perm->lisMax<<" ";
    }
    else if(n->leftChild != NULL){
        cout<<n->key<<":L"<<n->leftChild->key<<":LIS"<<n->perm->lis<<":LISMAX"<<n->perm->lisMax<<" ";
    }
    else if(n->rightChild != NULL){
        cout<<n->key<<":R"<<n->rightChild->key<<":LIS"<<n->perm->lis<<":LISMAX"<<n->perm->lisMax<<" ";
    }
    else{
        cout<<n->key<<":LIS"<<n->perm->lis<<":LISMAX"<<n->perm->lisMax<<" ";
    }

    //recurse on left child
    preorderTraversal(n->leftChild);

    //recurse on right child
    preorderTraversal(n->rightChild);
}
