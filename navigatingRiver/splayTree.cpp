//Quinn Corcoran
//navigatingRiver

#include "splayTree.h"

using namespace std;

splayTree::~splayTree(){
    while(root != NULL){
        splayDelete(root);
    }
}

void splayTree::insert(splayNode* n, splayNode* current){
    if(root == NULL){
        root = n;
        return;
    }
    if(n->key < current->key){
        //traverseLeft
        if(current->leftChild == NULL){
            //cout<<n->key<<" set left child"<<endl;
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
    root = x;
}

splayNode* splayTree::splayMax(){  
    //loop down to the rightmost leaf
    splayNode* current = root;
    while(current->rightChild != NULL){
        current = current->rightChild;
    }
    splay(current);
    return current;
}

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
    x = NULL;
    leftRight[0] = leftSide;
    leftRight[1] = rightSide;
    return leftRight;
}

splayNode* splayTree::join(splayNode* leftSide, splayNode* rightSide){
    if(leftSide == NULL){
        return rightSide;
    }
    if(rightSide == NULL){
        return leftSide;
    }
    splayNode* x = splayMax();
    x->rightChild = rightSide;
    rightSide->parent = x;
    return x;
}

void splayTree::splayDelete(splayNode* x){
    splayNode** s = split(x);
    if(s[0]->leftChild != NULL){
        s[0]->leftChild->parent = NULL;
        root = s[0]->leftChild;
    }
    join(s[0]->leftChild, s[1]);
    size--;
}

splayNode* splayTree::search(int k, splayNode* r){
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

splayNode* splayTree::splaySearch(int k){
    splayNode* x = search(k, root);
    if(x != NULL){
        splay(x);
    }
    return x;
}

splayNode* splayTree::getSuccessor(int k){
    splayNode* current = root;
    if (current == NULL){
        return current;
    }
    splayNode* successor = NULL;
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

void splayTree::inorderTraversal(splayNode* n){
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
