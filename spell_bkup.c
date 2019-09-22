#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

bool check_word(const char* word, hashmap_t hashtable[]) {
    //Set int bucket to the output of hash_function(word).
    int bucket = hash_function(word);
    //Set hashmap_t cursor equal to hashtable[bucket].
    hashmap_t cursor = hashtable[bucket];

    //While cursor is not NULL:
    while (cursor != NULL) {
        //    If word equals cursor->word:
        if (strcmp(word, cursor->word) == 0) {
            //        return True.
            return 1;
        }
        //    Else if lower_case(word) equals cursor->word:
        else {
            int i = 0;
            while (word[i]) {
                tolower(word[i]);
                i++;
            }
            // the word changed  might have to reset the index and run the linked list (if there)
            if (strcmp(word, cursor->word) == 0) {
                // return True.
                return 1;
            }
            // Set cursor to cursor->next.
            cursor = cursor->next;
        }
    }
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
        if (strlen(word)>45)
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
}

int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {
    // Set int num_misspelled to 0
    int num_misspelled = 0;
    //
    *misspelled = (char *) malloc(45000);
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char newString[100][46];
    int i,j,ctr;
    // While line in fp is not EOF (end of file):
    // Read the line
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("%s", line);   // used this to assure reading file ok
        // Split the line on spaces.
        j=0; ctr=0;
        for(i=0;i<=(strlen(line));i++)
        {
            // if space or NULL found, assign NULL into newString[ctr]
            if(line[i]==' '||line[i]=='\0'||line[i]=='\n')
            {
                newString[ctr][j]='\0';
                ctr++;  //for next word
                j=0;    //for next word, init index to 0
            }
            else
            {
                newString[ctr][j]=line[i];
                j++;
            }
        }
        // got the line split; have to remove the punctuation on front or back of word, remove number, check misspelled
        int q = 0;
        char* tempstr;
        while(newString[q][0]){
            // move newstring(q) char by char (the sub r) to tempstr
               tempstr = &newString[q][0];
            // printf("tempstr before we clip it - %s\n", tempstr); //tshooting
            int eow = 0;
            int g = 0;
            while(tempstr[g]){ // make g length of word because sizeof isn't working
                eow++;
                g++;
            }
            int punct1 = 0;
            if ((punct1 = ispunct(tempstr[g-1])) > 0){  // if the end of the word is punctuation, replace with Null
                tempstr[g-1] = '\0';
            }
            int punct2 = 0;
            if ((punct2 = ispunct(tempstr[0])) > 0){ //if the start of the word is punctuation, remove it
                //printf("start of word is punct %s\n", tempstr);  //tshooting
                int t=0;
                while(tempstr[t]){
                    tempstr[t] = tempstr[t+1];
                    t++;
                }
                //printf("tempstr after start of word is punct: %s \n", tempstr);  //tshooting
            }
            // tempstr should be a conditioned 'word'; check tempstr
            int k = check_word(tempstr, hashtable);
            if(k != 1){
                num_misspelled++;
                //printf("bad: %s\n", tempstr);
                strcat(*misspelled, tempstr);
            }
            q++;
        }
    }
    //printf("somewhere to do break point and look at what is in misspelled; %d \n", eo_mispelled);
    return num_misspelled;
 }
/*
    While line in fp is not EOF (end of file):
        Read the line.
        Split the line on spaces.
        For each word in line:
            Remove punctuation from beginning and end of word.
            check is number  passes if it is, otherwise --
            If not check_word(word):
                Append word to misspelled.
                Increment num_misspelled.
    Return num_misspelled. */