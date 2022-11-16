//Quinn Corcoran
//navigatingRiver

#ifndef splayNode_H
#define splayNode_H

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

class splayNode{
	private:
		int key;
		point* p;
		splayNode* parent;
		splayNode* leftChild;
		splayNode* rightChild;
	public:
		splayNode(point* pi) {p = pi; key = p->getY(); parent = NULL; leftChild = NULL; rightChild = NULL;}
		void setParent(splayNode* n) {parent = n;}
		void setLeftChild(splayNode* n) {leftChild = n; n->setParent(this);}
		void setRightChild(splayNode* n) {rightChild = n; n->setParent(this);}
		int getKey() {return key;}
		point* getPoint() {return p;}
		splayNode* getLeftChild() {return leftChild;}
		splayNode* getRightChild() {return rightChild;}
	friend class splayTree;
};

#endif /* splayNode_H */
