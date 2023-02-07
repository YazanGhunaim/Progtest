#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "Invalid input.\n"

typedef struct data
{
    int salary;
    char region[11];
} DATA;

typedef struct freq
{
    char *region;
    int salary;
    int count;
} FREQ;

typedef struct all
{
    DATA *data;
    int dataLen;
    FREQ *array;
    int arraySize;
} ALL;

int cmp(DATA *a, DATA *b)
{
    return ((*b).salary < (*a).salary) - ((*a).salary < (*b).salary);
}

void fillFreq(ALL *x)
{
    int initialSize = 3;
    for (int i = 0; i < x->dataLen; ++i)
    {
        int found = 0;
        for (int j = 0; j < x->arraySize; ++j)
        {
            if (x->array[j].salary == x->data[i].salary)
            {
                x->array[j].count++;
                found = 1;
            }
        }
        if (!found)
        {
            if (x->arraySize == initialSize)
            {
                initialSize = initialSize * 2 + 1;
                x->array = (FREQ *)realloc(x->array, initialSize * sizeof(FREQ));
            }
            x->array[x->arraySize].salary = x->data[i].salary;
            x->array[x->arraySize].count = 1;
            (x->arraySize)++;
        }
    }
}

void fillFreqSpecial(ALL *x, char request[11], int *total)
{
    int count = 0;
    int length = strlen(request);
    int initialSize = 3;
    for (int i = 0; i < x->dataLen; ++i)
    {
        int found = 0;
        for (int j = 0; j < x->arraySize; ++j)
        {
            if (strncmp(x->data[i].region, request, length) == 0 && x->array[j].salary == x->data[i].salary)
            {
                x->array[j].count++;
                found = 1;
            }
        }
        if (!found && strncmp(x->data[i].region, request, length) == 0)
        {
            count++;
            if (x->arraySize == initialSize)
            {
                initialSize = initialSize * 2 + 1;
                x->array = (FREQ *)realloc(x->array, initialSize * sizeof(FREQ));
            }
            x->array[x->arraySize].count = 1;
            x->array[x->arraySize].region = strdup(x->data[i].region);
            x->array[x->arraySize].salary = x->data[i].salary;
            (x->arraySize)++;
        }
    }
    *total = count;
}

void print(ALL *x)
{
    printf("Modus: ");
    int max = 0;
    for (int i = 1; i < x->arraySize; ++i)
    {
        if (x->array[i].count > x->array[max].count)
        {
            max = i;
        }
    }
    int numOfMax = 1;
    for (int j = 0; j < x->arraySize; ++j)
    {
        if (x->array[j].count == x->array[max].count)
        {
            numOfMax++;
        }
    }
    for (int l = 0; l < x->arraySize; ++l)
    {
        if (x->array[l].count == x->array[max].count)
        {
            numOfMax--;
            if (numOfMax > 1)
            {
                printf("%d, ", x->array[l].salary);
            }
            else
            {
                printf("%d ", x->array[l].salary);
            }
        }
    }
    printf("[%d]\n", x->array[max].count);
}
void query(ALL *x, char request[11])
{
    if (strcmp(request, "*") == 0)
    {
        x->array = (FREQ *)malloc(3 * sizeof(FREQ));
        x->arraySize = 0;
        fillFreq(x);
        //--//
        print(x);
        //--//
        free(x->array);
    }
    else
    {
        int count;
        x->array = (FREQ *)malloc(3 * sizeof(FREQ));
        x->arraySize = 0;
        fillFreqSpecial(x, request, &count);
        //--//
        if (count == 0)
        {
            printf("Modus: N/A\n");
        }
        else
        {
            print(x);
        }
        //--//
        for (int i = 0; i < x->arraySize; ++i)
        {
            free(x->array[i].region);
        }
        free(x->array);
    }
}

int readInput(ALL *x)
{
    int initialSize = 3;
    int first = 1;
    int end = 0;
    char buffer[100];
    char mode;
    DATA read;
    printf("Data:\n");
    while (fgets(buffer, 100, stdin))
    {
        if ((first && buffer[0] != '+') || (buffer[0] != '+' && buffer[0] != '?'))
        {
            return 0;
        }
        if (buffer[0] == '+')
        {
            first = 0;
            if (sscanf(buffer, "%c %s %d", &mode, read.region, &read.salary) != 3 || end)
            {
                return 0;
            }
            if (x->dataLen == initialSize)
            {
                initialSize = initialSize * 2 + 1;
                x->data = (DATA *)realloc(x->data, initialSize * sizeof(DATA));
            }
            x->data[x->dataLen] = read;
            (x->dataLen)++;
        }
        if (buffer[0] == '?')
        {
            char request[11];
            if (sscanf(buffer, "%c %s", &mode, request) != 2)
            {
                return 0;
            }
            end = 1;
            //--//
            qsort((void *)x->data, x->dataLen, sizeof(x->data[0]), (int (*)(const void *, const void *))cmp);
            query(x, request);
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
    x.data = (DATA *)malloc(3 * sizeof(DATA));
    x.dataLen = 0;
    if (!readInput(&x))
    {
        printf(INVALID);
        free(x.data);
        return 1;
    }
    free(x.data);
    return 0;
}
