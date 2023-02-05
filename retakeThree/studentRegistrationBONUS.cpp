#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "Invalid input.\n"

typedef struct person
{
    char **name;
    char **sorted;
    int nameLength;
    int visited;
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

int sameName(PERSON *a, PERSON *b)
{
    if (a->nameLength != b->nameLength)
    {
        return 0;
    }
    for (int i = 0; i < a->nameLength; ++i)
    {
        if (strcasecmp(a->sorted[i], b->sorted[i]) != 0)
            return 0;
    }
    return 1;
}

void printName(PERSON *a)
{
    for (int i = 0; i < a->nameLength - 1; ++i)
    {
        printf("%s ", a->name[i]);
    }
    printf("%s", a->name[a->nameLength - 1]);
}

int readInput(ALL *x)
{
    int initialSizeReg = 3;
    int initialSizePre = 3;
    const char *delimeter = " ";
    char mode;
    char colon;
    char *word;
    char buffer[1000];
    printf("Students:\n");
    while (scanf("\n%c%c ", &mode, &colon) == 2 && colon == ':')
    {
        if ((mode != 'R' && mode != 'P'))
        {
            return 0;
        }
        if (mode == 'R')
        {
            if (!fgets(buffer, 1000, stdin))
            {
                return 0;
            }
            buffer[strcspn(buffer, "\n")] = 0;
            if (x->regLen == initialSizeReg)
            {
                initialSizeReg = initialSizeReg * 2 + 1;
                x->reg = (PERSON *)realloc(x->reg, initialSizeReg * sizeof(PERSON));
            }
            x->reg[x->regLen].nameLength = 0;
            x->reg[x->regLen].visited = 0;
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
                (x->reg[x->regLen].nameLength)++;
            }
            memcpy(x->reg[x->regLen].sorted, x->reg[x->regLen].name, x->reg[x->regLen].nameLength * sizeof(x->reg[x->regLen].name[0]));
            qsort(x->reg[x->regLen].sorted, x->reg[x->regLen].nameLength, sizeof(x->reg[x->regLen].sorted[0]), (int (*)(const void *, const void *))cmp);
            (x->regLen)++;
        }
        if (mode == 'P')
        {
            if (!fgets(buffer, 1000, stdin))
            {
                return 0;
            }
            buffer[strcspn(buffer, "\n")] = 0;
            if (x->preLen == initialSizePre)
            {
                initialSizePre = initialSizePre * 2 + 1;
                x->pre = (PERSON *)realloc(x->pre, initialSizePre * sizeof(PERSON));
            }
            x->pre[x->preLen].nameLength = 0;
            x->pre[x->preLen].visited = 0;
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
                (x->pre[x->preLen].nameLength)++;
            }
            memcpy(x->pre[x->preLen].sorted, x->pre[x->preLen].name, x->pre[x->preLen].nameLength * sizeof(x->pre[x->preLen].name[0]));
            qsort(x->pre[x->preLen].sorted, x->pre[x->preLen].nameLength, sizeof(x->pre[x->preLen].sorted[0]), (int (*)(const void *, const void *))cmp);
            (x->preLen)++;
        }
    }
    if (!feof(stdin) || mode == 'R')
    {
        return 0;
    }
    return 1;
}

void notPresent(ALL *x)
{
    printf("Not Present:\n");
    for (int i = 0; i < x->regLen; ++i)
    {
        int found = 0;
        for (int j = 0; j < x->preLen; ++j)
        {
            if (sameName(&x->reg[i], &x->pre[j]) && x->pre[j].visited == 0)
            {
                x->pre[j].visited = 1;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("* ");
            printName(&x->reg[i]);
            printf("\n");
        }
    }
}

void withoutRegistration(ALL *x)
{
    printf("Without Registration:\n");
    for (int i = 0; i < x->preLen; ++i)
    {
        int found = 0;
        for (int j = 0; j < x->regLen; ++j)
        {
            if (sameName(&x->pre[i], &x->reg[j]) && x->reg[j].visited == 0)
            {
                x->reg[j].visited = 1;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("* ");
            printName(&x->pre[i]);
            printf("\n");
        }
    }
}

void freeMemory(ALL *x)
{
    for (int i = 0; i < x->regLen; ++i)
    {
        for (int j = 0; j < x->reg[i].nameLength; ++j)
        {
            free(x->reg[i].name[j]);
        }
        free(x->reg[i].name);
        free(x->reg[i].sorted);
    }
    free(x->reg);
    for (int i = 0; i < x->preLen; ++i)
    {
        for (int j = 0; j < x->pre[i].nameLength; ++j)
        {
            free(x->pre[i].name[j]);
        }
        free(x->pre[i].name);
        free(x->pre[i].sorted);
    }
    free(x->pre);
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
        freeMemory(&x);
        return 1;
    }
    notPresent(&x);
    withoutRegistration(&x);
    freeMemory(&x);
    return 0;
}
