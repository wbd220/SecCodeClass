#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

bool check_word(const char* word, hashmap_t hashtable[]) {
    int word_len = strlen(word);
    if (word_len > LENGTH){
        //printf("Word to be checked too large, bye!");
        return 0;
    }

    //Set int bucket to the output of hash_function(word).
    int bucket = hash_function(word);
    //Set hashmap_t cursor equal to hashtable[bucket].
    hashmap_t cursor = hashtable[bucket];

        //    If word equals cursor->word:
        if (strcmp(word, cursor->word) == 0) {
            //        return True.
            return 1;
        }
        //    Else make lower_case(word) and check equals cursor->word:
        else {
            // set word to lower case
            char word_lower[LENGTH+1];
            for (int i=0; i <= strlen(word); i++) {
                word_lower[i] = tolower(word[i]);
            }
            // the word changed reset the index and run the linked list (if there)
            int bucket2 = hash_function(word_lower);
            hashmap_t cursor = hashtable[bucket2];
            while(cursor != NULL){  //check repeatedly through the linked list for the lower case word
                if (strcmp(word_lower, cursor->word) == 0) {
                    // return True.
                return 1;
                }
                // Set cursor to cursor->next.
                cursor = cursor->next;
            }
        }
    //}
    //        return False.
    return 0;
}


bool load_dictionary(const char* dictionary, hashmap_t hashtable[])
{
    //Initialize all values in hash table to NULL.
    int i;
    for(i = 0; i < HASH_SIZE; i++){
        hashtable[i] = NULL;
    }


    //Open dict_file from path stored in dictionary.
    //            If dict_file is NULL: return false.
    FILE * fp;
    char * word = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(dictionary, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    //While word in dict_file is not EOF (end of file):
    while ((read = getline(&word, &len, fp)) != -1) {
        // printf("%s", word);   // used this to assure reading file ok
        // check to see if word is larger than 45; if so just move to next word
        if (strlen(word)>(LENGTH+1))
        {continue;}
        else {
            //Set hashmap_t new_node to a new node.
            hashmap_t new_node = (struct node *) malloc(sizeof(node));  // should check that malloc worked, but didn't
            // Set new_node->next to NULL.
            new_node->next = NULL;
            // Set new_node->word equal to word.
            for (i = 0; word[i] != '\0'; i++) {
                new_node->word[i] = word[i];
            }
            //Makes sure that the string is NULL terminated; get rid of the \n
            new_node->word[i-1] = '\0';
            // Set int bucket to hash_function(word).
            int bucket = hash_function(new_node->word);
            // if hashtable[bucket] is NULL:
            if (hashtable[bucket] == NULL) {
                //Set hashtable[bucket] to new_node
                hashtable[bucket] = new_node;
            } else {
                //Set new_node->next to hashtable[bucket].
                new_node->next = hashtable[bucket];
                //Set hashtable[bucket] to new_node.
                hashtable[bucket] = new_node;
            }
        }
    }
    // Close dict_file.
    fclose(fp);
    return 1;
}

int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {
    // Set int num_misspelled to 0
    int num_misspelled = 0;
    //
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char* tempstr;

    // While line in fp is not EOF (end of file):
    // Read the line
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("%s", line);   // used this to assure reading file ok
        // Split the line on spaces.  Get one word out
        tempstr = strtok(line," \t\r\n");
            while (tempstr) {
                // remove the punctuation on front or back of word, check misspelled
                int g = 0;
                while (tempstr[g]) {
                    g++;
                }
                // check the length of the word to be sure it isn't too long
                if (g > LENGTH) {
                    //    printf("Word to be checked too large, bye!");  // tshooting
                    return 0;
                }
                // remove punctuation from front and back
                int punct1 = 0;
                if ((punct1 = ispunct(tempstr[g - 1])) !=
                    0) {  // if the end of the word is punctuation, replace with Null
                    tempstr[g - 1] = '\0';
                }
                int punct2 = 0;
                if ((punct2 = ispunct(tempstr[0])) != 0) { //if the start of the word is punctuation, remove it
                    //printf("start of word is punct %s\n", tempstr);  //tshooting
                    int t = 0;
                    while (tempstr[t]) {
                        tempstr[t] = tempstr[t + 1];
                        t++;
                    }
                }
                //printf("tempstr after start of word is punct: %s \n", tempstr);  //tshooting
                // tempstr should be a conditioned 'word'; check tempstr for length, ensure a null, then test it

                tempstr[g] = '\0';  //enforce NULL at tempstr[LENGTH]

                int k = check_word(tempstr, hashtable);
                if (k != 1) {
                    // printf("bad: %s\n", tempstr);  //tshooting
                    misspelled[num_misspelled] = malloc(LENGTH + 1);
                    strcpy(misspelled[num_misspelled], tempstr);
                    num_misspelled++;
                }
                tempstr = strtok(NULL, " \t\r\n");
            }
    }
    //printf("somewhere to do break point and look at what is in misspelled; %d \n", eo_mispelled);
    return num_misspelled;
 }