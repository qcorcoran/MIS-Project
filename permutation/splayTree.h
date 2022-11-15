//Quinn Corcoran
//permutation

#ifndef splayTree_H
#define splayTree_H

#include "node.h"

using namespace std;

class splayTree{
	private:
		node* root;
		int size;
	public:
		splayTree() {root = NULL; size = 0;} //Start with an empty tree
		void insert(node* n, node* current);
		void splayInsert(node* n, node* r);
		void setHeight(node* n);
		void zigRotate(node* pivot);
		void zagRotate(node* pivot);
		void updateLis(node* n);
		void splay(node* x);
		node* splayMax();
		node** split(node* x);
		node* join(node* leftSide, node* rightSide);
		void splayDelete(node* x);
		node* search(int k, node* r);
		node* splaySearch(int k);
		node* getSuccessor(int k);
		void inorderTraversal(node* n);
		void preorderTraversal(node* n);
        //getters
        node* getRoot() {return root;}
};

#endif /* splayTree_H */
