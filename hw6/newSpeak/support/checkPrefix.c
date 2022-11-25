#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool startWith(char *string, char *start);

int main()
{

    char test[] = "Roses are red";

    char startOf[] = "Roses";

    char startOf1[] = "Rosess";

    if (startWith(test, startOf))
    {
        printf("prefix.\n");
    }
    else
    {
        printf("not a prefix.\n");
    }

     if (startWith(test, startOf1))
    {
        printf("prefix.\n");
    }
    else
    {
        printf("not a prefix.\n");
    }

    return 0;
}

bool startWith(char *string, char *start)
{
    int string_length = strlen(string);
    int start_length = strlen(start);

    if (start_length > string_length)
        return false;

    for (int i = 0; i < start_length; i++)
    {
        if (string[i] != start[i])
        {
            return false;
        }
    }
    return true;
}
