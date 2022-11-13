//Quinn Corcoran

#ifndef node_H
#define node_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <string>
#include <assert.h>
#include "permutation.h"

using namespace std;

class node{
	private:
		int key;
		permutation* perm;
		int height;
		node* parent;
		node* leftChild;
		node* rightChild;
	public:
		node(permutation* p) {perm = p; key = p->getPvalue(); height = 1;  parent = NULL; leftChild = NULL; rightChild = NULL;}
		void setParent(node* n) {parent = n;}
		void setLeftChild(node* n) {leftChild = n; n->setParent(this);}
		void setRightChild(node* n) {rightChild = n; n->setParent(this);}
		int getKey() {return key;}
		permutation* getPermutation() {return perm;}
		node* getLeftChild() {return leftChild;}
		node* getRightChild() {return rightChild;}
	friend class splayTree;
};

#endif /* node_H */
