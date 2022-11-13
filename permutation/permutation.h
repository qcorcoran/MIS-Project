//Quinn Corcoran

#ifndef permutation_H
#define permutation_H

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

class permutation{
    private:
        int lineNum;
        int pValue;
        int lis;
		int lisMax;
    public:
        permutation(int n, int pv) {lineNum = n; pValue = pv; lis = 1; lisMax = 1;}
        int getPvalue() {return pValue;}

    friend class graph;
	friend class splayTree;
};

#endif /* permutation_H */
