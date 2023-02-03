#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "Invalid input.\n"

typedef struct domino
{
    int digits[5];
    int digitLen;
    int visited;
} DOMINO;

typedef struct all
{
    DOMINO *dominos;
    int dominoLen;
} ALL;

int readInput(ALL *x)
{
    int initalSize = 3;
    int number = 0;
    DOMINO read;
    char buffer[256];
    while (fgets(buffer, 256, stdin))
    {
        number = sscanf(buffer, "[ %d, %d, %d, %d, %d ]", &read.digits[0], &read.digits[1], &read.digits[2], &read.digits[3], &read.digits[4]);
        if (number < 3 || number > 5)
            return 0;
        read.digitLen = number;
        if (x->dominoLen == initalSize)
        {
            initalSize = initalSize * 2 + 1;
            x->dominos = (DOMINO *)realloc(x->dominos, initalSize * sizeof(DOMINO));
        }
        read.visited = 0;
        x->dominos[x->dominoLen] = read;
        (x->dominoLen)++;
    }
    if (!feof(stdin))
    {
        return 0;
    }
    return 1;
}

void reverseArray(int *array, int start, int end)
{
    while (start < end)
    {
        int temp = array[start];
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    }
}

int equalArray(int *arrayOne, int *arrayTwo, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (arrayOne[i] != arrayTwo[i])
            return 0;
    }
    return 1;
}

int rotateArray(int *arrayOne, int *arrayTwo, int size, int k)
{
    k %= size;
    int temp[5];
    for (int i = 0; i < size; ++i)
    {
        temp[i] = arrayTwo[i];
    }
    reverseArray(temp, 0, size - 1);
    reverseArray(temp, 0, k - 1);
    reverseArray(temp, k, size - 1);

    if (equalArray(arrayOne, temp, size))
        return 1;
    return 0;
}

void unique(ALL *x)
{
    int unique = x->dominoLen;
    for (int i = 0; i < x->dominoLen; ++i)
    {
        for (int j = i + 1; j < x->dominoLen; ++j)
        {
            if (x->dominos[i].digitLen == x->dominos[j].digitLen && x->dominos[j].visited == 0)
            {
                x->dominos[j].visited = 1;
                for (int l = 0; l < x->dominos[i].digitLen; ++l)
                {
                    if (rotateArray(x->dominos[i].digits, x->dominos[j].digits, x->dominos[i].digitLen, l))
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
int main()
{
    ALL x;
    x.dominos = (DOMINO *)malloc(3 * sizeof(DOMINO));
    x.dominoLen = 0;
    if (!readInput(&x))
    {
        printf(INVALID);
        free(x.dominos);
        return 1;
    }
    unique(&x);
    free(x.dominos);
    return 0;
}
