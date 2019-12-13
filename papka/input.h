#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


char** input_text(int* number_of_sentence);
void delete_duble(char **t, int *n);
char** delete_sentence(char** t , int z ,int *n);
void prnt(char** t,int n);


#endif /* INPUT_H_ */
