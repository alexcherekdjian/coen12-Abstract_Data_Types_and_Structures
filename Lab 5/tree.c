#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "tree.h"

struct tree {
int data;
struct tree *left;
struct tree *right;
struct tree *parent;
};

// Big-O = O(1)
struct tree *createTree(int data, struct tree *left, struct tree *right){
	struct tree *newTree;

	newTree = malloc(sizeof(struct tree)); // allocating memory for node
	assert(newTree != NULL); // making sure tree pointer is not empty
	newTree->data = data; // assigning data to node
	
	newTree->parent = NULL; // setting parent pointer to empty
	
	setLeft(newTree,left); // setting left pointer
	
	setRight(newTree,right); // setting right pointer

	return newTree;
}

// Big-O = O(n), runs for how many nodes in tree
void destroyTree(struct tree *root){

		if (root == NULL){ 
			return; // if root is emtpy than return to leaf node
		}else{
			destroyTree(root->left); // destroy left child
			destroyTree(root->right); // destroy right child
			free(root); // free the tree
			}
}

// Big-O = O(1)
int getData(struct tree *root){
	assert (root != NULL);	// make sure variable passed is not empty

	return (root->data); // return data
}

// Big-O = O(1)
struct tree *getLeft(struct tree *root){
	assert (root != NULL); // make sure variable passed is not empty

	return (root->left); // return left child
}

// Big-O = O(1)
struct tree *getRight(struct tree *root){
	assert (root != NULL); // make sure variable passed is not empty

	return (root->right); // return right child
}

// Big-O = O(1)
struct tree *getParent(struct tree *root){
	assert (root != NULL); // make sure variable passed is not empty

	return (root->parent); // return parent 
}

// Big-O = O(1)
void setLeft(struct tree *root, struct tree *left){
	assert (root != NULL);

	if (root->left == NULL){ // if node left child is empty assign it with left
		root->left = left;
	}else{	// if not then detach left child and assign left
		root->left->parent = NULL;
		root->left = left;
		}
	if (left != NULL){ // if left is not empty
		if (left->parent != NULL){ // if left has a parent
			if(left->parent->left == left) // if left's parent points to left
				left->parent->left = NULL; // assign parents left pointer as empty		
			else
				left->parent->right = NULL; // assign parents right pointer as empty
		}	
		left->parent = root; // assign lefts parent as the root
	}
}

// Big-O = O(1)
void setRight(struct tree *root, struct tree *right){
	assert (root != NULL);

	if (root->right == NULL){ // if node right child is empty assign it with right
        	root->right = right; 
       		
	}else{ // if not then detach right child and assign right
        	root->right->parent = NULL; 
        	root->right = right;
        	
        	}
	
	 if (right != NULL){ // if right is not empty
                if (right->parent != NULL){ // if right has a parent
                        if(right->parent->right == right) // if right's parent points to right
                                right->parent->right = NULL; // assign parents right pointer as empty
                        else    
                                right->parent->left = NULL; // assign parents left pointer as empty
                }
        	right->parent = root; // assign rights parent as the root
	}
	
}
