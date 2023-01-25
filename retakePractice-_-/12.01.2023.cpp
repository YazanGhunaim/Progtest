#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "Invalid Input.\n"

typedef struct student
{
    char *name[3];
    char *sortedName[3];
    int nameLength;
    int visited;
} STUDENT;

typedef struct all
{
    STUDENT *pre;
    int preLen;
    STUDENT *reg;
    int regLen;
} ALL;

int cmpSort(const char **a, const char **b)
{
    return strcasecmp(*a, *b);
}

int readInput(ALL *x)
{
    int first = 0;
    int total = 0;
    int number = 0;
    int initialPRE = 3;
    int initialREG = 3;
    char line[255];
    char mode;
    while (fgets(line, 255, stdin))
    {
        if (line[0] != 'R' && line[0] != 'P')
        {
            return 0;
        }
        if (line[0] == 'R')
        {
            first = 1;
            if (x->regLen == initialREG)
            {
                initialREG = initialREG * 2 + 1;
                x->reg = (STUDENT *)realloc(x->reg, initialREG * sizeof(STUDENT));
            }
            for (int i = 0; i < 3; ++i)
            {
                x->reg[x->regLen].name[i] = (char *)malloc(50 * sizeof(char));
                x->reg[x->regLen].sortedName[i] = (char *)malloc(50 * sizeof(char));
            }
            number = sscanf(line, "%c: %s %s %s", &mode, x->reg[x->regLen].name[0], x->reg[x->regLen].name[1], x->reg[x->regLen].name[2]);
            x->reg[x->regLen].nameLength = number - 1;
            x->reg[x->regLen].visited = 0;
            memcpy(x->reg[x->regLen].sortedName, x->reg[x->regLen].name, x->reg[x->regLen].nameLength * sizeof(x->reg[x->regLen].name[0]));
            qsort(x->reg[x->regLen].sortedName, x->reg[x->regLen].nameLength, sizeof(x->reg[x->regLen].name[0]), (int (*)(const void *, const void *))cmpSort);
            (x->regLen)++;
        }
        if (line[0] == 'P')
        {
            if (first == 0)
                return 0;
            if (x->preLen == initialPRE)
            {
                initialPRE = initialPRE * 2 + 1;
                x->pre = (STUDENT *)realloc(x->pre, initialPRE * sizeof(STUDENT));
            }
            for (int i = 0; i < 3; ++i)
            {
                x->pre[x->preLen].name[i] = (char *)malloc(50 * sizeof(char));
            }
            number = sscanf(line, "%c: %s %s %s", &mode, x->pre[x->preLen].name[0], x->pre[x->preLen].name[1], x->pre[x->preLen].name[2]);
            x->pre[x->preLen].nameLength = number - 1;
            x->pre[x->preLen].visited = 0;
            memcpy(x->pre[x->preLen].sortedName, x->pre[x->preLen].name, x->pre[x->preLen].nameLength * sizeof(x->pre[x->preLen].name[0]));
            qsort(x->pre[x->preLen].sortedName, x->pre[x->preLen].nameLength, sizeof(x->pre[x->preLen].name[0]), (int (*)(const void *, const void *))cmpSort);
            (x->preLen)++;
        }
        total++;
    }
    if (!feof(stdin) || !total || mode != 'P')
    {
        return 0;
    }
    return 1;
}

int sameName(STUDENT *a, STUDENT *b)
{
    if (a->nameLength != b->nameLength)
        return 0;
    for (int i = 0; i < a->nameLength; ++i)
    {
        if (strcasecmp(a->sortedName[i], b->sortedName[i]) != 0)
            return 0;
    }
    return 1;
}

void printName(STUDENT *a)
{
    for (int i = 0; i < a->nameLength; ++i)
    {
        printf("%s ", a->name[i]);
    }
}

void notPresent(ALL *x)
{
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

int main()
{
    ALL x;
    x.pre = (STUDENT *)malloc(3 * sizeof(STUDENT));
    x.preLen = 0;
    x.reg = (STUDENT *)malloc(3 * sizeof(STUDENT));
    x.regLen = 0;

    printf("Students:\n");
    if (!readInput(&x))
    {
        free(x.pre);
        free(x.reg);
        printf(INVALID);
        return 1;
    }

    printf("\nAbsent:\n");
    notPresent(&x);
    printf("Without registration:\n");
    withoutRegistration(&x);

    int i, j;
    for (i = 0; i < x.preLen; ++i)
    {
        for (j = 0; j < x.pre[i].nameLength; ++j)
        {
            free(x.pre[i].name[j]);
        }
    }
    free(x.pre);
    for (i = 0; i < x.regLen; ++i)
    {
        for (j = 0; j < x.reg[i].nameLength; ++j)
        {
            free(x.reg[i].name[j]);
        }
    }
    free(x.reg);

    return 0;
}
