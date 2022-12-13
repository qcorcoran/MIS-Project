//Quinn Corcoran
//building

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
#include <stack>
#include <utility>
#include <limits>
#include "box.h"

using namespace std;

class graphNode{
	private:
        int nodeNum;
		box* build;
		int index;
	public:
		graphNode(int n, box* b) {nodeNum = n; build = b; index = b->getIndex();}
	friend class graph;
};

#endif /* graphNode_H */
