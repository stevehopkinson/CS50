#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    printf("O hai! How much change is owed? ");
    float dollars = GetFloat();
    while (dollars < 0)
    {
        printf("How much change is owed?\n");
        dollars = GetFloat();
    }
    
    int cents = dollars * 100 + 0.5;
    
    int quarters = cents / 25;
    
    int remainder = cents % 25;
    
    int dimes = remainder / 10;
    
    remainder = remainder % 10;
    
    int nickels = remainder / 5;
    
    remainder = remainder % 5;
    
    printf("%d\n", quarters + dimes + nickels + remainder);
    
    return 0;  
}
