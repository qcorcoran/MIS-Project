//Quinn Corcoran
//splay

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
    //cout << "inside splay " << x << " " << root << endl;
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

splayNode** splayTree::split(splayNode* x){
    static splayNode* leftRight[2];
    splayNode* rightSide = NULL;
    splay(x);
    //cout << "here split " << x << endl;
    if(x->rightChild != NULL){
        rightSide = x->rightChild;
        rightSide->parent = NULL;
        //x->rightChild = NULL;
    }
    splayNode* leftSide = x;
    leftSide->rightChild = NULL;
    //x = NULL;
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
    splayNode* x = splayMax(leftSide);
    x->rightChild = rightSide;
    rightSide->parent = x;
    return x;
}

void splayTree::splayDelete(splayNode* x){
    if(size > 1){
        splayNode** s = split(x);
        //cout << "here delete-> split " << x << endl;
        if(s[0]->leftChild != NULL){
            s[0]->leftChild->parent = NULL;
            root = s[0]->leftChild;
        }
        root = join(s[0]->leftChild, s[1]);
    }
    else{
       root = NULL;
    }
    //size--;
    //cout<<"size-- "<<size<<" "<<x<<endl;
    delete x;
    //cout<<"delete x "<<x<<endl;
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

void splayTree::preorderTraversal(splayNode* n){
    if (n == NULL)
        return;

    //print the key
    if(n->leftChild != NULL && n->rightChild != NULL){
        cout<<n->p->toString()<<n->index<<":L"<<n->leftChild->p->toString()<<n->leftChild->index<<":R"<<n->rightChild->p->toString()<<n->rightChild->index<<" | ";
    }
    else if(n->leftChild != NULL){
        cout<<n->p->toString()<<n->index<<":L"<<n->leftChild->p->toString()<<n->leftChild->index<<" | ";
    }
    else if(n->rightChild != NULL){
        cout<<n->p->toString()<<n->index<<":R"<<n->rightChild->p->toString()<<n->rightChild->index<<" | ";
    }
    else{
        cout<<n->p->toString()<<n->index<<" | ";
    }

    //recurse on left child
    preorderTraversal(n->leftChild);

    //recurse on right child
    preorderTraversal(n->rightChild);
}