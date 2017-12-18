/*
Alex Cherekdjian 
COEN 12 Lab
January 9, 2017
TA: Alberto Diaz
*/

#include <stdio.h>
#define MAX_WORD_LENGTH 30 	// defining a max word length for the buffers sake

int main(int argc,char *argv [2]){

FILE *p; 			// creating file pointer
int count = 0; 			// creating integer to store word count
char word [MAX_WORD_LENGTH]; 	// creating array with size of buffer to store words 

p = fopen(argv[1], "r"); 	// creating file pointer and opening argv[1]

// running loop to read a word into word array and check to see if it is at the EOF
while (fscanf(p, "%s", word) != EOF){
	count++; 		// if successful, increment count integer by one	
	}

printf("%d total words\n",count); // printing final result

fclose (p); 			// closing file

}
