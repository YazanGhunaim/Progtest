#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "Invalid input.\n"
#define MAX_CHARACTER 50

typedef struct names
{
    char **names;
    int nameLenght;
} NAMES;

typedef struct sorted
{
    char *names;
    int visited;
} SORTED;

typedef struct all
{
    NAMES *book;
    int bookLen;
    SORTED *sorted;
    int totalLength;
} ALL;

typedef struct freq
{
    char *name;
    int freq;
} FREQ;

int cmp(SORTED *a, SORTED *b)
{
    return (strcmp(a->names, b->names));
}

int readInput(ALL *x, int *numOfWords)
{
    char *word;
    int initialSize = 3;
    int totalNumOfWords = 0;
    char buffer[MAX_CHARACTER * 256];
    const char *delimeter = " ";

    printf("Names:\n");
    while (fgets(buffer, MAX_CHARACTER * 256, stdin))
    {
        if (x->bookLen == initialSize)
        {
            initialSize = initialSize * 2 + 1;
            x->book = (NAMES *)realloc(x->book, initialSize * sizeof(NAMES));
            for (int i = x->bookLen; i < initialSize; ++i)
            {
                x->book[i].nameLenght = 0;
            }
        }
        int initialSizeString = 3;
        x->book[x->bookLen].names = (char **)malloc((3) * sizeof(char *));
        for (word = strtok(buffer, delimeter); word != NULL; word = strtok(NULL, delimeter))
        {

            if (x->book[x->bookLen].nameLenght == initialSizeString)
            {
                initialSizeString = initialSizeString * 2 + 1;
                x->book[x->bookLen].names = (char **)realloc(x->book[x->bookLen].names, initialSizeString * sizeof(char *));
            }
            x->book[x->bookLen].names[x->book[x->bookLen].nameLenght] = strdup(word);
            (x->book[x->bookLen].nameLenght)++;
            totalNumOfWords++;
        }
        (x->bookLen)++;
    }
    if (!feof(stdin) || totalNumOfWords == 0)
    {
        for (int i = 0; i < x->bookLen; ++i)
        {
            for (int j = 0; j < x->book[i].nameLenght; ++j)
            {
                free(x->book[i].names[j]);
            }
            free(x->book[i].names);
        }
        free(x->book);
        return 0;
    }
    *numOfWords = totalNumOfWords;
    return 1;
}

void fillNames(ALL *x, int *size)
{
    int index = 0;
    for (int i = 0; i < x->bookLen; ++i)
    {
        for (int j = 0; j < x->book[i].nameLenght - 1; ++j)
        {
            (x->sorted[index++].names) = strdup(x->book[i].names[j]);
        }
    }
    *size = index;
}

void initfreq(FREQ *array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i].freq = 1;
        array[i].name = NULL;
    }
}

void initSorted(ALL *x)
{
    for (int i = 0; i < x->totalLength; ++i)
    {
        x->sorted[i].visited = 0;
    }
}

int getMax(FREQ *array, int size)
{
    int max = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i].freq > max)
        {
            max = array[i].freq;
        }
    }
    return max;
}

void gatherNames(FREQ *array, int max, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (array[i].freq == max)
        {
            printf("%s\n", array[i].name);
        }
    }
}

void freeFreq(FREQ *freq, int size)
{
    for (int i = 0; i < size; ++i)
    {
        free(freq[i].name);
    }
    free(freq);
}

void frequency(ALL *x, int size)
{
    FREQ *freq = (FREQ *)malloc(size * sizeof(*freq));
    initfreq(freq, size);
    x->sorted = (SORTED *)malloc(size * sizeof(SORTED));
    fillNames(x, &x->totalLength);
    initSorted(x);
    qsort((void *)x->sorted, x->totalLength, sizeof(x->sorted[0]), (int (*)(const void *, const void *))cmp);

    int index = 0;
    for (int i = 0; i < x->totalLength; ++i)
    {
        freq[index].name = strdup(x->sorted[i].names);
        for (int j = i + 1; j < x->totalLength; ++j)
        {

            if (strcmp(x->sorted[i].names, x->sorted[j].names) == 0 && x->sorted[j].visited == 0)
            {
                x->sorted[j].visited = 1;
                (freq[index].freq)++;
            }
        }
        index++;
    }
    int max = getMax(freq, index);
    printf("Most occurences: %d x\n", max);
    gatherNames(freq, max, index);
    freeFreq(freq, size);
}

void freeMemory(ALL *x)
{
    for (int i = 0; i < x->bookLen; ++i)
    {
        for (int j = 0; j < x->book[i].nameLenght; ++j)
        {
            free(x->book[i].names[j]);
        }
        free(x->book[i].names);
    }
    for (int i = 0; i < x->totalLength; ++i)
    {
        free(x->sorted[i].names);
    }
    free(x->sorted);
    free(x->book);
}

int main()
{
    ALL x;
    x.book = (NAMES *)malloc(3 * sizeof(NAMES));
    x.bookLen = 0;
    int totalNumOfWords = 0;
    for (int i = 0; i < 3; ++i)
    {
        x.book[i].nameLenght = 0;
    }
    if (!readInput(&x, &totalNumOfWords))
    {
        printf(INVALID);
        return 1;
    }
    printf("\n");
    frequency(&x, totalNumOfWords);
    freeMemory(&x);
    return 0;
}
