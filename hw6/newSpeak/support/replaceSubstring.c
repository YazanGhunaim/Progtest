#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *stringReplace(char *source, size_t sourceSize, char *substring, char *with);

int main()
{

    char str[100] = "The apples are delicious apples apples.";

    printf("%s\n", str);

    while (stringReplace(str, sizeof(str), "apples", "burgers"));

    // result:
    printf("%s\n", str);

    return 0;
}

char *stringReplace(char *source, size_t sourceSize, char *substring, char *with)
{
    char *substring_source = strstr(source, substring);
    if (substring_source == NULL)
    {
        return NULL;
    }

    if (sourceSize < strlen(source) + (strlen(with) - strlen(substring)) + 1)
    {
        printf("Buffer size is too small\n");
        return NULL;
    }

    memmove(
        substring_source + strlen(with),
        substring_source + strlen(substring),
        strlen(substring_source) - strlen(substring) + 1);

    memcpy(substring_source, with, strlen(with));
    return substring_source + strlen(with);
}
