#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "tree.h"
#include <string.h>
#include <ctype.h>
#include "pack.h"

#define p(x) ((x-1)/2)
#define l(x) ((x*2)+1)
#define r(x) ((x*2)+2)

int* createFreqArray ();
void readFile (int charFreq[], FILE* file);
void insert (struct tree* tp);
struct tree *delete(void);
void printing (struct tree *bitNode);

struct tree *nodes[257] = {NULL}; // initializing global nodes pointer
struct tree *minHeap[257] = {NULL}; // initializing global heap pointer
int heapCounter = 0; // initializing global heap counter

int main(int argc,char *argv [2])
{
	int *charFreq; // initializing array pointer
	FILE *file; // initializing file pointer
	int i; // initializing loop variable
	
	charFreq = createFreqArray(); // creating array to hold frequencies

	file = fopen(argv[1], "r"); // opening file to be read

	if (file == NULL){ 
		printf("\nERROR IN OPENING FILE"); // if error in opening file
		return 0;
	}

	readFile(charFreq, file); // assigning frequency of letter to correct index
 
	// extract charFreq's with data and put into nodes
	for (i = 0; i < 257; i++){ 
		if (charFreq[i] != 0){ // if array value does not equal zero
			nodes[i] = createTree(charFreq[i], NULL, NULL); // create node with data in array
		}
	}
	
	// initialize node for EOF
	nodes[256] = createTree (0, NULL, NULL);
 
	// since all nodes in nodes will be values we need, insert all of them into priority que
	for (i = 0; i < 257; i++){ 
		if (nodes[i] != NULL){ 
			insert(nodes[i]); // if node contains data, insert into the heap
		}
	}

	// creating huffman tree
	struct tree *min1;
	struct tree *min2;
	struct tree *newTree;
	
	while (heapCounter > 1){ // continue as long as one element in heap
		min1 = delete(); // take out first element in heap
		min2 = delete(); // take out second element in heap
		newTree = createTree(getData(min1) + getData(min2), min1, min2); // create new tree with combined data
		insert(newTree); // insert new tree back into heap
	}

	// printing encoded values
	int element; 	
	for (element = 0; element < 257; element++){

		if(nodes[element] != NULL){ // if data in nodes[element] then print data
			if (isprint(element)) // if printable character printf first else do second
				printf("'%c': %d ",(char) element, getData(nodes[element]));
			else
				printf("'%03o': %d ",(char) element, getData(nodes[element]));

			printing (nodes[element]); // run print function to find character encoding 
			printf("\n"); // simply for formating purposes
		}
	}
	
	pack(argv[1], argv[2], nodes); // running pack function
	
	destroyTree(nodes[0]); // destroying tree

	fclose(file); // closing file

	return 0;
}

void printing (struct tree *bitNode){
	struct tree *temp;
	if ((temp = getParent(bitNode)) == NULL){
		return; // if parent is null return to previous node, that node which is the root
	}else{
		printing(temp); // once hit root node, this will return with the root
	}

	temp = getRight(getParent(bitNode)); // using temp to check whether left or right child
	if(temp == bitNode){ // if left print a 0 if right print a 1
		printf("0");	
	}else {
		printf("1");
	}
}

void insert (struct tree* tp){
	assert (tp != NULL); 

	struct tree *temp; 
	int index = heapCounter; // initializing index to heapCounter
	minHeap[heapCounter] = tp; // adding new element into last slot in heap

	// reheaping
	while(index > 0){
		if(getData(minHeap[p(index)]) > getData(minHeap[index])){ // if data in parent is > than data in child
			// switch spots with child and parent
			temp = minHeap[index]; 
			minHeap[index] = minHeap[p(index)];
			minHeap[p(index)] = temp;
			index = p(index); // reinitializing index to check parent of parent
		}
		else
			break; // if case not satisfied above, then heap is good
	}
	heapCounter++; // increment heapCounter since added a new element
}

struct tree *delete(void){
	int index = 0; // initializing index to zero to delete from front
	struct tree *temp;
	int child;
	struct tree *treeDelete; 
	
	treeDelete = minHeap[0]; // assigning treeDelete to first element
	minHeap[0] = minHeap[heapCounter-1]; // taking last added element and moving it to first slot
	minHeap[heapCounter-1] = NULL; // overwriting last slot added
	heapCounter--; // since deleted, heapcounter decrement
	
	//reheaping
	while (l(index) < heapCounter) {
		
		child = l(index); // child index
		
		// testing to find smallest child
		if (r(index) < heapCounter && getData(minHeap[r(index)]) < getData(minHeap[child]))
			child = r(index);

		// if data in child is less than parent
		if (getData(minHeap[child]) < getData(minHeap[index])){			
			// switch the two nodes
			temp = minHeap[index];
			minHeap[index] = minHeap[(child)];
			minHeap[(child)] = temp;
	
			index = l(index); // reinitialize index to left child of index
		}else
			break; // if nothing excecuted then heap is good
	}

	return treeDelete; 
}

void readFile (int charFreq[], FILE* file){
	int index;
	while ((index = fgetc(file)) != EOF){ // while index doesnt equal EOF
		charFreq [index]++; // increase frequency index by then
	}

	return; 
}

int* createFreqArray (){
	int *freqArray;
	int init = 0;

	freqArray = malloc(sizeof(int)*257); // allocating memory for array
	assert(freqArray != NULL); // making sure array pointer is not empty
		
	while (init != 257){
		freqArray[init] = 0; // initializing all slots in array to 0
		init++;
	}

	return freqArray;
}
