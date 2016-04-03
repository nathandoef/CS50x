#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
   // make sure there are two command line arguments 
   if (argc != 2)
   {
      printf("Usage: workspace/pset2/caesar <key>\n");
      return 1;
   }
   
   // change command line argument 2 into an integer
   int key = atoi(argv[1]);
   
   // get plain text from user
   printf("Please enter text to be encrypted:\n");
   string plain = GetString();
 
   // create an array to store encrypted text
   char encrypted[strlen(plain)]; 
   
   printf("Encrypting text...\n");
   
   // iterate through plain text 
   for (int i = 0, n = strlen(plain) ; i < n ; i++)
   {
      // encrypt lower case characters
      if(islower(plain[i]))
         encrypted[i] = ((plain[i] - 97 + key) % 26) + 97;
      
      // encrypt upper case characters 
      else if(isupper(plain[i]))
         encrypted[i] = ((plain[i] - 65 + key) % 26) + 65;
      
      // if not alphabetical, do not change character 
      else 
         encrypted[i] = plain[i];
   }
   
   // print encrypted text
   printf("%s\n", encrypted);
   
   return 0;
}
