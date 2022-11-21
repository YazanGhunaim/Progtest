#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *checkIfExists(const char *(*replace)[2], char *string)
{
    size_t numOfRows = 0;
    // finding the number of rows using endpoint NULL;
    for(int i=0; *replace[i]; i++) {
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

    char str[] = "dosao";
    char str1[] = "hello fail";
    char str2[] = "student";
    char str3[] = "you are one hell of a student";

    printf("%s\n", checkIfExists(d2, str));
    printf("%s\n", checkIfExists(d2, str1));
    printf("%s\n", checkIfExists(d1, str2));
    printf("%s\n", checkIfExists(d1, str3));

    return 0;
}
