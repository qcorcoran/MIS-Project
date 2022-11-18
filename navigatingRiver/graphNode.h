//Quinn Corcoran
//navigatingRiver

#ifndef graphNode_H
#define graphNode_H

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

class graphNode{
	private:
        int nodeNum;
		int key;
        point* p;
		int index;
	public:
		graphNode(int n, point* k) {nodeNum = n; p = k; key = p->getX();}
		int getKey() {return key;}
	friend class graph;
};

#endif /* graphNode_H */
