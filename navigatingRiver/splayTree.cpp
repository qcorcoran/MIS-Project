//Quinn Corcoran
//navigatingRiver

#include "splayTree.h"

using namespace std;

//destructor
splayTree::~splayTree(){
    while(root != NULL){
        splayDelete(root);
    }
}

//recursive insert
void splayTree::insert(splayNode* n, splayNode* current){
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
void splayTree::splayInsert(splayNode* n, splayNode* r){
    insert(n, r);
    size++;
    splay(n);
}

//single right rotation
void splayTree::zigRotate(splayNode* pivot){
    splayNode* lc = pivot->leftChild;
    splayNode* lcrc;
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
    }
}

//single left rotation
void splayTree::zagRotate(splayNode* pivot){
    splayNode* rc = pivot->rightChild;
    splayNode* rclc;
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
    }
}

//move node x to the root while maintaining binary search property
void splayTree::splay(splayNode* x){
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
splayNode* splayTree::splayMax(splayNode* r){
    if(r == NULL){
        return r;
    }
    //loop down to the rightmost leaf
    splayNode* current = r;
    while(current->rightChild != NULL){
        current = current->rightChild;
    }
    splay(current);
    return current;
}

//move the min value in the tree to the root
splayNode* splayTree::splayMin(splayNode* r){
    if(r == NULL){
        return r;
    }
    //loop down to the leftmost leaf
    splayNode* current = r;
    while(current->leftChild != NULL){
        current = current->leftChild;
    }
    splay(current);
    
    return current;
}

//split the tree into two seperate trees
//node x will be the root of the left tree
//and the right child of x will be the root of the right tree
//split is used for delete
splayNode** splayTree::split(splayNode* x){
    static splayNode* leftRight[2];
    splayNode* rightSide = NULL;
    splay(x);
    if(x->rightChild != NULL){
        rightSide = x->rightChild;
        rightSide->parent = NULL;
    }
    splayNode* leftSide = x;
    leftSide->rightChild = NULL;
    leftRight[0] = leftSide;
    leftRight[1] = rightSide;
    return leftRight;
}

//joins two trees together into one tree
//join is used for delete
splayNode* splayTree::join(splayNode* leftSide, splayNode* rightSide){
    if(leftSide == NULL){
        return rightSide;
    }
    if(rightSide == NULL){
        return leftSide;
    }
    splayNode* x = splayMax(leftSide);
    x->rightChild = rightSide;
    rightSide->parent = x;
    return x;
}

//deletes node x from the tree
void splayTree::splayDelete(splayNode* x){
    //split the tree on x
    if(size > 1){
        splayNode** s = split(x);
        if(s[0]->leftChild != NULL){
            //set the left child of x as the root of the left tree
            //since x was previously the root this effectively deletes x
            s[0]->leftChild->parent = NULL;
            root = s[0]->leftChild;
        }
        //rejoin the two halves of the tree now without x
        root = join(s[0]->leftChild, s[1]);
    }
    else{
        //if x was the last node in the tree set root to NULL
        root = NULL;
    }
    //decrement the size of the tree
    size--;
    //free up x from memory
    delete x;
}

//recursively searches the tree for the given key and returns the node
splayNode* splayTree::search(int k, splayNode* r){
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
splayNode* splayTree::splaySearch(int k){
    splayNode* x = search(k, root);
    if(x != NULL){
        splay(x);
    }
    return x;
}

//inoder traversal function for debugging
void splayTree::inorderTraversal(splayNode* n){
    if(n == NULL){
        return;
    }
 
    //recurse on left child
    inorderTraversal(n->leftChild);
 
    //print the index
    cout<<n->getIndex();
    if(n->parent != NULL){
        cout<<" P:"<<n->parent->getIndex();
    }
    if(n->getLeftChild() != NULL){
        cout<<" L:"<<n->getLeftChild()->getIndex();
    }
    if(n->getRightChild() != NULL){
        cout<<" R:"<<n->getRightChild()->getIndex();
    }
    cout<<" | ";
 
    //recurse on right child
    inorderTraversal(n->rightChild);
}

//preorder traversal function for debugging
void splayTree::preorderTraversal(splayNode* n){
    if (n == NULL)
        return;

    //print the key
    if(n->leftChild != NULL && n->rightChild != NULL){
        cout<<"("<<n->p->getX()<<", "<<n->key<<")"<<":L"<<n->leftChild->key<<":R"<<n->rightChild->key<<" ";
    }
    else if(n->leftChild != NULL){
        cout<<"("<<n->p->getX()<<", "<<n->key<<")"<<":L"<<n->leftChild->key<<" ";
    }
    else if(n->rightChild != NULL){
        cout<<"("<<n->p->getX()<<", "<<n->key<<")"<<":R"<<n->rightChild->key<<" ";
    }
    else{
        cout<<"("<<n->p->getX()<<", "<<n->key<<")"<<" ";
    }

    //recurse on left child
    preorderTraversal(n->leftChild);

    //recurse on right child
    preorderTraversal(n->rightChild);
}
