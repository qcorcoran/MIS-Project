//Quinn Corcoran
//building

#ifndef box_H
#define box_H

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

class box{
	private:
        int index;
        int l;
		int r;
        int b;
        int t;
	public:
		box(int i, int li, int ri, int bi, int ti) {index = i; l = li; r = ri; b = bi; t = ti;}
        int getIndex() {return index;}
    friend class neighborhood;
};

#endif /* box_H */
