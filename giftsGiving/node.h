//Quinn Corcoran
//giftsGiving

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

using namespace std;

class node{
	private:
		int label;
		int maxNodes;
		int numChildren;
		int mark;
		node** children; //this is an array
		node* parent;
	public:
		node(int l, int n) {label = l; maxNodes = n; numChildren = 0; mark = 1; parent = NULL; children = new node*[n];}
		~node() {delete[] children;}
		void addChild(node* n) {children[numChildren] = n; numChildren++;}
		void setParent(node* n) {parent = n;}
		void kill() {mark = 0;}
	friend class tree;
};

#endif /* node_H */
