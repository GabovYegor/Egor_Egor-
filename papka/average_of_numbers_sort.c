#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "average_of_numbers_sort.h"

float average_of_numbers_sentence(char* text){
	float average = 0;
	float count = 0;
	float sum = 0;
	float a = 0;
	for (int j = 0; j < strlen(text); j++){
			if ((isdigit(text[j])) && ((j == 0) || (text[j-1] == ' '))){
				while (isdigit(text[j]))  {
					a = a * 10 + (text[j] - '0');
					j++;						
				}
				if ((text[j] != ' ') && (text[j] != '.') && (text[j] != ','))
					a = 0;					
				j--;			
				sum = sum + a;
				count++;
				a = 0;			
			}
			else {
				a = 0;
			}
		}
	if(count != 0){
		average = sum/count;
		printf("%.1f\n",average);
		}
	return average;
}

int cmp(const void* a, const void * b) {
	char* a1 = *((char**) a);
	char* b1 = *((char**) b);
	float forA = average_of_numbers_sentence(a1);
	float forB = average_of_numbers_sentence(b1);
	if(forA < forB)
		return -1;
	if(forA == forB)
		return 0;
	if(forA > forB)
		return 1;

}


void average_of_numbers_sort(char** text, int number_of_sentence){
	qsort(text, number_of_sentence, sizeof(char*), cmp);
}
