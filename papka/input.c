#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "input.h"


void prnt(char** t, int n){
    for(int i = 0 ; i < n ; i++){
        printf("\n%s" , t[i]);
    }
}

char** delete_sentence(char** t , int z ,int *n){
    char** t1;
    free(t[z]);
    for(int q = z ; q < (*n - 1) ; q++ ){
        t[q] = t[q + 1];
    }
    (*n)--;
    t1 = realloc(t , sizeof(char*) * (*n) );
    return t1;

}


void delete_duble(char** t, int *n){
    for(int i = 0 ; i < *n - 1 ; i++ ){
        for(int z = (i + 1) ; z < *n ; z ++ ){
            if (strcmp(t[i], t[z]) == 0){ // Р±РµР· СѓС‡РµС‚Р° СЂРµРіРёСЃС‚СЂР°
                t = delete_sentence(t , z , n);
                z--;
            }
        }
    }
}

char* input_sentence(char* end){
    char *str,*str1;
    int i = 0;
    str = (char *)malloc(sizeof(char));
    do{
        *end = getchar() ;
        str[i] = *end;
        i++;
        str = realloc(str ,(i + 1) * sizeof(char));
    }
    while((*end != '\n') && (*end != '.'));
    str[i] = '\0';
    return str;
}


char** input_text(int* number_of_sentence){
    char **text,**t;
    char end_of_sentece;

    *number_of_sentence = 0;
    text = (char **)malloc(sizeof(char **));
    do{
        text[*number_of_sentence] = input_sentence(&end_of_sentece);
        (*number_of_sentence)++;
        text = (char **)realloc(text, (*number_of_sentence + 1)*sizeof(char *));
    }
    while(end_of_sentece != '\n');
    (*number_of_sentence)--;
    return text;
}



