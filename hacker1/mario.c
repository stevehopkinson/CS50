#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int height;

    do 
    {
        printf("Enter a non-negative integer < 24: ");
        height = GetInt();
    } while (height < 0 || height >= 24);

    for (int i = 1; i <= height; i++)
    {
        int width = height + i + 2;
        char row[width];
    
        for (int x = 0; x < width; x++)
        {
            if (x >= height - i || (x <= (height - i) + 2 && x >= height))
            {
                row[x] = '#';
            }
            else
            {
                row[x] = ' ';
            }   
        }

        row[height] = ' ';
        row[height + 1] = ' ';
        row[width] = '\0';

        printf("%s\n", row);
    } 
    return 0;
}
