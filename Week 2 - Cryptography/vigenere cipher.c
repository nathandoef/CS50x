#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, string argv[])
{
   // ensure there are 2 command line arguments 
   if (argc != 2)
   {
      printf("Usage: workspace/pset2/vigenere <keyword>\n");
      return 1;
   }
  
   // ensure second command line argument is alphabetical
   for (int i = 0, n = strlen(argv[1]) ; i < n ; i++)
   {
      if ( !isalpha(argv[1][i]) )
      {
         printf("Keyword must only contain letters A-Z and a-z\n");
         return 1;
      }
   }
   
   // get plain text from user
   printf("Please enter text to be encrypted:\n");
   string plain = GetString();

   // use second command line argument for the key 
   string key = (argv[1]);
  
   // change key to lowercase to make encryption easier
   for (int i = 0, n = strlen(key) ; i < n ; i++)
        key [i] = tolower(key[i]);
   
   // create an array to store encrypted text
   char encrypted[strlen(plain)];
   
   printf("Encrypting text...\n");
   
   // iterate through the plain text 
   // i tracks the total number of characters
   // j is used so the position of the key is incremented only if plain[i] is alphabetical
   // j = (j+1) % strlen(key) loops the key if plain text is longer than the key 
   for (int i = 0, j = 0, n = strlen(plain) ; i < n ; i++)
   {
      // encrypt lower case characters
      if (islower(plain[i]))
      {
         encrypted[i] = (((plain[i] - 97 + key[j] - 97)  % 26) + 97);
         j = (j + 1) % strlen(key);
         
      }
      
      // encrypt upper case characters
      else if (isupper(plain[i]))
      {
         encrypted [i] = (((plain[i] - 65 + key[j] - 97)  % 26) + 65);
         j = (j + 1) % strlen(key);
      }
      
      // if not aplhabetical, do not change character
      else 
         encrypted[i] = plain[i];
   }
   
   // print encrypted text
   printf("%s\n", encrypted);
      
   return 0;
   
}