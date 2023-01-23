#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "Invalid input.\n"

typedef struct parkedcar
{
    int floor;
    int position;
    char rz[11];
} PARKEDCAR;

typedef struct garage
{
    int floors;
    int positions;
    PARKEDCAR *occupied;
    int occupiedlen;
} GARAGE;

int readSize(GARAGE *taj)
{
    printf("Size:\n");
    if (scanf("%d %d", &(*taj).floors, &(*taj).positions) != 2 || (*taj).floors < 0 || (*taj).positions < 0)
        return 0;
    return 1;
}

int takenParking(GARAGE *taj, int floor, int position)
{
    GARAGE *temp = taj;
    for (int i = 0; i < temp->occupiedlen; ++i)
    {
        if (temp->occupied[i].floor == floor && temp->occupied[i].position == position)
            return 1;
    }
    return 0;
}

int getPlate(GARAGE *taj, int floor, int position)
{
    GARAGE *temp = taj;
    for (int i = 0; i < temp->occupiedlen; ++i)
    {
        if (temp->occupied[i].floor == floor && temp->occupied[i].position == position)
            return i;
    }
    return 0;
}
int existingCar(GARAGE *taj, char RZ[11], int *index)
{
    for (int i = 0; i < taj->occupiedlen; ++i)
    {
        if (strcmp(taj->occupied[i].rz, RZ) == 0)
        {
            *index = i;
            return 1;
        }
    }
    return 0;
}
void readRequests(GARAGE *taj, int initialSize)
{
    char mode;
    int total = 0;
    printf("Requests:\n");
    while (scanf("\n%c", &mode) == 1)
    {
        if (mode != '+' && mode != '-')
            break;
        if (mode == '+')
        {
            int requestedFloor, requestedPosition;
            char buffer[11];
            if (scanf("%d %d %10s", &requestedFloor, &requestedPosition, buffer) != 3 || requestedFloor < 0 || requestedFloor >= taj->floors || requestedPosition < 0 || requestedPosition > taj->positions)
                break;
            if (!takenParking(taj, requestedFloor, requestedPosition))
            {
                total++;
                printf("OK\n");
                if (total >= initialSize)
                {
                    initialSize = 2 * initialSize + 1;
                    taj->occupied = (PARKEDCAR *)realloc(taj->occupied, initialSize * sizeof(PARKEDCAR));
                }
                taj->occupied[taj->occupiedlen].floor = requestedFloor;
                taj->occupied[taj->occupiedlen].position = requestedPosition;
                strcpy(taj->occupied[taj->occupiedlen].rz, buffer);
                (taj->occupiedlen)++;
            }
            else
            {
                int index = getPlate(taj, requestedFloor, requestedPosition);
                printf("Occupied %s\n", taj->occupied[index].rz);
            }
        }
        if (mode == '-')
        {
            int index = 0;
            char bufferRZ[11];
            if (scanf("%10s", bufferRZ) != 1)
                break;
            if (existingCar(taj, bufferRZ, &index))
            {
                printf("OK\n");
                for (int i = index; i < (taj->occupiedlen) - 1; ++i)
                {
                    taj->occupied[i] = taj->occupied[i + 1];
                }
                (taj->occupiedlen)--;
            }
            else
            {
                printf("Not Found\n");
            }
        }
    }
    if (!feof(stdin))
    {
        printf(INVALID);
        return;
    }
}
int main()
{
    GARAGE taj;
    if (!readSize(&taj))
    {
        printf(INVALID);
        return 1;
    }
    int initialSize = 10;
    taj.occupied = (PARKEDCAR *)malloc(initialSize * sizeof(PARKEDCAR));
    taj.occupiedlen = 0;
    readRequests(&taj, initialSize);
    free(taj.occupied);
    taj.occupied = NULL;
    return 0;
}
