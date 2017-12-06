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

static int findElement(SET* sp, char* elts);

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
        free (sp->elts[i]);                      // going through array and freeing space
    }
    free (sp->elts);                             // free array itself
    free (sp);                                   // free structure
    
    return;
}

// Big O Notation: O(1) since no loops
int numElements(SET *sp){
    return (sp->count);                          // return value in count
}

// Big O Notation: O(n) since calls FindElement and FindElement function has O(n)
bool hasElement(SET *sp, char *elt){
    assert (sp != NULL);                         // make sure sp is not empty
    
    int result;                                  // creating integer var to hold result of findElements
    
    result = findElement(sp, elt);               // calling find elements function
    
    if (result == -1){                           // if result is not there, return false
        return false;
    }
    
    return true;                                 // else if no error, can return true
}

// Big O Notation: O(n) since calls FindElement and FindElement function has O(n)
bool addElement(SET *sp, char *elt){
    assert (sp != NULL);                         // make sure sp is not empty
    
    int result;                                  // creating int variable to hold result of findElements
    
    result = findElement(sp, elt);               // calling find elements function
    
    if (result == -1){                           // if result to be added is not there, add
        sp->elts[sp->count]= strdup(elt);        // copy contents of elt into last spot in array
        (sp->count)++;                           // added element, thus increment counter variable
        return true;                             // if success, return true
    }
    
    return false;
}
// Big O Notation: O(n) since calls FindElement and FindElement function has O(n)
bool removeElement(SET *sp, char *elt){
    assert (sp != NULL);                         // make sure sp is not empty
    
    int result;                                  // creating int variable to hold result of findElements
    
    result = findElement(sp, elt);               // calling find elements function
    
    if (result == -1){                           // if result to be removed is not there, return false
        return false;
    }
    
    free(sp->elts[result]);                      // if search success, free the space with that index
    sp->elts[result]=sp->elts[sp->count-1];      // copy last element in array to the now empty space
    (sp->count)--;                               // decrease counter in set by one since removed item
    
    return true;                                 // return removal successful
}

// Big O Notation: O(n) since increment is a linear algorithm
static int findElement(SET *sp, char *elt){
    assert (sp != NULL);                         // make sure sp is not empty

    int result;                                  // creating integer variable to hold result of strcmp
    
    for (int i=0; i < (sp->count); i++) {
        result = strcmp(sp->elts[i], elt);       // looping through array to find element
        
        if (result == 0)
            return i;                            // if elt in array = elt search, return index of array
    }
    
    return -1;                                   // return -1 signifying failure in search
}

