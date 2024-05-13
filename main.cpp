#include <iostream>
#include "RBTree.h"

int main() {
	RBTree<int> tree;
	tree.insert(0);
	tree.PrintTree();

	tree.insert(0);
	tree.PrintTree();

	tree.insert(-1);
	tree.insert(2);
	tree.PrintTree();

	tree.insert(-2);	
	tree.PrintTree();

	tree.insert(-3);
	tree.PrintTree();
}