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

int cmp(const char **a, const char **b)
{
    return strcasecmp(*a, *b);
}

int sameName(STUDENT *a, STUDENT *b)
{
    if (a->nameLength != b->nameLength)
    {
        return 0;
    }
    for (int i = 0; i < a->nameLength; ++i)
    {
        if (strcasecmp(a->sortedName[i], b->sortedName[i]) != 0)
            return 0;
    }
    return 1;
}

int readInput(ALL *x)
{
    int initialSizeReg = 3;
    int initialSizePre = 3;
    int number = 0;
    int first = 1;
    char mode;
    char buffer[256];
    printf("Students:\n");
    while (fgets(buffer, 256, stdin))
    {
        if ((buffer[0] != 'R' && buffer[0] != 'P') || (first == 1 && buffer[0] == 'P'))
        {
            return 0;
        }
        if (buffer[0] == 'R')
        {
            first = 0;
            if (x->regLen == initialSizeReg)
            {
                initialSizeReg = initialSizeReg * 2 + 1;
                x->reg = (STUDENT *)realloc(x->reg, initialSizeReg * sizeof(STUDENT));
            }
            for (int i = 0; i < 3; ++i)
            {
                x->reg[x->regLen].name[i] = (char *)malloc(33 * sizeof(char));
            }
            number = sscanf(buffer, "%c: %s %s %s", &mode, x->reg[x->regLen].name[0], x->reg[x->regLen].name[1], x->reg[x->regLen].name[2]);
            x->reg[x->regLen].nameLength = number - 1;
            x->reg[x->regLen].visited = 0;
            memcpy(x->reg[x->regLen].sortedName, x->reg[x->regLen].name, x->reg[x->regLen].nameLength * sizeof(x->reg[x->regLen].name[0]));
            qsort(x->reg[x->regLen].sortedName, x->reg[x->regLen].nameLength, sizeof(x->reg[x->regLen].sortedName[0]), (int (*)(const void *, const void *))cmp);
            (x->regLen)++;
        }
        if (buffer[0] == 'P')
        {
            if (x->preLen == initialSizePre)
            {
                initialSizePre = initialSizePre * 2 + 1;
                x->pre = (STUDENT *)realloc(x->pre, initialSizePre * sizeof(STUDENT));
            }
            for (int i = 0; i < 3; ++i)
            {
                x->pre[x->preLen].name[i] = (char *)malloc(33 * sizeof(char));
            }
            number = sscanf(buffer, "%c: %s %s %s", &mode, x->pre[x->preLen].name[0], x->pre[x->preLen].name[1], x->pre[x->preLen].name[2]);
            x->pre[x->preLen].nameLength = number - 1;
            x->pre[x->preLen].visited = 0;
            memcpy(x->pre[x->preLen].sortedName, x->pre[x->preLen].name, x->pre[x->preLen].nameLength * sizeof(x->pre[x->preLen].name[0]));
            qsort(x->pre[x->preLen].sortedName, x->pre[x->preLen].nameLength, sizeof(x->pre[x->preLen].sortedName[0]), (int (*)(const void *, const void *))cmp);
            (x->preLen)++;
        }
    }
    if (!feof(stdin) || x->regLen == 0 || mode == 'R')
    {
        return 0;
    }
    return 1;
}

void printName(STUDENT *a)
{
    for (int i = 0; i < a->nameLength - 1; ++i)
    {
        printf("%s ", a->name[i]);
    }
    printf("%s", a->name[a->nameLength - 1]);
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

int main()
{
    ALL x;
    x.pre = (STUDENT *)malloc(3 * sizeof(STUDENT));
    x.reg = (STUDENT *)malloc(3 * sizeof(STUDENT));
    x.preLen = x.regLen = 0;
    if (!readInput(&x))
    {
        printf(INVALID);
        free(x.pre);
        free(x.reg);
        return 1;
    }
    notPresent(&x);
    withoutRegistration(&x);
    return 0;
}
