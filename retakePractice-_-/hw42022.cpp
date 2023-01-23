#include <stdio.h>
#include <stdlib.h>

#define MAX 2000
#define INVALID "Invalid input.\n"

int readInput(int *array, int *length)
{
    int input = 0;
    int total = 0;
    int index = 0;
    while (scanf("%d", &input) == 1)
    {
        total++;
        if (total == MAX)
        {
            return 0;
        }
        array[index++] = input;
    }
    if (!feof(stdin) || total == 0)
    {
        return 0;
    }
    *length = total;
    return 1;
}

int rangeSum(int *array, int start, int finish)
{
    int sum = 0;
    for (int i = start; i <= finish; ++i)
    {
        sum += array[i];
    }
    return sum;
}

void fillArray(int *array, int *answer, int length, int answerLength)
{
    int sum = 0;
    int index = 0;
    for (int i = 0; i < length; ++i)
    {
        for (int j = i + 1; j < length && index < answerLength; ++j)
        {
            sum = rangeSum(array, i, j);
            answer[index++] = sum;
        }
    }
}

int cmp(const int *a, const int *b)
{
    return (*b < *a) - (*a < *b);
}

int countDuplicates(int *array, int length)
{
    int count = 0;
    for (int i = 0; i < length; ++i)
    {
        for (int j = i + 1; j < length; ++j)
        {
            if (array[i] == array[j])
                count++;
        }
    }
    return count;
}

int main()
{
    int array[MAX];
    int length = 0;
    printf("Input sequence:\n");
    if (!readInput(array, &length))
    {
        printf(INVALID);
        return 1;
    }

    int answerLength = (length * 0.5) * (length - 1);
    int *answer = (int *)malloc(sizeof(*answer) * answerLength);

    fillArray(array, answer, length, answerLength);
    qsort(answer, answerLength, sizeof(array[0]), (int (*)(const void *, const void *))cmp);
    int result = countDuplicates(answer, answerLength);
    printf("Total pairs: %d\n", result);
    return 0;
}
