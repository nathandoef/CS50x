/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * 
 * THIS VERSION USES TRIES*
 */
 
#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // make sure cursor is pointing at the root 
    cursor = root;
    
    // create a new character string that is the size of the maximum length 
    char* word_copy = calloc(1,(LENGTH + 1));
    
    // copy the const char* word into the the new string 
    strcpy(word_copy, word);

    // iterate through all the characters in the word 
    for (int i = 0, n = strlen(word_copy) ; i < n ; i++)
    {
        // used to pass in an integer index to cursor 
        int c = 0;
        
        // change apostrophe character to an alphabetical index of 26 
        if ( word_copy[i] == '\'')
        {
            c = 26;
        }
        
        // if not an apostrophe, c is assumed to be alphabetical 
        else
        {
            c = tolower(word_copy[i]) - 97;
        }
        
        // if the cursor is pointing to NULL, the word is not in the dictionary      
        if (cursor->letter[c] == NULL)
        {
            // free word_copy
            free(word_copy);
            return false;
        }

        // else the word could be in the trie, traverse to the next node
        else 
            cursor = cursor->letter[c];
    }
    
    /*after each character is iterated through, if the value of 
    the cursor at is_word is true, the word is in the dictionary*/
    if (cursor->is_word == true)
    {
        free(word_copy);
        return true;
    }
    
    // is_word must be false and the word is not in the dictionary
    free(word_copy);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // initialize global variables root and cursor 
    root = calloc(1, sizeof(node));
    
    cursor = root;
    
    // open the dictionary 
    FILE* memory = fopen(dictionary, "r");
    if (memory == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return 11;
    }
    
    // iterates through every character in the dictionary 
    for (int c = fgetc(memory) ; c != EOF ; c = fgetc(memory)) 
    {
       // change c from ascii apostrophe value to the last number in alpha index
        if ( c == '\'')
        {
            c = 26;     
        }
        
        // make sure the newline character is outside the alpha index (\n is 10 in ascii)
        else if ( c == '\n' )
        {
            c = 50;
        }
        
        // change c from ascii to an alphabetical index value, assumed c is lowercase
        else 
        {
            c -= 97;
        }
        
        // checks to see if c is a valid character 
        if ( c <= 26 && c >= 0 )
        {
            // if the letter[c] node pointer has not been referenced
            if ( cursor->letter[c] == NULL )
            {
                // create a new node 
                cursor->letter[c] = calloc(1, sizeof(node));
                
                // move cursor to created node 
                cursor = cursor->letter[c];
            }
            // if there is already a pointer created then point to next node 
            else if ( cursor->letter[c] != NULL )
            {
                cursor = cursor->letter[c];
            }
        }
        // if c is a newline character, the end of a word has been reached
        else if (c == 50)
        {
            // change is_word field to true
            cursor->is_word = true;
            
            // increase the word count
            word_count++;
            
            // point cursor back to the root
            cursor = root;
        }
    }   
    
    // the end of the file was reached, close the dictionary file 
    fclose(memory);
    
    // if the word count isn't zero the dictionary was loaded
    if (word_count != 0)
    {
        return true;
    }
    
    // if word_count is zero, the dictionary was not loaded
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
    // set cursor to the root of the trie
    cursor = root;
    
    // call the recursive destroy function to destroy all the node pointers
    destroy(cursor);
    
    // after all the node pointer have been destroyed, the dictionary is unloaded
    return true;
}
/*
*** This function is used to introduce a pointer into the unload function, it 
checks to see if all the letter[] pointers of a node are NULL and if they are, 
it deletes that node
*/
void destroy(node* cursor)
{
    // if the cursor is pointing to NULL, stop 
    if (cursor == NULL)
        return;
    
    // otherwise iterate over all node points in node ( letter[i] )
    for (int i = 0 ; i < 27 ; i++)
    {
        // recursively call destroy 
        destroy(cursor->letter[i]);     
    }
    
    // if all letter[i] are NULL pointers, then the node can be deleted
    free(cursor);

    // return to previous call stack or unload if its the last node
    return;
}