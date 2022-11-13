//Quinn Corcoran

#ifndef arc_H
#define arc_H

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
#include <stack>

using namespace std;

class arc{
	private:
        string lineNum;
		double ai;
		double bi;
		double ci;
		double intersect1[2]; //x and y cordinates of one of the intersections of the line with the circle
		double intersect2[2]; //x and y cordinates of the other intersection of the line with the circle
		double crossProduct; //cross product of the intersection points
		double startTheta; //angle of the start point
		double endTheta; //angle of the end point
		arc* next;
	public:
		arc(string num, int a, int b, int c) {lineNum = num; ai = a; bi = b; ci = c; next = NULL;}
		arc(string num, double st, double et) {lineNum = num; startTheta = st; endTheta = et; next = NULL;} //used when setting optimum arcs in linegraph function
		arc(string num, arc* a) {lineNum = num; startTheta = a->startTheta; endTheta = a->endTheta; next = NULL;} //used when setting optimum arcs in linegraph function
		void setIntersect1(double x, double y) {intersect1[0] = x; intersect1[1] = y;} 
		void setIntersect2(double x, double y) {intersect2[0] = x; intersect2[1] = y;}
		void setCrossProduct() {crossProduct = (intersect1[0] * intersect2[1]) - (intersect1[1] * intersect2[0]);}
		void setStartTheta(double intersection[2]) {startTheta = acos(intersection[0] / (sqrt(pow(intersection[0], 2) + pow(intersection[1], 2)))); if(intersection[1] < 0){startTheta = 2*M_PI - startTheta;}}
		void setEndTheta(double intersection[2]) {endTheta = acos(intersection[0] / (sqrt(pow(intersection[0], 2) + pow(intersection[1], 2)))); if(intersection[1] < 0){endTheta = 2*M_PI - endTheta;}}
		void setNext(arc* n) {next = n;}
		//getters mostly only used in main for debug prints
		string getLineNum() {return lineNum;}
		double getIntersect1(int i) {return intersect1[i];}
		double getIntersect2(int i) {return intersect2[i];}
		double getCrossProduct() {return crossProduct;}
		double getStartTheta() {return startTheta;}
		double getEndTheta() {return endTheta;}
		arc* getNext() {return next;}
	friend class graph;
};

#endif /* arc_H */
