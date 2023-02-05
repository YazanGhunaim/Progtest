#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INVALID "Invalid input.\n"

typedef struct person
{
    char **name;
    char **sorted;
    int nameLength;
} PERSON;

typedef struct all
{
    PERSON *reg;
    int regLen;
    PERSON *pre;
    int preLen;
} ALL;

int cmp(const char **a, const char **b)
{
    return strcasecmp(*a, *b);
}

int readInput(ALL *x)
{
    int initialSizeReg = 3;
    int initialSizePre = 3;
    const char *delimeter = " ";
    char *word;
    char buffer[1000];
    while (fgets(buffer, 1000, stdin))
    {
        if ((buffer[0] != 'R' && buffer[0] != 'P') || buffer[1] != ':')
        {
            return 0;
        }
        if (buffer[0] == 'R')
        {
            if (x->regLen == initialSizeReg)
            {
                initialSizeReg = initialSizeReg * 2 + 1;
                x->reg = (PERSON *)realloc(x->reg, initialSizeReg * sizeof(PERSON));
            }
            x->reg[x->regLen].nameLength = 0;
            int initialString = 3;
            x->reg[x->regLen].name = (char **)malloc(3 * sizeof(char *));
            x->reg[x->regLen].sorted = (char **)malloc(3 * sizeof(char *));
            for (word = strtok(buffer, delimeter); word; word = strtok(NULL, delimeter))
            {
                if (x->reg[x->regLen].nameLength == initialString)
                {
                    initialString = initialString * 2 + 1;
                    x->reg[x->regLen].name = (char **)realloc(x->reg[x->regLen].name, initialString * sizeof(char *));
                    x->reg[x->regLen].sorted = (char **)realloc(x->reg[x->regLen].sorted, initialString * sizeof(char *));
                }
                x->reg[x->regLen].name[x->reg[x->regLen].nameLength] = strdup(word);
                memcpy(x->reg[x->regLen].sorted, x->reg[x->regLen].name, x->reg[x->regLen].nameLength * sizeof(x->reg[x->regLen].name[0]));
                qsort(x->reg[x->regLen].sorted, x->reg[x->regLen].nameLength, sizeof(x->reg[x->regLen].sorted[0]), (int (*)(const void *, const void *))cmp);
                (x->reg[x->regLen].nameLength)++;
            }
            (x->regLen)++;
        }
        if (buffer[0] == 'P')
        {
            if (x->preLen == initialSizePre)
            {
                initialSizePre = initialSizePre * 2 + 1;
                x->pre = (PERSON *)realloc(x->pre, initialSizePre * sizeof(PERSON));
            }
            x->pre[x->preLen].nameLength = 0;
            int initialString = 3;
            x->pre[x->preLen].name = (char **)malloc(3 * sizeof(char *));
            x->pre[x->preLen].sorted = (char **)malloc(3 * sizeof(char *));
            for (word = strtok(buffer, delimeter); word; word = strtok(NULL, delimeter))
            {
                if (x->pre[x->preLen].nameLength == initialString)
                {
                    initialString = initialString * 2 + 1;
                    x->pre[x->preLen].name = (char **)realloc(x->pre[x->preLen].name, initialString * sizeof(char *));
                    x->pre[x->preLen].sorted = (char **)realloc(x->pre[x->preLen].sorted, initialString * sizeof(char *));
                }
                x->pre[x->preLen].name[x->pre[x->preLen].nameLength] = strdup(word);
                memcpy(x->pre[x->preLen].sorted, x->pre[x->preLen].name, x->pre[x->preLen].nameLength * sizeof(x->pre[x->preLen].name[0]));
                qsort(x->pre[x->preLen].sorted, x->pre[x->preLen].nameLength, sizeof(x->pre[x->preLen].sorted[0]), (int (*)(const void *, const void *))cmp);
                (x->pre[x->preLen].nameLength)++;
            }
            (x->preLen)++;
        }
    }
    if (!feof(stdin))
    {
        return 0;
    }
    return 1;
}

int main()
{
    ALL x;
    x.reg = (PERSON *)malloc(3 * sizeof(PERSON));
    x.pre = (PERSON *)malloc(3 * sizeof(PERSON));
    x.regLen = 0;
    x.preLen = 0;
    if (!readInput(&x))
    {
        printf(INVALID);
        // freeMemory(&x);
        return 1;
    }
    return 0;
}
