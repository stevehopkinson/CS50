#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    if (argc != 2) 
    {
        printf("Please enter one non-negative integer as an argument.\n");
        return 1;
    }
    int cypher = atoi(argv[1]) % 26;
    string userstring = GetString();
    for (int i = 0, n = strlen(userstring); i < n; i++)
    {
        if (userstring[i] >= 'A' && userstring[i] <= 'Z')
        {
            userstring[i] += cypher - 'A';
            userstring[i] %= 26;
            userstring[i] += 'A';
        }
        else if (userstring[i] >= 'a' && userstring[i] <= 'z')
        {
            userstring[i] += cypher - 'a';
            userstring[i] %= 26;
            userstring[i] += 'a';
        }
    }
    printf("%s\n", userstring);
    return 0;
}
