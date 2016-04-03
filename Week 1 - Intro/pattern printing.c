#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    int height;
    
    // make sure user enters a height between 0 and 23 
    do 
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height > 23 || height < 0);
    
    // make number of rows in the pyramid equal to entered height
    for(int row = 0 ; row < height ; row++)
    {
        // print spaces until number of spaces in the row equals (height - row - 1)
        for(int space = 0 ; space < (height - row - 1) ; space++)
        {
            printf(" ");
        }
        
        // then, print hashes until number of hashes in row equals (row + 2) 
        for(int hash = 0 ; hash < (row + 2) ; hash++)
        {
            printf("#");
        }
        
        // start printing on a new line 
        printf("\n");
    }
                
    return 0;
}