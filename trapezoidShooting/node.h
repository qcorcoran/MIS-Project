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
#include "trapezoid.h"

using namespace std;

class node{
	private:
		int key;
		trapezoid* trap;
		int height;
		node* parent;
		node* leftChild;
		node* rightChild;
	public:
		node(trapezoid* t) {trap = t; key = t->getTopRight(1); height = 1;  parent = NULL; leftChild = NULL; rightChild = NULL;}
		void setParent(node* n) {parent = n;}
		void setLeftChild(node* n) {leftChild = n; n->setParent(this);}
		void setRightChild(node* n) {rightChild = n; n->setParent(this);}
		int getKey() {return key;}
		trapezoid* getTrapezoid() {return trap;}
		node* getLeftChild() {return leftChild;}
		node* getRightChild() {return rightChild;}
	friend class splayTree;
};

#endif /* node_H */
