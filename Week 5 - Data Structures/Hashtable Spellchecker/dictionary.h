/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 * THIS VERSION USES A HASHTABLE
 */
 

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45 
#define BUCKETS 5783
#endif

// *** GLOBAL VARIABLES ***
// creates a node to be used for each word in a hashtable (linked list element)
typedef struct node 
{
    char entry[LENGTH + 1];
    struct node* next;
}node;

// create an array of node pointers
node* hash_table[BUCKETS];
    
// variable for assigning new nodes
node* new_node;

// used to traverse the linked list
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

/**
 * Hash function from user deplipity at reddit 
 * http://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
 */
int hash_function(char* word);

