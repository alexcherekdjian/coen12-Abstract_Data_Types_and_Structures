#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

#define EMPTY 0
#define DELETED 1
#define FILLED 2

static int findElement(SET* sp, char* elts, bool *found);
unsigned hashString(char  *s);

struct set {
    int  *flags;
    char **elts;
    int len;
    int count;
};

// Big O Notation = O(n) since for loop runs n amount of times
SET *createSet(int maxElts){
    
    SET *sp;                                     // creating set pointer
    sp = malloc(sizeof(SET));                    // dynamically allocating memory for the structure
    assert (sp != NULL);                         // making sure sp does not point to nothing
    sp->elts = malloc(sizeof(char*)*maxElts); 	 // making space for character pointer to array size of maxElts
    assert (sp->elts != NULL);                   // making sure not empty
    sp->len = maxElts;                           // initializing length parameter
    sp->count = 0;                               // initializing count parameter
    sp->flags = malloc(sizeof(int*)*maxElts);	 // allocating memory for character array and initializing character pointer
    assert (sp->flags != NULL);                  // making sure character array pointer for flags was allocated

    for (int i = 0; i < maxElts; i++){  	 // initializing all flags in flag array to EMPTY
        sp->flags[i] = EMPTY;
    }

    return sp;                                   // returning pointer
}

// Big O Notation = O(n) since for loop runs n amount of times
void destroySet(SET *sp){
    assert (sp != NULL);                         // make sure sp is not empty

    for (int i=0; i < (sp->count); i++) {
        if (sp->flags [i] == FILLED){
            free (sp->elts[i]);                  // if flag array states FILLED, free element in array
	}    
    }

    free (sp->elts);                             // free array pointer
    free (sp->flags);                            // free flag array pointer
    free (sp);                                   // free structure
    
    return;
}

// Big O Notation = O(1) since there is only one operation to complete
int numElements(SET *sp){
    return (sp->count);                          // return value in count
}

// Big O Notation (worst case) = O(n) since calls FindElement and the worst case relies on how much we linear probe
// Big O Notation (best case) = O(1) assuming there are no collisions and hash function returns the correct index for the element we are searching
bool hasElement(SET *sp, char *elt){
    assert(sp!= NULL);                           // make sure sp is initialized
    int result;                                  // creating integer variable to hold result of findElements
    bool found;                                  // creating bool variable to be returned

    result = findElement(sp, elt, &found);       // calling find elements function
    if (found == false){                         // if false, search failed thus return false
        return false;
    }
        return true;                             // else if no error, then find element function has done it's job, thus can return true
}

// Big O Notation (worst case) = O(n) since calls FindElement and the worst case relies on how much we linear probe
// Big O Notation (best case) = O(1) assuming there are no collisions and hash function returns the correct index for the element we are searching
bool addElement(SET *sp, char *elt){
    assert(sp!= NULL);                           // make sure sp is initialized
    int result;                                  // creating integer variable to hold result of findElements
    bool found;                                  // creating bool variable to be returned
    
    result = findElement(sp, elt, &found);       // calling find elements function
    
    if (found == false){                         // if result to be added is not there, add
        sp->elts[result] = strdup(elt);          // copy contents of elt into last spot in array
        sp->flags[result] = FILLED;              // initialize flag to be filled
        (sp->count)++;                           // added element, thus increment counter variable
        return true;                             // if success, return true
    }
    return false;
    
}

// Big O Notation (worst case) = O(n) since calls FindElement and the worst case relies on how much we linear probe
// Big O Notation (best case) = O(1) assuming there are no collisions and hash function returns the correct index for the element we are searching
bool removeElement(SET *sp, char *elt){
    assert(sp!= NULL);                           // make sure sp is initialized
    int result;                                  // creating integer variable to hold result of findElements
    bool found;                                  // creating bool variable to be returned
    
    result = findElement(sp, elt, &found);       // calling find elements function
    if (found == false){                         // if result to be removed is not there, return false
        return false;
    }
    
    free(sp->elts[result]);                      // if search success, free the space with that index
    sp->flags[result] = DELETED;                 // initialize flag to be deleted
    (sp->count)--;                               // decrease counter in set by one since removal was successful
    
    return true;                                 // return removal successful
}

// Big O Notation (worst case) = O(n) since the worst case relies on how much we linear probe
// Big O Notation (best case) = O(1) assuming there are no collisions and hash function returns the correct index for the element we are searching
static int findElement(SET *sp, char *elt, bool *found){
    assert(sp!= NULL);                           // make sure sp is initialized
    int result;                                  // stores result of strcmp
    int marker = -1;                             // if stays -1 thus failed search, if different then a deleted spot was found
    int deleteCounter = 0;                       // counter to insure that if a deleted spot is found that the first one is kept in storage
    
    result = hashString(elt)% (sp->len);         // running hash function
    
    while (sp->flags[result] != EMPTY){          // initializing loop to run until empty spot found

        if (sp->flags[result] == FILLED){
            if (strcmp(elt,sp->elts[result]) == 0){
                *found = true;                   // if string found return true and the index of where it is
                return result;
            }
        }
        if (sp->flags[result] == DELETED){
            if (deleteCounter != 1){             // make counter so marker only initializes the first time
		  marker = result;               // assign marker to index of result
           	  deleteCounter++;               // increase counter so first deleted spot is saved only
             }
        }
        if (result == ((sp->len)-1)){
            result = 0;                          // if index of result is = to the last index, reset result to continue at start
        }else
            result++;                            // if not returned, increase result to search next spot
        }
    
	*found = false;                          // if exited loop initialize found to false since search failed
	if (marker == -1){                       // if deleted spot not found then return the empty spot
            return result;
        }else {
            return marker;                       // if deleted marker found return marker
	}
}

unsigned hashString(char *s) {
	unsigned hash = 0;                       // hash function given to us for lab
	
	while (*s != '\0')
		hash = 31 * hash + *s++; // the hash function
	
    	return hash;                             // returning hash result
}



