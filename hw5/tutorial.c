#include <stdlib.h>
#include <stdio.h>

void printArray(const int *array, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int *pushInArray1(int *array, size_t *pSize, size_t *pCapacity, int newItem)
{
    if (*pSize >= *pCapacity)
    {
        // increase capacity
        *pCapacity = 2*(*pCapacity) + 1;
        array = (int *)realloc(array, *pCapacity * sizeof(array[0]));
    }
    array[*pSize] = newItem;
    (*pSize)++;
    return array;
}
void pushInArray2(int **pArray, size_t *pSize, size_t *pCapacity, int newItem)
{
    if (*pSize >= *pCapacity)
    {
        // increase capacity
        *pCapacity = 2 * (*pCapacity) + 1;
        *pArray = (int *)realloc(*pArray, *pCapacity * sizeof((*pArray)[0]));
    }
    (*pArray)[*pSize] = newItem;
    (*pSize)++;
}

int intCmp(const int *pA, const int *pB)
{
    if (*pA < *pB)
        return -1;

    if (*pA == *pB)
        return 0;

    return 1;
}

int main()
{
    int *numbers = NULL;
    size_t numberCapacity = 0;
    size_t numberSize = 0;
    int integer;

    while (scanf("%d", &integer) == 1)
    {
        numbers = pushInArray1(numbers, &numberSize, &numberCapacity, integer);
    }

    // while (scanf("%d", &integer) == 1)
    // {
    //     pushInArray2(&numbers, &numberSize, &numberCapacity, integer);
    // }

    qsort(numbers, numberSize, sizeof numbers[0], (int (*)(const void *, const void *))intCmp);

    printArray(numbers, numberSize);

    free(numbers);
    return 0;
}
