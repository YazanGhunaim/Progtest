#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *checkIfExists(const char *(*replace)[2], char *string)
{
    size_t numOfRows = 0;
    // finding the number of rows using endpoint NULL;
    for (int i = 0; *replace[i]; i++)
    {
        numOfRows++;
    }
    // printf("%zu\n", numOfRows);
    char *res;
    for (size_t i = 0; i < numOfRows; ++i)
    {
        res = strstr(string, *replace[i]);
        if (res)
        {
            break;
        }
    }
    return res;
}

char *m(const char *s)
{
    char *c = (char *)malloc(strlen(s) + 1);
    strcpy(c, s);
    return c;
}


int startWith(const char *string, const char *start)
{
    int string_length = strlen(string);
    int start_length = strlen(start);

    if (start_length > string_length)
        return false;

    for (int i = 0; i < start_length; i++)
    {
        if (string[i] != start[i])
        {
            return 0;
        }
    }
    return 1;
}

int checkPrefix(const char *string, const char *(*replace)[2], size_t rows, size_t index)
{

    size_t lengthOfString = strlen(string);

    for (size_t i = 0; i < rows; i++)
    {
        if (i == index)
            continue;

        size_t lengthOfArrayString = strlen(*replace[i]);

        if (lengthOfString > lengthOfArrayString)
            continue;

        if (startWith((*replace[i]), string))
            return 0;
    }
    return 1;
}

int checkPrefixInArray(const char *(*replace)[2])
{

    size_t numOfRows = 0;
    // finding the number of rows using endpoint NULL;
    for (int i = 0; *replace[i]; i++)
    {
        numOfRows++;
    }

    for (size_t i = 0; i < numOfRows; ++i)
    {
        if (!checkPrefix(*replace[i], replace, numOfRows, i))
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    const char *d1[][2] =
        {
            {"murderer", "termination specialist"},
            {"failure", "non-traditional success"},
            {"specialist", "person with certified level of knowledge"},
            {"dumb", "cerebrally challenged"},
            {"teacher", "voluntary knowledge conveyor"},
            {"evil", "nicenest deprived"},
            {"incorrect answer", "alternative answer"},
            {"student", "client"},
            {NULL, NULL}};

    const char *d2[][2] =
        {
            {"fail", "suboptimal result"},
            {"failure", "non-traditional success"},
            {NULL, NULL}};

    const char *d3[][2] =
        {
            {"Roses are Red", "suboptimal result"},
            {"Violet", "non-traditional success"},
            {"Roses", "non-traditional success"},
            {NULL, NULL}};

    const char *str = "dosao";
    const char *str1 = "hello fail";
    const char *str2 = "student";
    const char *str3 = "you are one hell of a student";

    char *str4 = m(str);
    char *str5 = m(str1);
    char *str6 = m(str2);
    char *str7 = m(str3);

    printf("strings 1-4: \n");
    printf("%s\n", str4);
    printf("%s\n", str5);
    printf("%s\n", str6);
    printf("%s\n\n", str7);

    printf("%p\n", checkIfExists(d2, str4));
    printf("%s\n", checkIfExists(d2, str5));
    printf("%s\n", checkIfExists(d1, str6));
    printf("%s\n", checkIfExists(d1, str7));

    printf("\nIs d2 valid? \"should be yes\" \n");
    if (checkPrefixInArray(d1))
    {
        printf("Invalid array.\n");
    }
    else
    {
        printf("Valid array.\n");
    }

    printf("\nIs d2 valid? \"should be no\" \n");
    if (checkPrefixInArray(d2))
    {
        printf("Invalid array.\n");
    }
    else
    {
        printf("Valid array.\n");
    }

    printf("\nIs d3 valid? \"should be no\" \n");
    if (checkPrefixInArray(d3))
    {
        printf("Invalid array.\n");
    }
    else
    {
        printf("Valid array.\n");
    }

    free(str4);
    free(str5);
    free(str6);
    free(str7);
    return 0;
}
