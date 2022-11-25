#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceChar(char *string, char replace, char new);

int main()
{
    char s[] = "im going to pass this dreaded course!";
    replaceChar(s,'o','X');
    // check result
    printf("%s\n", s);

    return 0;
}

void replaceChar(char *string, char replace, char new)
{
    size_t sLen = strlen(string);

    for (size_t i = 0; i < sLen ; ++i)
    {
        if (string[i] == replace)
            string[i] = new;
    }
}


