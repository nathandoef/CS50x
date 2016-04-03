/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * 
 * THIS VERSION USES A HASHTABLE*
 */
 
#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // create a new character string that is the size of the maximum length 
    char* new_word = calloc(1, (LENGTH + 1));
    
    // copy the const char* word into the the new string 
    strcpy(new_word, word);
    
    /* change the new string to all lowercase to match the case of the dictionary 
    word and therefore, ensure the hashed values are the same */
    for (int i = 0, length = strlen(new_word) ; i < length ; i++)
    {
        if ( isalpha(new_word[i]) ) 
        {
            new_word[i] = tolower(new_word[i]);
        }
    }
        
    // determine the hash number of the word (after word is changed to lowercase)
    int n = hash_function(new_word);
    
    // if there is no entry in the hash table, the word is not in the dictionary
    if (hash_table[n] == NULL)
    {
        free(new_word);
        return false;
    }
    
    // else the word may be in the dictionary
    else 
    {
        // point the cursor to correct bucket of the hashtable
        cursor = hash_table[n];
        
        while (cursor != NULL)
        {
            // the entry field is equal to the word to be tested, it is in the dictionary
            if (strcmp(cursor->entry, new_word) == 0)
            {
                free(new_word);
                return true;
            }
            
            // if its not, move cursor and keep looking
            else 
                cursor = cursor->next;
        }
    }
    
    free(new_word);
    
    // if the cursor has reached NULL and word was not found, it is not in the dictionary
    return false;
}

bool load(const char* dictionary)
{
    // Open the dictionary file 
    FILE* memory = fopen(dictionary, "r");
    if (memory == NULL)
    {
        printf("could not open %s\n", dictionary);
        return 11;
    }

    //initialize the the array of pointers to NULL
    for (int i = 0 ; i < BUCKETS ; i++)
    {
        hash_table[i] = NULL;
    }
    
    // character array for each word to hold each dictinary word
    // LENGTH+2 because of fgets stops reading at a newline character
    char word[LENGTH+2];
    
    // iniitialize word_count
    word_count = 0;
    
    /* read each string from the dictionary file and store word buffer 
    until NULL (error or EOF) is reached */
    while ( fgets(word, LENGTH + 2 , memory) != NULL )
    {
        // counter for the number of characters until a newline
        int k = 0;
        while(word[k] != '\n')
        {
            k++;
        }
        
        // put a null terminator where the newline character was 
        word[k] = '\0';
        
        //create a new node for each word
        new_node = calloc(1, sizeof(node));
        
        // scan the word into the entry field of the node 
        sscanf(word, "%s", new_node->entry);
        
        // determine the words hashed value
        int n = hash_function(word);
        
        // If there is not already a linked list at the corresponding bucket
        if (hash_table[n] == NULL)
        {
            // insert the new node into the empty bucket of the hash table
            hash_table[n] = new_node;
        }
        
        // If there is already a linked list at the corresponding bucket
        else 
        {
            // connect the next portion of the new node to the existing node
            new_node->next = hash_table[n];
            
            // connect the hash_table pointer to the new node
            hash_table[n] = new_node;
        }
        // increment the word count
        word_count++;
    }
    
    // close the file
    fclose(memory);
    
    // if word count is not zero, the dictionary was loaded
    if (word_count != 0)
        return true;
    
    // else the word count is zero and nothing was loaded   
    else 
        return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // uses the global variable word_count to determine the size of the dictionary
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // iterate through all the buckets in the hash table
    for (int i = 0 ; i < BUCKETS ; i++)
    {
        if (hash_table[i] != NULL)      // if a bucket is pointing to a linked list 
        {
            cursor = hash_table[i];     // set cursor to head of linked list 
            
            while (cursor != NULL)      // iterate through linked list 
            {
                node* temp = cursor;    // point temp pointer to where cursor is pointng
                cursor = cursor->next;  // move the cursor to the next node
                free(temp);             // free where temp pointer is pointing
            }
        }
    }
    
return true;
}

/*
* Hash function from user deplipity at reddit 
* http://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
*/
int hash_function(char* word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word) ; i < n ; i++)
        hash = (hash << 2) ^ word[i];
    return hash % BUCKETS;
}