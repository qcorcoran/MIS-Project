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

using namespace std;

class node{
	private:
		int lable;
		int numChildren;
		int mark;
		node* children[1000000];
		node* parent;
	public:
		node(int l) {lable = l; numChildren = 0; mark = 1; parent = NULL;}
		void addChild(node* n) {children[numChildren] = n; numChildren++;}
		void setParent(node* n) {parent = n;}
		void kill() {mark = 0;}
	friend class tree;
};

#endif /* node_H */
