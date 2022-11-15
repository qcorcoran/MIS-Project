//Quinn Corcoran
//navigatingRiver

#ifndef bst_H
#define bst_H

#include "node.h"

using namespace std;

class bst{
	private:
		node* root;
		int size;
	public:
		bst() {root = NULL; size = 0;} //Start with an empty tree
		void insert(node* n, node* current);
		void splayInsert(node* n, node* r);
		void setHeight(node* n);
		int balanceFactor(node* n);
		void rotateLL(node* pivot);
		void rotateRR(node* pivot);
		void rotateLR(node* pivot);
		void rotateRL(node* pivot);
		void zigRotate(node* pivot);
		void zagRotate(node* pivot);
		node* search(int k, node* r);
		node* getSuccessor(int k);
		void inorderTraversal(node* n);
		void preorderTraversal(node* n);
        //getters
        node* getRoot() {return root;}
};

#endif /* bst_H */
