/*
Alex Cherekdjian
Coen 12L, Mon 2:15
Project 2 - Sorted
January 23, 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

static int findElement(SET* sp, char* elts, bool *found);

struct set {                                     // initializing set
    char **elts;
    int len;
    int count;
};

// Big O Notation: O(1) since no loops
SET *createSet(int maxElts){
    
    SET *sp;                                     // creating set pointer
    sp = malloc(sizeof(SET));                    // dynamically allocating memory for the structure
    assert (sp != NULL);                         // making sure sp does not point to nothing
    sp->elts = malloc(sizeof(char*)*maxElts); 	 // making space for char pointer to array size of maxElts
    assert (sp->elts != NULL);                   // making sure not empty
    sp->len = maxElts;                           // initializing length parameter
    sp->count = 0;                               // initializing count parameter
    
    return sp;                                   // returning pointer
}

// Big O Notation: O(n) since increment is linear for the for loop
void destroySet(SET *sp){
    assert (sp != NULL);                         // make sure sp is not empty
    
    for (int i=0; i < (sp->count); i++) {        // starting from first slot and going through array
        free (sp->elts[i]);                      // freeing contents in array first
    }
    free (sp->elts);                             // free array itself
    free (sp);                                   // free structure
    
    return;
}

// Big O Notation: O(1) since no loops
int numElements(SET *sp){
    return (sp->count);                          // return value in count
}

// Big O Notation: O(log n) since findElement is O(log n)
bool hasElement(SET *sp, char *elt){
    assert(sp!= NULL);                           // making sure sp points to structure
    
    int result;                                  // creating int variable to hold result of findElements
    bool found;                                  // creating bool variable to store search result
    
    result = findElement(sp, elt, &found);       // calling find elements function
    if (found == false){                         // if result is not there, return false
        return false;
    }
    return true;
}

// Big O Notation: O(n) since findElement is O(log n) & the for loop is O(n) so combined = O(log n + n) but only care about fastest growing element, which is n
bool addElement(SET *sp, char *elt){
    assert(sp!= NULL);                           // making sure sp points to structure
    
    int result;                                  // creating int variable to hold result of findElements
    bool found;                                  // creating bool variable to store search result
    
    result = findElement(sp, elt, &found);       // calling find elements function
    
    if (found == false){                         // if result to be added is not there, add
        int i;
        
        for (i = (sp->count); i > result; i--) { // Big O Notation: O(n) increment is linear
            sp->elts[i] = sp->elts[i-1];         // shifting array down, making room for new element
            }
        
        sp->elts[result]= strdup(elt);           // copy contents of elt into last spot in array
        (sp->count)++;                           // added element, thus increment counter variable
        
        return true;                             // if success, return true
    }
    
    return false;
}

// Big O Notation: O(n) since findElement is O(log n) & the for loop is O(n) so combined = O(log n + n) but only care about fastest growing element, which is n
bool removeElement(SET *sp, char *elt){
    assert(sp!= NULL);                           // making sure sp points to structure
    
    int result;                                  // creating int variable to hold result of findElements
    bool found;                                  // creating bool variable to store search result
    int i;                                       // variable for 'for' loop
    
    result = findElement(sp, elt, &found);       // calling find elements function
    if (found == false){                         // if result to be removed is not there, return false
        return false;
        }

    free(sp->elts[result]);                      // if search success, free the space with that index
    
    for (i = result; i < (sp->count); i++) { // Big O Notation: O(n) since increment is linear
        sp->elts[i] = sp->elts[i+1];             // moving everything in array up one slot
        }
    
    (sp->count)--;                               // decrease counter in set by one since removed
    return true;                                 // return removal successful
}

// Big O Notation: O(log n) since this is a binary search alogorithm
static int findElement(SET *sp, char *elt, bool *found){
    assert(sp!= NULL);                           // making sure sp points to structure
    
    int lo, mid, hi;                             // creating int's for indexes
    lo = 0;                                      // initialzing lo
    hi = (sp->count)-1;                          // initialzing hi
    mid = (lo + hi)/2;                           // initialzing mid
    int cmp;                                     // initialzing cmp variable for strcmp return
   
    while (lo <= hi){                            // if lo exceeds hi then search is false
        cmp = strcmp((sp->elts[mid]),elt);       // storing response of strcmp in cmp
        
        if (cmp == 0){                           // if cmp = 0 then return location and set found = true
            *found = true;
            return mid;
            }
        
        if (cmp > 0){                            // if cmp > 0 then reinitialze hi and mid values
            hi = mid-1;
            mid = (lo +hi)/2;
        }else{                                   // if cmp < 0 then reinitialze lo and mid values
            lo = mid+1;
            mid = (lo +hi)/2;
        }
    }
    
    *found = false;                              // if reaches end of loop, search failed
    return lo;                                   // points to where a new addition should be inserted

}

