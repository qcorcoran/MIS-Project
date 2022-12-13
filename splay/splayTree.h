//Quinn Corcoran
//splay

#ifndef splayTree_H
#define splayTree_H

#include "splayNode.h"

using namespace std;

class splayTree{
	private:
		splayNode* root;
		int size;
	public:
		splayTree() {root = NULL; size = 0;} //Start with an empty tree
		~splayTree();
		void insert(splayNode* n, splayNode* current);
		void splayInsert(splayNode* n, splayNode* r);
		void zigRotate(splayNode* pivot);
		void zagRotate(splayNode* pivot);
		void splay(splayNode* x);
		splayNode* splayMax(splayNode* r);
		splayNode* splayMin(splayNode* r);
		splayNode** split(splayNode* x);
		splayNode* join(splayNode* leftSide, splayNode* rightSide);
		void splayDelete(splayNode* x);
		splayNode* search(int k, splayNode* r);
		splayNode* splaySearch(int k);
		void inorderTraversal(splayNode* n);
		void preorderTraversal(splayNode* n);
        //getters
        splayNode* getRoot() {return root;}
};

#endif /* splayTree_H */
