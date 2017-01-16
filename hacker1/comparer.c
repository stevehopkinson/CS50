#include <cs50.h>
#include <stdio.h>

int main (void) 
{
    printf("Give me an integer please: ");
    int x = GetInt();
    printf("Give me a second integer please: ");
    int y = GetInt();
    
    if (x > y) {
        printf("%i is %i bigger than %i!\n", x, x-y, y);
    }
    else if (y > x) {
        printf("%i is %i bigger than %i!\n", y, y-x, x);
    }
    else {
        printf("Hey, those are the same number! What gives?\n");
    }
}
