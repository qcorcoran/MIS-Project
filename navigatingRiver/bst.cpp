//Quinn Corcoran
//navigatingRiver

#include "bst.h"

using namespace std;

void bst::insert(node* n, node* current){
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

    //balance tree
    if(balanceFactor(n) == 2 && balanceFactor(n->leftChild) == 1){
        rotateLL(n);
    }
    else if(balanceFactor(n) == -2 && balanceFactor(n->rightChild) == -1){
        rotateRR(n);
    }
    else if(balanceFactor(n) == -2 && balanceFactor(n->rightChild) == 1){
        rotateRL(n);
    }
    else if(balanceFactor(n) == 2 && balanceFactor(n->leftChild) == -1){
        rotateLR(n);
    }
}

void bst::setHeight(node* n){
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

int bst::balanceFactor(node* n){
    if(n->leftChild != NULL && n->rightChild != NULL){
        return n->leftChild->height - n->rightChild->height; 
    }
    else if(n->leftChild != NULL && n->rightChild == NULL){
        return n->leftChild->height; 
    }
    else if(n->leftChild == NULL && n->rightChild != NULL){
        return -n->rightChild->height;
    }
    else{
        return 0;
    }
}

void bst::rotateLL(node* pivot){
    zagRotate(pivot);
    zagRotate(pivot);
}

void bst::rotateRR(node* pivot){
    zigRotate(pivot);
    zigRotate(pivot);
}

void bst::rotateLR(node* pivot){
    zagRotate(pivot);
    zigRotate(pivot);
}

void bst::rotateRL(node* pivot){
    zigRotate(pivot);
    zagRotate(pivot);
}

//single right rotation
void bst::zigRotate(node* pivot){
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
        setHeight(lc);
        if(lc->parent != NULL){
            setHeight(lc->parent);
        }
    }
}

//single left rotation
void bst::zagRotate(node* pivot){
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
        setHeight(rc);
        if(rc->parent != NULL){
            setHeight(rc->parent);
        }
    }
}

node* bst::search(int k, node* r){
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

node* bst::getSuccessor(int k){
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

void bst::inorderTraversal(node* n){
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

void bst::preorderTraversal(node* n){
    if (n == NULL)
        return;

    //print the key
    if(n->leftChild != NULL && n->rightChild != NULL){
        cout<<n->key<<":L"<<n->leftChild->key<<":R"<<n->rightChild->key<<":H"<<n->height<<" ";
    }
    else if(n->leftChild != NULL){
        cout<<n->key<<":L"<<n->leftChild->key<<":H"<<n->height<<" ";
    }
    else if(n->rightChild != NULL){
        cout<<n->key<<":R"<<n->rightChild->key<<":H"<<n->height<<" ";
    }
    else{
        cout<<n->key<<":H"<<n->height<<" ";
    }

    //recurse on left child
    preorderTraversal(n->leftChild);

    //recurse on right child
    preorderTraversal(n->rightChild);
}
