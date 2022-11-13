//Quinn Corcoran

#ifndef trapezoid_H
#define trapezoid_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <string>
#include <cmath>
#include <math.h>

using namespace std;

class trapezoid{
	private:
        int lineNum;
		int u;
		int v;
		int w;
		int z;
		int bottomLeft[2];
		int topRight[2];
		int lis;
		int lisMax;
	public:
		trapezoid(int n, int ui, int vi, int wi, int zi) {lineNum = n; u = ui; v = vi; w = wi; z = zi; bottomLeft[0] = u; topRight[0] = v; bottomLeft[1] = w; topRight[1] = z; lis = 1; lisMax = 1;}
		int getTopRight(int index) {return topRight[index];};
	friend class graph;
	friend class splayTree;
};

#endif /* trapezoid_H */
