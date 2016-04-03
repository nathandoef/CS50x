#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // declare variable to store dollars  
    float dollars; 
    
    // make sure user enters a positive dollar value
    do  
    {
        printf("How much change is owed?\n");
        dollars = GetFloat();
    }
    while (dollars < 0);
    
    // change dollar value into cent value 
    int cents = round(dollars*100.0);
    
    // keep track of coins 
    int coin_count = 0;
    
    // repeat until the cent value is reduced to zero
    while (cents != 0)
    {
        // if cents is greater than or equal to 25 give customer quarter and subtract 25 cents
        if (cents >= 25)
        {
            coin_count += 1;
            cents -= 25;
        }
        
        // if cents is greater than or equal to 10 give customer dime and subtract 10 cents
        else if (cents >= 10)
        {
            coin_count += 1;
            cents -= 10;
        }
        
        // if cents is greater than or equal to 5 give customer a nickel and subtract 5 cents 
        else if  ( cents >= 5 )
        {
            coin_count += 1;
            cents -= 5;
        }
    
        // if cents is greater than or equal to 1 give customer a penny and subtract 1 cent
        else if (cents >= 1)
        {
            coin_count += 1;
            cents -= 1;
        }
    }

    printf("You should give the customer %d coins.\n", coin_count);
     
    return 0;
}

