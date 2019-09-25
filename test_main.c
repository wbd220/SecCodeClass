#include <check.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define DICTIONARY "wordlist.txt"
#define MAX_MISSPELLED 0
#define TESTDICT "test_wordlist.txt"

/*
START_TEST(test_dictionary_normal)
    {
        hashmap_t hashtable[HASH_SIZE];
        ck_assert(load_dictionary(TESTDICT, hashtable));
        // Here we can test if certain words ended up in certain buckets
        // to ensure that our load_dictionary works as intended. I leave
        // this as an exercise.
    }
END_TEST
*/

START_TEST(test_check_word_w_double_spaces)  // check to see if spaces in the word confuse check word
    {
        hashmap_t hashtable[HASH_SIZE];
        load_dictionary(DICTIONARY, hashtable);
        const char* incorrect_word = "Just  ice";
        ck_assert(!check_word(incorrect_word, hashtable));
    }
END_TEST

START_TEST(test_check_word_with_punct_in_middle)
    {
        hashmap_t hashtable[HASH_SIZE];
        load_dictionary(DICTIONARY, hashtable);
        const char* correct_word = "Justice";
        const char* punctuation_word_2 = "pl.ace";
        ck_assert(check_word(correct_word, hashtable));
        ck_assert(!check_word(punctuation_word_2, hashtable));
        // Test here: What if a word begins and ends with "?
    }
END_TEST

START_TEST(test_check_words_normal)
    {
        hashmap_t hashtable[HASH_SIZE];
        load_dictionary(DICTIONARY, hashtable);
        char* expected[3];
        expected[0] = "sogn";
        expected[1] = "sogn";
        expected[2] = "skyn";
        expected[3] = "betta";
        char *misspelled[MAX_MISSPELLED];
        FILE *fp = fopen("test1.txt", "r");
        int num_misspelled = check_words(fp, hashtable, misspelled);
        ck_assert(num_misspelled == 3);
        bool test = strlen(misspelled[0]) == strlen(expected[0]);
        int len1 = strlen(misspelled[0]);
        int len2 = strlen(expected[0]);
        ck_assert_msg(test, "%d!=%d", len1, len2);
        ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0, "got %s, wanted %s", misspelled[0], expected[0]);
        ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0, "got %s, wanted %s", misspelled[0], expected[1]);
        ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0, "got %s, wanted %s", misspelled[0], expected[2]);
    }
END_TEST

START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* incorrect_word = "Caoimhín";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST

START_TEST(test_check_word_buffer_overflow)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char incorrect_word[500000];
    for(int i = 0; i < 499999; i++)
        incorrect_word[i] = 'A';
    incorrect_word[499999] = 0;
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_check_word_w_double_spaces);
    tcase_add_test(check_word_case, test_check_word_with_punct_in_middle);
    tcase_add_test(check_word_case, test_check_words_normal);
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_word_buffer_overflow);
    suite_add_tcase(suite, check_word_case);
    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
