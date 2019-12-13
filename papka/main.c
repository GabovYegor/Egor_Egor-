#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "input.h"
#include "print_title.h"
#include "delete_word.h"
#include "average_of_numbers_sort.h"
#include "delete_without_lower.h"

void printText(char** text, int number_of_sentence) {
    printf("Source text: \n");
    printf("----------------------------------\n");
    for(int i = 0; i < number_of_sentence; ++i) {
        printf("%s\n", text[i]);
    }
    printf("----------------------------------\n");
}

int main(void) {
    int choice;
    int wordsize = 10;
    char* word;
    char **text;
    int number_of_sentence = 0;
    printf("Введите текст\n");
    text = input_text( &number_of_sentence );
    delete_duble(text, &number_of_sentence);
    printText(text, number_of_sentence);

    while(1){
        printf("\n1)Во всем тексте удалить слово введенное пользователем. Если после удаления в предложении не останется слов, его необходимо удалить.\n");
        printf("2)Для каждого предложения вывести все заглавные буквы в лексикографическом порядке.\n");
        printf("3)Отсортировать предложения по среднему арифметическому чисел в предложении. Число - слово состоящее только из цифр.\n");
        printf("4)Удалить все предложения в которых нет строчных букв.\n");
        printf("5)Выход из программы.\n");
        scanf("%d" , &choice);
        switch(choice){
        case 1:
            word = malloc(wordsize * sizeof(char));
            printf("%s","Введите слово\n");
            scanf("%s", word);
            printf("Your word: %s\n", word);
            number_of_sentence = delete_word(text, number_of_sentence, word);
            break;
        case 2:
            print_title(text, number_of_sentence);
            break;
        case 3:
            average_of_numbers_sort(text, number_of_sentence);
            for (int i = 0; i < number_of_sentence; i++)
                printf("%s",text[i]);
            break;
        case 4:
            delete_without_lower(text, number_of_sentence);
            for (int i = 0; i < number_of_sentence; i++)
                printf("%s",text[i]);
            break;
        case 5:
            free(text); // memory leak
            return 0;
        }
    }

    return 0;
}

