#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdbool>
#include "deque.h"

struct Node {			 // defining node structure
  int data;
  struct Node *next;
  struct Node *prev;
};


// Big O = O(1)
Deque::Deque() {
 
 count  = 0;			 // initializing count
 head  = new Node;		 // making new dummy node
 head->next = head;		 // initializing pointers
 head->prev = head; 

}

// Big O = O(n)
Deque::~Deque() {

 int i;
    for(i = 0; i < count; i++)
        removeFirst();		 // using function defined to remove first items

    delete head;		 // freeing dummy node
}

// Big O = O(1)
int Deque::size(){

return count;			 // returning number of count

}

// Big O = O(1)
void Deque::addFirst(int x){
 
 Node  *pNew = new Node;	 // making  a new node
    
 pNew->data = x;		 // assigning data x to node
 
 pNew->next = head->next;	 // initializing new node pointers
 pNew->prev = head;

 head->next->prev = pNew;	 // initializing dummy and node after first node pointers
 head->next = pNew; 

 count++;			 // increasing count

}

// Big O = O(1)
void Deque::addLast(int x){
    
  Node *pNew = new Node;	 // making  new node
    
  pNew->data = x;		 // assigning data to new node
  
  pNew->next = head;		 // initializing new node pointers
  pNew->prev = head->prev; 
  
  head->prev->next = pNew;	 // initializing dummy and node after first node pointers
  head->prev = pNew; 
  
  count++;			 // increasing count

}

// Big O = O(1)
int Deque::removeFirst(){

 Node *pDel = head->next;	 // making pDel equal to item we want to delete

 head->next = pDel->next;	 // reassigning pointers accordingly
 head->next->prev = head;
    
 int ans = pDel->data;		 // assigning ans to data in pDel
 delete pDel;			 // deleting  pDel

 count--;			 // decreasing count

 return ans;

}

// Big O = O(1)
int Deque::removeLast(){
 
 Node  *pDel = head->prev;	 // making pointer pDel equal to what we want to delete

 pDel->prev->next = head;	 // reassigning pointers accordingly
 head->prev = pDel->prev; 
 
 int ans = pDel->data; 		 // assigning ans to data in pDel
 delete pDel;			 // deleting pDel

 count--; 			 // decreasing counter

 return ans;

}

// Big O = O(1)
int Deque::getFirst(){

 int ans; 
 ans = head->next->data; 	 // assigning the ans to the data in the first node

 return ans;			 // returning data
}

// Big O = O(1)
int Deque::getLast(){

 int ans;
 ans = head->prev->data; 	 // assigning the ans to the data in the first node

 return ans;			 // returning data int
}
