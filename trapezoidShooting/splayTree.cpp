//Quinn Corcoran
//trapezoidShooting

#include "splayTree.h"

using namespace std;

splayTree::~splayTree(){
    while(root != NULL){
        splayDelete(root);
    }
}

void splayTree::insert(node* n, node* current){
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
            insert(n, current->leftChild);
        }
    }
    else{
        //traverseRight
        if(current->rightChild == NULL){
            current->setRightChild(n);
        }
        else{
            insert(n, current->rightChild);
        }
    }
}

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

void splayTree::updateLis(node* n){
    n->trap->lisMax = max(n->trap->lis, n->trap->lisMax);
    if(n->rightChild != NULL && n->leftChild != NULL){
        n->trap->lisMax = max(n->trap->lis, n->rightChild->trap->lisMax);
        n->trap->lisMax = max(n->trap->lis, n->leftChild->trap->lisMax);
    }
    else if(n->rightChild != NULL){
        n->trap->lisMax = max(n->trap->lis, n->rightChild->trap->lisMax);
    }
    else if(n->leftChild != NULL){
        n->trap->lisMax = max(n->trap->lis, n->leftChild->trap->lisMax);
    }
}

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
    root = x;
}

node* splayTree::splayMax(){  
    //loop down to the rightmost leaf
    node* current = root;
    while(current->rightChild != NULL){
        current = current->rightChild;
    }
    splay(current);
    return current;
}

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

void splayTree::splayDelete(node* x){
    node** s = split(x);
    if(s[0]->leftChild != NULL){
        s[0]->leftChild->parent = NULL;
        root = s[0]->leftChild;
    }
    join(s[0]->leftChild, s[1]);
    size--;
    if(root == x){
        root = NULL;
    }
    delete x;
}

node* splayTree::search(int k, node* r){
    if(r->key == k){
        return r;
    }
    else if(r->key < k){
        search(k, r->leftChild);
    }
    else{
        search(k, r->rightChild);
    }
    return r;
}

node* splayTree::splaySearch(int k){
    node* x = search(k, root);
    if(x != NULL){
        splay(x);
    }
    return x;
}

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

void splayTree::preorderTraversal(node* n){
    if (n == NULL)
        return;

    //print the key
    if(n->leftChild != NULL && n->rightChild != NULL){
        cout<<n->key<<":L"<<n->leftChild->key<<":R"<<n->rightChild->key<<":LIS"<<n->trap->lis<<":LISMAX"<<n->trap->lisMax<<" ";
    }
    else if(n->leftChild != NULL){
        cout<<n->key<<":L"<<n->leftChild->key<<":LIS"<<n->trap->lis<<":LISMAX"<<n->trap->lisMax<<" ";
    }
    else if(n->rightChild != NULL){
        cout<<n->key<<":R"<<n->rightChild->key<<":LIS"<<n->trap->lis<<":LISMAX"<<n->trap->lisMax<<" ";
    }
    else{
        cout<<n->key<<":LIS"<<n->trap->lis<<":LISMAX"<<n->trap->lisMax<<" ";
    }

    //recurse on left child
    preorderTraversal(n->leftChild);

    //recurse on right child
    preorderTraversal(n->rightChild);
}
