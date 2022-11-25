#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int howManyTimes(char *str, const char *toSearch)
{
    int i, j, found, count;
    int stringLen, searchLen;

    stringLen = strlen(str);      // length of string
    searchLen = strlen(toSearch); // length of word to be searched

    count = 0;

    for (i = 0; i <= stringLen - searchLen; i++)
    {
        /* Match word with string */
        found = 1;
        for (j = 0; j < searchLen; j++)
        {
            if (str[i + j] != toSearch[j])
            {
                found = 0;
                break;
            }
        }

        if (found == 1)
        {
            count++;
        }
    }

    return count;
}
char *checkWhatExists(const char *(*replace)[2], char *string, int data[], size_t numOfRows, size_t *dataLength)
{
    size_t length = 0;
    char *res = string;
    for (size_t i = 0; i < numOfRows; ++i)
    {
        res = strstr(string, *replace[i]);
        if (res)
        {
            data[length] = i;
            length++;
        }
    }
    *dataLength = length;
    return res;
}

char *checkIfExists(const char *(*replace)[2], char *string, size_t numOfRows)
{
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
    char *c = (char *)malloc(100000 + 1);
    strcpy(c, s);
    return c;
}

int startWith(const char *string, const char *start)
{
    int string_length = strlen(string);
    int start_length = strlen(start);

    if (start_length > string_length)
        return 0;

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

int checkPrefixInArray(const char *(*replace)[2], size_t numOfRows)
{

    for (size_t i = 0; i < numOfRows; ++i)
    {
        if (!checkPrefix(*replace[i], replace, numOfRows, i))
        {
            return 1;
        }
    }
    return 0;
}

char *stringReplace(char *source, size_t sourceSize, const char *substring, const char *with, const char *(*replace)[2])
{
    char *substring_source = strstr(source, substring);
    if (substring_source == NULL)
    {
        return NULL;
    }

    // int initialIncrease = 10;
    // if (sourceSize < strlen(source) + (strlen(with) - strlen(substring)) + 1)
    // {
    //     initialIncrease = initialIncrease * 2 ;
    //     source = realloc(source,initialIncrease*sizeof(*source) + 1);
    // }
    memmove(
        substring_source + strlen(with),
        substring_source + strlen(substring),
        strlen(substring_source) - strlen(substring) + 1);

    memcpy(substring_source, with, strlen(with));
    return substring_source + strlen(with);
}

char *replaceInArray(const char *(*replace)[2], char *string, size_t numOfRows, int data[], size_t dataLength)
{
    for (size_t i = 0; i < dataLength; i++)
    {
        int numOfTimes = howManyTimes(string, *replace[data[i]]);
        while (numOfTimes)
        {
            stringReplace(string, sizeof(string), *replace[data[i]], replace[data[i]][1], replace);
            numOfTimes--;
        }
    }

    return string;
}

char *newSpeak(const char *text, const char *(*replace)[2])
{
    size_t numOfRows = 0;
    // finding the number of rows using endpoint NULL;
    for (int i = 0; *replace[i]; i++)
    {
        numOfRows++;
    }
    size_t initialDataSize = numOfRows;
    int *data = (int *)malloc(initialDataSize * sizeof(*data));
    char *res = m(text);
    size_t dataLength = 0;
    // printf("string: %s , size: %lu\n", res, strlen(res));

    if (checkPrefixInArray(replace, numOfRows))
    {
        free(res);
        free(data);
        return NULL;
    }

    if (checkIfExists(replace, res, numOfRows))
    {
        char *temp = res;

        for (size_t i = 0; i < numOfRows; i++)
        {
            if (checkWhatExists(replace, res, data, numOfRows, &dataLength))
            {
                temp = checkWhatExists(replace, temp, data, numOfRows, &dataLength);
            }
        }
        // for (size_t i = 0; i < dataLength; i++)
        // {
        //     printf("word in index: %d occured this many times: %d\n", data[i], howManyTimes(res, *replace[data[i]]));
        // }
        res = replaceInArray(replace, res, numOfRows, data, dataLength);
    }
    printf("%s\n", res);
    free(data);
    return res;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    char *res;

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

    res = newSpeak("Everybody is happy.", d1);
    assert(!strcmp(res, "Everybody is happy."));
    free(res);

    res = newSpeak("The student answered an incorrect answer.", d1);
    assert(!strcmp(res, "The client answered an alternative answer."));
    free(res);

    res = newSpeak("He was dumb, his failure was expected. dumb", d1);
    assert(!strcmp(res, "He was cerebrally challenged, his non-traditional success was expected. cerebrally challenged"));
    free(res);

    res = newSpeak("The evil teacher became a murderer.", d1);
    assert(!strcmp(res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist."));
    free(res);

    res = newSpeak("Devil's advocate.", d1);
    assert(!strcmp(res, "Dnicenest deprived's advocate."));
    free(res);

    res = newSpeak("Hello.", d2);
    assert(!res);

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
