#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();
    bool newword = true;
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if (name[i] == ' ')
        {
            newword = true;
        }
        else if (newword)
        {
            printf("%c", toupper(name[i]));           
            newword = false;
        }
    }
    printf("\n");
}
