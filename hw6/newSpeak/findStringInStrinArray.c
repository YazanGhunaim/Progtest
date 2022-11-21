#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{

    char arr[3][100] = {"apple", "orange", "programmer"};
    char input[100];

    printf("Input a word:\n");
    fgets(input, 100, stdin);
    // remove \n and make it null terminator
    input[strlen(input) - 1] = 0;

    int i;
    for (i = 0; i < strlen(input); i++)
    {
        input[i] = tolower(input[i]);
    }
    
    for (i = 0; i < 3; ++i)
    {
        // 0 if the same
        if (!strcmp(arr[i], input))
        {
            printf("found input string at index %d\n", i);
            break;
        }
    }
    //  if i is less than size of array.. we found the string else we didnt
    if (i >= 3)
    {
        printf("not found.\n");
    }
    
    return 0;
}
