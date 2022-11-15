//Quinn Corcoran
//navigatingRiver

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
#include "point.h"

using namespace std;

class node{
	private:
		int key;
		point* p;
		int height;
		node* parent;
		node* leftChild;
		node* rightChild;
	public:
		node(point* pi) {p = pi; key = p->getY(); height = 1;  parent = NULL; leftChild = NULL; rightChild = NULL;}
		void setParent(node* n) {parent = n;}
		void setLeftChild(node* n) {leftChild = n; n->setParent(this);}
		void setRightChild(node* n) {rightChild = n; n->setParent(this);}
		int getKey() {return key;}
		point* getPoint() {return p;}
		node* getLeftChild() {return leftChild;}
		node* getRightChild() {return rightChild;}
	friend class bst;
};

#endif /* node_H */
