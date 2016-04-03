/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // ensure user has entered two or three command line arguments
    if (argc != 2 || argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // change second command line argument to an integer
    int n = atoi(argv[1]);

    // if there are 3 command line arguments, set the random number generator seed to the third argument 
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    
    // there must be 2 command line arguments, set the random number generator seed to NULL 
    // (NULL is the number of seconds that have gone by since 00:00:00 Jan 1 1970)
    else
    {
        srand48((long int) time(NULL));
    }

    /* print out the product of the random number generator and the LIMIT 
    constant until the value of the command line argumnt 2 is reached*/
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    return 0;
}