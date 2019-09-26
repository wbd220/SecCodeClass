#include <check.h>
#include "dictionary.h"
//#include "dictionary.c"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define DICTIONARY "/root/CLionProjects/SecCoding/wordlist.txt"

int main() {
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char * misspelled[0];

    FILE * fp;
    fp = fopen("test1.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int num_mispelled = check_words(fp, hashtable, misspelled);

    printf("misspelled words: %d\n", num_mispelled);
    int i = 0;
    while(misspelled[i] != NULL){
        printf("%s\n", misspelled[i]);
        i++;
    }

    while(misspelled != NULL){
        free(misspelled);
    }
}

/*
//  test out the check_word routine  (and technically load_dictionary)
    const char* correct_word = "Justice";
    const char* incorrect_word = "Caoimhín";
    int test1 = check_word(correct_word, hashtable);
    int test2 = check_word(incorrect_word, hashtable);
    printf("Test1 is %d, and Test2 is %d\n", test1, test2);
}
 */