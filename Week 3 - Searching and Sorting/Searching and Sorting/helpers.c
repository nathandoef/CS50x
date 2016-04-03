/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"

 /** 
  * Takes in a key to be found in an array of integers.
  * The function uses recursion and changes the min index or max index
  * of the array in each resursive call. 
  * binary_search is called by search
  */
bool binary_search(int key, int array[], int min, int max)
{
    if (min >= 0)
    {
        // make sure min is never greater than max
        if (max < min)
        {
            return false;
        }
    
        int midpoint = (min + max)/2; 
    
        /* if the key less than the midpoint, recursively call binary_search
        with a minimum index of the midpoint + 1 */
        if(array[midpoint] < key)
        {
            return binary_search(key, array, midpoint + 1, max);
        }
        
        /* else if the key greater than the midpoint, recursively call 
        binary_search with a maximum index of the midpoint - 1 */
        else if(array[midpoint] > key)
        {
            return binary_search(key, array, min, midpoint - 1);
        }
        
        // the key is in the array
        else if (array[midpoint] == key)
        {
            return true;
        }
    }
    
    // key is not in the array
    return false;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
   // return the value of the binary_search function
   // 0 is used for the min index value, the array size (n) is used for the max index value
   return binary_search(value, values, 0, n);
}

/**
 * Sorts array of n values.

 */ 
void sort(int values[], int n)
{
    int place_holder;
    
    // iterate through values up until the second last value
    for (int i = 0 ; i < (n - 1) ; i ++)
    {
        // compare each value i with the next value 
        for (int j = i + 1 ; j < n  ; j++)
        {
            // if the first value is greater the next value, switch them
            if (values[i] > values[j])
            {
                place_holder = values[i];
                values[i] = values[j];
                values[j] = place_holder;
            }
        }
    }
    
    return;
}












