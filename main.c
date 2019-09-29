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
    char *misspelled[0];

    FILE *fp;
    fp = fopen("text2test.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int num_mispelled = check_words(fp, hashtable, misspelled);

    printf("misspelled words: %d\n", num_mispelled);
    int i = 0;
    while (misspelled[i] != NULL) {
        printf("%s\n", misspelled[i]);
        i++;
    }
    //Free your misspelled array
    int q;
    for (q = 0; q < num_mispelled; q++) {
        free(misspelled[q]);
    }
}
/* just another stab at freeing the dictionary memory, but fails
    for (int r = 0; r < HASH_SIZE; r++) {  // for the length of the hashmap
        node * curr = hashtable[r];
        while (curr != NULL) {
            node *next = curr->next;
            free(curr);
            curr = next;
        }
    }
}
 */
/*
// another stab at freeing the dictionary memory
    hashmap_t second_last;
    for (int r = 0; r < HASH_SIZE; r++) {  // for the length of the hashmap
        if (hashtable[r]->next == NULL) {
            free(hashtable[r]);
        }
        else {
            while (hashtable[r]->next != NULL) {
                second_last = hashtable[r];
                while (second_last->next->next != NULL) {
                    second_last = second_last->next;
                }

                // Delete last node
                free(second_last->next);

                // Change next of second last
                second_last->next = NULL;

                if (second_last == hashtable[r]) {
                    hashtable[r]->next = NULL;
                    free(second_last);
                }
            }
        }
    }
}
*/
 /*
//Free your dictionary hashtable (and linked lists!)
hashmap_t back1, cursor;
for (int r = 0; r < HASH_SIZE; r++) {  // for the length of the hashmap
    while (hashtable[r] != NULL) {
            cursor = hashtable[r];
            back1 = NULL;  //trailing, next to last node

            while(cursor->next != NULL)  //for as long as there is a next
            {
                back1 = cursor;          //set the back to cursor
                cursor = cursor->next;   //set the cursor to the next
            }                            // this should stop with cursor at last and back1 trailing

            if(back1 != NULL)
                back1->next = NULL;

            // if this is the last node in the list
            if(cursor == hashtable[r])
                hashtable[r] = NULL;
            free(cursor);
        }
    }
}
*/
/*
//  test out the check_word routine  (and technically load_dictionary)
    const char* correct_word = "Justice";
    const char* incorrect_word = "Caoimhín";
    int test1 = check_word(correct_word, hashtable);
    int test2 = check_word(incorrect_word, hashtable);
    printf("Test1 is %d, and Test2 is %d\n", test1, test2);
}
 */