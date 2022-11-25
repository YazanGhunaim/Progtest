#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[] = "Apples are good in fact very good for your health";
    char to_find[] = "good";

    // strstr tells us if a string is present in another string
    // it returns a pointer to the start of the found string in the original string
    // int this case "good" to the end of the string str

    // we can store this pointer!

    char *res = strstr(str, to_find);

    // if substring is NOT found res will be NULL...

    if (res)
    {
        printf("%s\n", res);
        // adress would be all zeros if not found
        printf("address of res: %p\n", res);
        printf("word has been found.\n");
    }
    else
    {
        printf("word has not been found.\n");
    }

    printf("word found in string str is at position: %ld\n", res - str);

    // to find the ocurrences of all words

    int lengthOfWordToBeFound = strlen(to_find);

    char *resTwo = strstr(res + lengthOfWordToBeFound, to_find);

    if (resTwo)
    {
        printf("the second occurence was found here: %s", resTwo);
    }

    return 0;
}
