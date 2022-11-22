#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *checkIfExists(const char *(*replace)[2],char *string)
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

    printf("%s\n", checkIfExists(d2, str4));
    printf("%s\n", checkIfExists(d2, str5));
    printf("%s\n", checkIfExists(d1, str6));
    printf("%s\n", checkIfExists(d1, str7));

    free(str4);
    free(str5);
    free(str6);
    free(str7);
    return 0;
}

