//Quinn Corcoran
//trapezoidShooting

#ifndef trapezoidGraph_H
#define trapezoidGraphh_H

#include "trapezoid.h"
#include "point.h"
#include "splayTree.h"

using namespace std;

class trapezoidGraph{
	private:
		int n;
		trapezoid** trapezoids; //this is an array
        int size;
		int misSize;
		point** boxes; //this is an array
		int boxesSize;
		splayTree* splay;
	public:
		trapezoidGraph() {n = 0; size = 0; misSize = 0; boxesSize = 0; splay = new splayTree();} //Start with an empty graph
		~trapezoidGraph();
		void readData();
		void transformToBoxes();
		int checkLeft(trapezoid* trap, point* p);
		int checkRight(trapezoid* trap, point* p);
		void sweepLine();
		void mergesort(int start, int end);
		void merge(int start, int middle, int end);
		//getters
		int getMisSize() {return misSize;}
		int getSize() {return size;}
		int getBoxesSize() {return boxesSize;};
		int getBoxesX(int i) {return boxes[i]->getX();}
		int getBoxesY(int i) {return boxes[i]->getY();}
		point* getBoxes(int i) {return boxes[i];}
};

#endif /* trapezoidGraph_H */
