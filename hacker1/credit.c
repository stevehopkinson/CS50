#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Number: ");
    long long cardnumber = GetLongLong();
    char str[32];
    sprintf(str, "%lld", cardnumber);
    int numlength = strlen(str);
    int numarray[numlength];
    for (int i = 0; i < numlength; i++)
    {
        numarray[i] = str[i] - '0';       
    }
    
    int checksum = 0;
    
    for (int i = 1; i <= numlength; i++)
    {
        if (i % 2 == 1)
        {
            checksum += numarray[numlength-i];
        }
        else
        {
            int x = numarray[numlength-i] * 2;
            if (x < 10)
            {
                checksum += x;
            }
            else
            {
                checksum += (1 + x % 10);
            }
        }
    }
    
    bool checksumvalid;
    if (checksum % 10 == 0)
    {
        checksumvalid = true;
    }
    else {
        checksumvalid = false;
    }
    
    if (checksumvalid && numlength == 15 && numarray[0] == 3 && (numarray[1] == 4 || numarray[1] == 7))
    {
        printf("AMEX\n");
    }
    else if (checksumvalid && numlength == 16 && numarray[0] == 5 && numarray[1] >= 1 && numarray[1] <= 5)
    {
        printf("MASTERCARD\n");
    }
    else if (checksumvalid && (numlength == 13 || numlength == 16) && numarray[0] == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}
    
