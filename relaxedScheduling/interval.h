//Quinn Corcoran

#ifndef interval_H
#define interval_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <string>

using namespace std;

class interval{
	private:
		int startPoint;
		int endPoint;
	public:
		interval(int s, int e) {startPoint = s; endPoint = e;}
	friend class graph;
};

#endif /* interval_H */
