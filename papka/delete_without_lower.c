#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "delete_without_lower.h"

char** delete_without_lower(char** text, int* number_of_sentence) {
    for(int i = 0; i < *number_of_sentence; ++i) {
        int flag = 1;
        for (int j = 0; text[i][j]; ++j) {
            if ((text[i][j] < 'A' || text[i][j] > 'Z')
                 && text[i][j] != ' ' && text[i][j] != '.' && text[i][j] != ',') {
                flag = 0;
            }
        }
        if(flag) {
            for(int k = i--; text[k+1]; ++k) {
                text[k] = text[k+1];
            }
            free(text[--*number_of_sentence]);
        }
    }
}
