#include <stdio.h>
#include <stdlib.h>

#define INVALID "Invalid input.\n"

typedef struct domino
{
    int sides[5];
    int numOfSides;
    int visited;
} DOMINO;

int readInput(DOMINO **array, int initialSize, int *finalSize)
{
    int total = 0;
    int numSides = 0;
    int index = 0;
    char line[25];
    int matched = 0;
    DOMINO read;
    while (fgets(line, 25, stdin))
    {
        if (sscanf(line, "[ %d,%d,%d,%d,%d ]%n", &read.sides[0], &read.sides[1], &read.sides[2], &read.sides[3], &read.sides[4], &matched) == 5)
        {
            numSides = 5;
        }
        else if (sscanf(line, "[%d,%d,%d,%d]%n", &read.sides[0], &read.sides[1], &read.sides[2], &read.sides[3], &matched) == 4)
        {
            numSides = 4;
        }
        else if (sscanf(line, "[%d,%d,%d]%n", &read.sides[0], &read.sides[1], &read.sides[2], &matched) == 3)
        {
            numSides = 3;
        }
        else
        {
            break;
        }
        if (total >= initialSize)
        {
            initialSize = initialSize * 2 + 1;
            *array = (DOMINO *)realloc(*array, initialSize * sizeof(**array));
        }
        total++;
        read.numOfSides = numSides;
        read.visited = 0;
        (*array)[index++] = read;
    }
    if (!feof(stdin))
    {
        return 0;
    }
    *finalSize = total;
    return 1;
}

void reverse(int array[5], int from, int to)
{
    while (from < to)
    {
        int temp = array[from];
        array[from] = array[to];
        array[to] = temp;
        from++;
        to--;
    }
}

int equalArray(int *one, int *two, int length)
{
    for (int i = 0; i < length; ++i)
    {
        if (one[i] != two[i])
            return 0;
    }
    return 1;
}

int rotateArray(int main[5], int array[5], int length, int k)
{
    int temp[5];
    for (int i = 0; i < length; ++i)
    {
        temp[i] = array[i];
    }
    k = k % length;
    reverse(temp, 0, length - 1);
    reverse(temp, 0, k - 1);
    reverse(temp, k, length - 1);

    if (equalArray(main, temp, length))
        return 1;
    return 0;
}

void numberOfUniques(DOMINO *array, int finalSize)
{
    int unique = finalSize;
    for (int i = 0; i < finalSize; ++i)
    {
        for (int j = i + 1; j < finalSize; ++j)
        {
            if (array[i].numOfSides == array[j].numOfSides && !array[j].visited)
            {
                array[j].visited = 1;
                for (int l = 0; l < array[i].numOfSides; ++l)
                {
                    if (rotateArray(array[i].sides, array[j].sides, array[i].numOfSides, l))
                    {
                        unique--;
                        break;
                    }
                }
            }
        }
    }
    printf("Unique: %d\n", unique);
}

void print(DOMINO *array, int length)
{
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < array[i].numOfSides; ++j)
        {
            printf("%d ", array[i].sides[j]);
        }
        printf("\n");
    }
}

int main()
{
    int initialSize = 3;
    int finalSize = 0;
    DOMINO *array;
    array = (DOMINO *)malloc(sizeof(*array) * initialSize);
    printf("Dominos:\n");
    if (!readInput(&array, initialSize, &finalSize))
    {
        free(array);
        printf(INVALID);
        return 1;
    }
    numberOfUniques(array, finalSize);
    return 0;
}
