//Quinn Corcoran
//permutation

#include "splayTree.h"

using namespace std;

void splayTree::insert(node* n, node* current){
    if(root == NULL){
        root = n;
        n->height = 1;
        return;
    }
    setHeight(current);
    if(n->key < current->key){
        //traverseLeft
        if(current->leftChild == NULL){
            //cout<<n->key<<" set left child"<<endl;
            current->setLeftChild(n);
            setHeight(current);
        }
        else{
            insert(n, current->leftChild);
        }
    }
    else{
        //traverseRight
        if(current->rightChild == NULL){
            current->setRightChild(n);
            setHeight(current);
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

void splayTree::setHeight(node* n){
    if(n->leftChild != NULL && n->rightChild != NULL){
        if(n->leftChild->height < n->rightChild->height){
            n->height = n->rightChild->height + 1;
        }
        else{
            n->height = n->leftChild->height + 1;
        }
    }
    else if(n->leftChild != NULL && n->rightChild == NULL){
        n->height = n->leftChild->height + 1;
    }
    else if(n->leftChild == NULL && n->rightChild != NULL){
        n->height = n->rightChild->height + 1;
    }
    else{
        n->height = 1;
    }
    if(n->parent != NULL){
        setHeight(n->parent);
    }
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

        if(lcrc != NULL){
            setHeight(lcrc);
        }
        setHeight(pivot);
        updateLis(pivot);
        setHeight(lc);
        updateLis(lc);
        if(lc->parent != NULL){
            setHeight(lc->parent);
        }
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

        if(rclc != NULL){
            setHeight(rclc);
        }
        setHeight(pivot);
        updateLis(pivot);
        setHeight(rc);
        updateLis(rc);
        if(rc->parent != NULL){
            setHeight(rc->parent);
        }
    }
}

void splayTree::updateLis(node* n){
    if(n->rightChild != NULL && n->leftChild != NULL){
        if(n->key == 3302901){
            cout<<n->perm->lisMax<<" "<<n->rightChild->perm->lisMax<<" "<<n->leftChild->perm->lisMax<<endl;
        }
        n->perm->lisMax = max(n->perm->lisMax, n->rightChild->perm->lisMax);
        n->perm->lisMax = max(n->perm->lisMax, n->leftChild->perm->lisMax);
        if(n->key == 3302901){
            cout<<"under "<<n->perm->lisMax<<" "<<n->rightChild->perm->lisMax<<" "<<n->leftChild->perm->lisMax<<endl;
        }
    }
    else if(n->rightChild != NULL){
        if(n->key == 3302901){
            cout<<n->perm->lisMax<<" "<<n->rightChild->perm->lisMax<<endl;
        }
        n->perm->lisMax = max(n->perm->lisMax, n->rightChild->perm->lisMax);
        if(n->key == 3302901){
            cout<<"under2 "<<n->perm->lisMax<<" "<<n->rightChild->perm->lisMax<<endl;
        }
    }
    else if(n->leftChild != NULL){
        if(n->key == 3302901){
            cout<<n->perm->lisMax<<" "<<n->leftChild->perm->lisMax<<endl;
        }
        n->perm->lisMax = max(n->perm->lisMax, n->leftChild->perm->lisMax);
        if(n->key == 3302901){
            cout<<"under3 "<<n->perm->lisMax<<" "<<n->leftChild->perm->lisMax<<endl;
        }
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
