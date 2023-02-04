#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "Invalid input.\n"

typedef struct car
{
    char rz[11];
    int floor;
    int parkingSpace;
} CAR;

typedef struct garage
{
    int floors;
    int spaces;
    CAR *carArray;
    int carLen;
} GARAGE;

int occupiedParkingPlace(GARAGE *x, int floor, int space, int *index)
{
    for (int i = 0; i < x->carLen; ++i)
    {
        if (x->carArray[i].floor == floor && x->carArray[i].parkingSpace == space)
        {
            *index = i;
            return 1;
        }
    }
    return 0;
}

int findRZ(GARAGE *x, char plate[11], int *index)
{
    for (int i = 0; i < x->carLen; ++i)
    {
        if (strcmp(x->carArray[i].rz, plate) == 0)
        {
            *index = i;
            return 1;
        }
    }
    return 0;
}

int readInput(GARAGE *x)
{
    printf("Size :\n");
    if (scanf("%d %d", &x->floors, &x->spaces) != 2)
        return 0;
    // ---------- //
    int initialSize = 3;
    char mode;
    printf("Requirements: \n");
    while (scanf("\n%c", &mode) == 1)
    {
        if (mode != '-' && mode != '+')
            return 0;
        if (mode == '+')
        {
            CAR read;
            int index = 0;
            if (scanf("%d %d %10s", &read.floor, &read.parkingSpace, read.rz) != 3 || read.floor >= x->floors || read.parkingSpace >= x->spaces)
            {
                return 0;
            }
            if (occupiedParkingPlace(x, read.floor, read.parkingSpace, &index))
            {
                printf("OCCUPIED %s\n", x->carArray[index].rz);
            }
            else
            {
                printf("OK\n");
                if (x->carLen == initialSize)
                {
                    initialSize = initialSize * 2 + 1;
                    x->carArray = (CAR *)realloc(x->carArray, initialSize * sizeof(CAR));
                }
                x->carArray[x->carLen] = read;
                (x->carLen)++;
            }
        }
        else
        {
            char toRemove[11];
            int index = 0;
            if (scanf("%s", toRemove) != 1)
                return 0;
            if (!findRZ(x, toRemove, &index))
            {
                printf("Not Found\n");
            }
            else
            {
                findRZ(x, toRemove, &index);
                for (int i = index; i < x->carLen; ++i)
                {
                    x->carArray[i] = x->carArray[i + 1];
                }
                printf("OK\n");
            }
        }
    }
    if (!feof(stdin) || x->carLen == 0)
    {
        return 0;
    }
    return 1;
}

int main()
{
    GARAGE x;
    x.carArray = (CAR *)malloc(3 * sizeof(CAR));
    x.carLen = 0;
    if (!readInput(&x))
    {
        free(x.carArray);
        printf(INVALID);
        return 1;
    }
    free(x.carArray);
    return 0;
}
