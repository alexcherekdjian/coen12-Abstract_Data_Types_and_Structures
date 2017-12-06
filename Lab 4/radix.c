#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "deque.h"

int main()
{
    int raddix = 10; // initializing radix
    int max = -1; // largest value stored here
    int input = 0; // initializing temporary storage for data streamed
    DEQUE *allNumbers; // initializing all deque pointers
    DEQUE *digit[raddix];
    
    int scanResult = 1; // initializing result from scanf
    
    // initializing variables for a for loop
    int i;
    int j;
    int k;
    
    for (i = 0; i < raddix; i++){ // initializing all deques
        digit[i] = createDeque();
    }
    
    allNumbers = createDeque(); // initializing deque to store initial data
    
    while (scanResult == 1){ // run loop until control d is implemented
        
        printf("\nInput a positive number (ctrl-D to run): "); // prompting for a positive number
        scanResult = scanf(" %d", &input); // assign scanResult value of scanf and assigning input value
        
        
        while(input < 0){
            printf("\nThat is negative. Input a positive number (ctrl-D to run): "); // if less that positive then need to choose another number
            scanResult = scanf(" %d", &input); // assign scanResult value of scanf and assigning input value
            
        }
        
        if (scanResult == 1) // if scanned in control d, precaution to not add into list
            addLast(allNumbers, input); // adding elements from last
        
        if (input > max){
            max = input; // if max is less that new input, set inpuut to new max
        }
    }
    
    int iterations;
    iterations = log(max+1)/log(raddix); // getting number of times needed to run
    int result; // result from modding whatever significant digit
    int number; // initializing number to total number of nodes
    int items = numItems(allNumbers); // number of items in allNumbers
    
    for(i = 0; i < log(max+1)/log(raddix); i++){
        for (j = 0; j < items; j++){
            number = removeFirst(allNumbers); // remove first node and get data
            result = (number/ (int) pow(10,i)) % 10; // result will equal a rounded approximation of that particular digit
            addLast(digit[result], number); // whatever digit that was, add to corresponding deque
        }
        
        int replace;
        int count = 0; // initializing parameters
        
        for (count= 0; count < 10; count++){
            int num = numItems(digit[count]); // getting number of items in certain deque
            for(k = 0; k < num; k++){
                replace = removeFirst(digit[count]); // if count not zero than move node data to main deque
                addLast(allNumbers, replace); // add to main deque
            }
        }
        // if number count = zero then skip cause nothing there
    }
    
    // printing all numbers
    int printing;
    printf("\n\nSorted Sequence\n"); // printing description
    for (i = 0; i < items; i++){
        printing = removeFirst(allNumbers); // grabbing data from real node
        printf("%d\n", printing); // printing the data
        
    }
    
    // destroy everything!!
    for (i = 0; i < 10; i++){
        destroyDeque(digit[i]); // destroying sorting digit deques
    }
    
    destroyDeque(allNumbers); // destroying main deque
    
    return 0;
}







