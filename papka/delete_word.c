#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"delete_word.h"

int delete_word(char** text, int number_of_sentence , char* word){
    for(int i = 0; i < number_of_sentence; i++){
        char* prt = strstr(text[i], word);
        if(prt != NULL) {
            if(prt == text[i]) {
                if(*(prt+strlen(word)) == ' ' || *(prt+strlen(word)) == ',' || *(prt+strlen(word)) == '.') {
                    for (int q = 0; q < strlen(text[i]) - strlen(word); q++){
                        text[i][q] = text[i][q + strlen(word)];
                    }
                    text[i][strlen(text[i]) - strlen(word)] = '\0';
                }
            }
            else {
                if(*(prt - 1) == ' ' || *(prt - 1) == ',' &&
                        (*(prt+strlen(word)) == ' ' || *(prt+strlen(word)) == '.' || *(prt+strlen(word)) == ',')) {
                    for (int q = prt - text[i]; q < strlen(text[i]) - strlen(word); q++){
                        text[i][q] = text[i][q+strlen(word)];
                    }
                    text[i][strlen(text[i]) - strlen(word)] = '\0';
                }
            }
        }
        int flag = 1;
        for(int j = 0; j < text[i][j]; ++j) {
            if(text[i][j] != ' ' && text[i][j] != '.' && text[i][j] != ',') {
                flag = 0;
                break;
            }
        }

        if(flag == 1) {
            for(int k = i; text[k + 1]; ++k) {
                text[k] = text[k+1];
            }
            free(text[--number_of_sentence]);
        }
    }

    printf("After delete: \n");
    printf("----------------------------------\n");
    for(int i = 0; i < number_of_sentence; ++i) {
        printf("%s\n", text[i]);
    }
    printf("----------------------------------\n");
    return number_of_sentence;
}
