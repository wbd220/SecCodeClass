// #include <check.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>


// Hash table is an array of linked lists.
node* hashtable[HASH_SIZE];

int hash_function(const char* word);

// Maps a word to an integer value to place it in the hash table.
// Sum the value of each character in the word, then find the
// remainder after dividing by the size of the hash table.
int hash_function(const char* word)
{
    int sum = 0;
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++)
    {
        sum += word[i];
    }

    int bucket = sum % HASH_SIZE;
    return bucket;
}

// function to load the list of words into the hash map
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]){
    // open dictionary file (wordlist.txt expected) for read
    // dictionary_file is the variable with filename to open

    FILE* inp;
    inp = fopen(dictionary_file,"r");		// open dictionary file
    char arr[5000][50];			//max 5000 words, max word length 50
    int i = 0;
    while(1){
        char r = (char)fgetc(inp);
        int k = 0;
        while(r!=' ' && !feof(inp)){	//read till ' ' or EOF
            arr[i][k++] = r;			//store in array
            r = (char)fgetc(inp);
        }
        arr[i][k]=0;		    //make last character of string null
        hashtable[i] == arr[i]; //completed word, so move from arr to your hashtable[]
        if(feof(inp)){		    //check again for EOF
            break;
        }
        i++;
    }
    return 0;
}

// function to check if a word is correctly spelled
bool check_word(const char* word, hashmap_t hashtable[]){
    // check the word passed to this function against the hashtable
    //but have to figure out how to do that
    // thinking I need to collect the code from
    // https://web.archive.org/web/20160329102146/http://elliottback.com/wp/hashmap-implementation-in-c/
}

// function called check_words to tie them all together.
int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]) {
    bool load_dictionary("wordlist.txt", hashmap_t hashtable[]);
    if (1 == load_dictionary)
    {
        // go ahead and start parsing lines from text2test; checking each word along the way  (space or \n)
        // use check_word to look for the word in hashmap, if there, it is spelled correctly, otherwise, misspelled
        // keep track of misspellings by adding misspelled word to end of misspelling array
        // return the misspellings
        //redo the 'read file a char/word at a time' once you have the array  check against the hash table
        FILE* inp;
        inp = fopen(fp,"r");		// open dictionary file
        char arr[5000][50];			//max 5000 words, max word length 50
        int i = 0;
        while(1){
            char r = (char)fgetc(inp);
            int k = 0;
            while(r!=' ' && !feof(inp)){	//read till ' ' or EOF
                arr[i][k++] = r;			//store in array
                r = (char)fgetc(inp);
            }
            arr[i][k]=0;		    //make last character of string null
            bool check_word(char arr[i]); //completed word, so check against hashtable
            if (check_word == 0)
            {
                // want to add the word to an array to pass back, but realloc?
            }
            if(feof(inp)){		    //check again for EOF
                break;
            }
            i++;
        }
        return 0;
    }
}


int main(int argc, char **argv)
{
    if(argc!=3)/*3 because we need two file names, one for file to check, one for wordlist, plus the arg[0] itself */
    {
        printf("unexpected number of arguments\n");
        printf("Should have two file names, file to check, then wordlist.txt to check against\n");
        return -1;
    }
    // argv[1] is a filename to open
    FILE* fptext2test;
    fptext2test = fopen(argv[1], "r");

    /* fopen returns 0, the NULL pointer, on failure */
    if ( fptext2test == 0 )
    {
    printf( "Could not open file %s \n", argv[1] );
    }
    else
    {
    // Call the routine that checks all the words
    char misspelled[1000]; // max misspelled words is now 1000
    int check_words(FILE* fptext2test, hashmap_t hashtable[], char* misspelled[]);

    //check_words returns misspelled words, print the misspelled words
    int num = sizeof(misspelled) / sizeof(misspelled[0]);
    if ( num > 0)
        {
        printf("Misspelled words:\n");
        for(int i = 0; num > i; i++) {
        printf("%s\n", misspelled[i]);
            }
        }
    if ( num == 0 )
        {
        printf("no misspelled words");
        }
    fclose( fptext2test );
    }


}
