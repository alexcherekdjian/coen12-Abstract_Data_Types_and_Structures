#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "deque.h"

typedef struct node NODE;

struct node {                      // defining node structure
  int data;
  struct node *next;
  struct node *prev;
};

struct deque {                     // defining deque structure
int count;
struct node *head;

};

// Big O = O(1)
DEQUE *createDeque(void){
 DEQUE *dp;                       // creating pointer to deque
 dp = malloc (sizeof(DEQUE));     // allocating space for deque
 assert (dp != NULL);             // making sure the pointer is not null
 dp->count = 0;                   // initializing count
 dp->head = malloc (sizeof(NODE));// allocating memory for dummy node
 assert (dp->head != NULL);       // making sure dummy node is not empty
 dp->head->next = dp->head;       // initializing pointers
 dp->head->prev = dp->head;

return dp;
}

// Big O = O(n)
void destroyDeque(DEQUE *dp){
 assert (dp != NULL);           // making sure pointer is not null

 int i;
    for(i = 0; i < dp->count; i++)
        removeFirst(dp);        // using function defined to remove items

    free (dp->head);            // freeing dummy node
    free(dp);                   // freeing deque pointer
}

// Big O = O(1)
int numItems(DEQUE *dp){
 assert (dp != NULL);           // making sure pointer is not null
return dp->count;               // returning number of count

}

// Big O = O(1)
void addFirst(DEQUE *dp, int x){
 assert (dp != NULL);           // making sure pointer is not null
 
 NODE *pNew = malloc (sizeof(NODE)); // allocating memory for a new node
 assert (pNew != NULL);         // making sure allocation went well
    
 pNew->data = x;                // assigning data x to node
 
 pNew->next = dp->head->next;   // initializing new node pointers
 pNew->prev = dp->head;

 dp->head->next->prev = pNew;   // initializing dummy and node after first node pointers
 dp->head->next = pNew; 
 dp->count++;                   // increasing count

}

// Big O = O(1)
void addLast(DEQUE *dp, int x){
  assert (dp != NULL);          // making sure pointer is not null
    
  NODE *pNew = malloc (sizeof(NODE)); // allocating memory for new node
  assert (pNew != NULL);        // making sure allocation went smoothly
    
  pNew->data = x;               // assigning data to new node
  
  pNew->next = dp->head; // initializing new node pointers
  pNew->prev = dp->head->prev; 
  
   
  dp->head->prev->next = pNew; // initializing dummy and node after first node pointers
  dp->head->prev = pNew; 
  
  dp->count++;                 // increasing count
  return;

}

// Big O = O(1)
int removeFirst(DEQUE *dp){
 assert (dp != NULL);         // making sure pointer is not null
 assert (dp->count > 0);      // making sure counter is not null

 NODE *pDel = dp->head->next; // making pDel equal to item we want to delete

 dp->head->next = pDel->next; // reassigning pointers accordingly
 dp->head->next->prev = dp->head;
    
 int ans = pDel->data;       // assigning ans to data in pDel

 free (pDel);                // releasing pDel

 dp->count--;                // decreasing count
 return ans;

}

// Big O = O(1)
int removeLast(DEQUE *dp){
 assert (dp != NULL);       // making sure pointer is not null
 assert (dp->count > 0);    // making sure counter is not null
 
 NODE *pDel = dp->head->prev;// making pointer pDel equal to what we want to delete

 pDel->prev->next = dp->head;// reassigning pointers accordingly
 dp->head->prev = pDel->prev; 
 
 int ans = pDel->data;      // assigning ans to data in pDel
 free (pDel);               // releasing pDel
 dp->count--;               // decreasing counter

 return ans;

}

// Big O = O(1)
int getFirst(DEQUE *dp){
 assert (dp != NULL);     // making sure pointer is not null
 assert (dp->count != 0); // making sure counter is not null
 int ans; 
 ans = dp->head->next->data; // assigning the ans to the data in the first node
 return ans; // returning data int
}

// Big O = O(1)
int getLast (DEQUE *dp){
 assert (dp != NULL); // making sure pointer is not null 
 assert (dp->count != 0); // making sure counter is not null
 int ans;
 ans = dp->head->prev->data; // assigning the ans to the data in the first node
 return ans; // returning data int
}
