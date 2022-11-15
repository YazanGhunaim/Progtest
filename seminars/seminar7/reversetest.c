#include <stdio.h>

void reverse(int nums[], int start, int end)
{

    while (start < end)
    {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}

void rotateArray(int array[], int arrayLen, int rotateBy)
{

    if (rotateBy > 0)
    {
        reverse(array, 0, arrayLen - 1);
        reverse(array, 0, rotateBy - 1);
        reverse(array, rotateBy, arrayLen - 1);
    }
    else if (array < 0)
    {
        reverse(array, rotateArray, arrayLen - 1);
        reverse(array, 0, rotateBy - 1);
        reverse(array, 0, arrayLen - 1);
    }
}

int main()
{

    int array[] = {1, 2, 3, 4, 5};

   rotateArray ( array, 5, 1 );

    for (int i = 0; i < 5; i++)
    {
        printf("%d  ", array[i]);
    }

    return 0;
}