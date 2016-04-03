/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */
 
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>
#endif

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// *** GLOBAL VARIABLES ***

/*create a struct that determines if the word ends and that contans an array of 
27 struct node pointers*/
typedef struct node 
{
    bool is_word;
    struct node* letter[27];
}node;
    
// pointer to root of tree
node* root;

// used to traverse the trie
node* cursor;
    
// used to count the number of words 
int word_count;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/*
*** This function is used to introduce a pointer into the unload function
*/
void destroy(node* cursor);