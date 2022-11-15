//Quinn Corcoran
//giftsGiving

#ifndef tree_H
#define tree_H

#include "node.h"

using namespace std;

class tree{
	private:
		int n;
		node* root;
		int size;
		int* mis; //this is an array
		int misSize;
		node** nodes; //this is an array
		node* saved;
		node** brute; //this is an array
		int bruteSize;
	public:
		tree() {n = 0; root = NULL; size = 0; misSize = 0; bruteSize = 0;} //Start with an empty tree
		~tree();
		void readData();
		void insert(int parentLable, int childLable, node* curNode);
		void trim(node* leaf);
		void computeMIS(node* curNode);
		void postorderSearch(node* curNode, string job);
		int visit(node* curNode, string job);
		void mergesort(int start, int end, string job);
		void merge(int start, int middle, int end, string job);
		void bruteForce();
		void findSubsets(node* subset[], int subsetSize, int index);
		int validate(node* arry[], int arrySize);
		//getters
		node* getRoot() {return root;}
		int getSize() {return size;}
		int getMis(int index) {return mis[index];}
		int getMisSize() {return misSize;}
};

#endif /* tree_H */
