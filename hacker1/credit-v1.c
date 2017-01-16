#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int** NumberToArray(long long n, int** numarray)
{
    char str[32];
    sprintf(str, "%lld", n);
    for (int i = 0; i < strlen(str); i++)
    {
        numarray[i] = str[i] - '0';
    }
    return numarray;
}

int main(void)
{
    printf("Please enter a credit card number: ");
    long long cardnumber = GetLongLong();
    int* numarray[32];
    numarray = NumberToArray(cardnumber, numarray);
}
