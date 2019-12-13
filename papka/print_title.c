#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "print_title.h"

int sort_function(const void* a, const void* b){
	char* a1 = (char*) a;
	char* b1 = (char*) b;
	if (*a1 == *b1) 
		return 0;
	if (*a1 < *b1) 
		return -1;
	if (*a1 > *b1)
		return 1;
}

void print_title(char** arr1, int number_of_sentence){	
	for (int i = 0; i < number_of_sentence; i++){
		char* arr2 = (char*)malloc(strlen(arr1[i])*sizeof(char));
		strcpy(arr2, arr1[i]);		
		qsort(arr2, strlen(arr2), sizeof(char), sort_function);
		for (int j = 0; j < strlen(arr2); j++){
			if (isupper(arr2[j])){		
				printf("%c",arr2[j]);
			}
		}
		free(arr2);
		printf("\n");
	}
}
