//Quinn Corcoran

#ifndef graph_H
#define graph_H

#include "trapezoid.h"
#include "point.h"
#include "splayTree.h"

using namespace std;

class graph{
	private:
		trapezoid* trapezoids[1000000];
        int size;
		int misSize;
		point* boxes[1000000];
		int boxesSize;
		splayTree* splay;
	public:
		graph() {size = 0; misSize = 0; boxesSize = 0; splay = new splayTree();} //Start with an empty graph
		void readData();
		void mergesort(int start, int end);
		void merge(int start, int middle, int end);
		int checkLeft(trapezoid* trap, point* p);
		int checkRight(trapezoid* trap, point* p);
		void sweepLine();
		//getters
		int getMisSize() {return misSize;}
		int getSize() {return size;}
		int getBoxesSize() {return boxesSize;};
		int getBoxesX(int i) {return boxes[i]->getX();}
		int getBoxesY(int i) {return boxes[i]->getY();}
		point* getBoxes(int i) {return boxes[i];}
};

#endif /* graph_H */
