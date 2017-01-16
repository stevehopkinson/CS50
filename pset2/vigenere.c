#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    if (argc != 2) 
    {
        printf("Please enter one alphabetical string as an argument.\n");
        return 1;
    }
    
    string keyphrase = argv[1];
    int keylength = strlen(keyphrase);
    
    for (int i = 0, n = strlen(keyphrase); i < n; i++) 
    {
        if (!isalpha(keyphrase[i])) 
        {
            printf("Please only enter alphabetical characters.\n");
            return 1;
        } else if (islower(keyphrase[i]))
        {
            keyphrase[i] -= 'a';
        } else 
        {
            keyphrase[i] -= 'A';
        }
    }
    
    string userstring = GetString();
    int counter = 0;
    
    for (int i = 0, n = strlen(userstring); i < n; i++) 
    {
        if (islower(userstring[i])) 
        {
            userstring[i] += keyphrase[counter] - 'a';
            userstring[i] %= 26;
            userstring[i] += 'a';
        } else if (isupper(userstring[i]))
        {
            userstring[i] += keyphrase[counter] - 'A';
            userstring[i] %= 26;
            userstring[i] += 'A';
        } else 
        {
            continue;
        }
        counter++;
        counter %= keylength;
    }
    printf("%s\n", userstring);
}
