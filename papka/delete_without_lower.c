#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "delete_without_lower.h"

char** delete_without_lower(char** text,int n){
	for (int i = 0; i < n; i++){
		char* str;
		int q = n;
		str = malloc((strlen(text[i])/*+1*/) * sizeof(char));
		strcpy(str, text[i]);
		for(int j = 0; j <strlen(str); j++) {
			str[j] = toupper(str[j]);
		}		
		if (strcmp(str,text[i]) == 0){
			free(text[i]);
			q--;
			if (i != q-1){
				for (int k = i; k<q-2; k++){
						text[k] = text[k+1];
				}
				free(text[q-1]);
			}			
		}
		free(str);
	}	
}
