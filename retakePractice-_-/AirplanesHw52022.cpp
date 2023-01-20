#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INVALID "Invalid input.\n"
#define EPSILON 10e-12

typedef struct AIRPLANE
{
    double x;
    double y;
    char *name;
} Airplane;

int readInput(Airplane ***array, int initialLength, int *finalLength)
{
    int total = 0;
    int index = 0;
    double point1, point2;
    char string[200];
    while (scanf("%lf,%lf:%199s", &point1, &point2, string) == 3)
    {
        if (total >= initialLength)
        {
            initialLength = 2 * initialLength + 1;
            *array = (Airplane **)realloc(*array, initialLength * sizeof(**array));
        }
        total++;
        Airplane *newPlane = (Airplane *)malloc(sizeof(*newPlane));
        newPlane->x = point1;
        newPlane->y = point2;
        newPlane->name = strdup(string);
        (*array)[index++] = newPlane;
    }
    *finalLength = total;
    if (!feof(stdin) || total < 2)
    {
        free(*array);
        return 0;
    }
    return 1;
}

double distanceBetweenTwoPoints(double xOne, double yOne, double Xtwo, double Ytwo)
{
    double deltaX = (Xtwo - xOne);
    double deltaY = (Ytwo - yOne);
    return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

void fillArray(double *distanceArray, int distanceArrayLength, Airplane **array, int airplaneArrayLength)
{
    int index = 0;
    for (int i = 0; i < airplaneArrayLength; ++i)
    {
        for (int j = i + 1; j < airplaneArrayLength && index < distanceArrayLength; ++j)
        {
            distanceArray[index++] = distanceBetweenTwoPoints(array[i]->x, array[i]->y, array[j]->x, array[j]->y);
        }
    }
}

int getMinimum(double *array, int size)
{
    int min = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i] < array[min])
            min = i;
    }
    return min;
}

double cmp(const double *a, const double *b)
{
    return (*b < *a) - (*a < *b);
}

int numOfPairs(double *array, int size, double min)
{
    int total = 0;
    for (int i = 0; i < size; ++i)
    {
        if (fabs(array[i] - min) <= EPSILON * (fabs(min)))
            total++;
    }
    return total;
}

void pairs(Airplane **array, int size, double min)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            double distance = distanceBetweenTwoPoints(array[i]->x, array[i]->y, array[j]->x, array[j]->y);
            if (fabs(distance - min) <= EPSILON * (fabs(min)))
            {
                printf("%s - %s\n", array[i]->name, array[j]->name);
            }
        }
    }
}

int main()
{
    int initialLength = 6;
    int finalLength = 0;
    Airplane **array = (Airplane **)malloc(sizeof(*array) * initialLength);
    printf("Plane coordinates:\n");
    if (!readInput(&array, initialLength, &finalLength))
    {
        printf(INVALID);
        return 1;
    }
    double minimumDistance = 0;
    int distanceArrayLength = (finalLength) * (finalLength - 1) / 2;
    double *distanceArray = (double *)malloc(sizeof(*distanceArray) * (distanceArrayLength));
    fillArray(distanceArray, distanceArrayLength, array, finalLength);
    minimumDistance = distanceArray[getMinimum(distanceArray, distanceArrayLength)];
    printf("Minimum airplane distance: %lf\n", minimumDistance);
    printf("Pairs found: %d\n", numOfPairs(distanceArray, distanceArrayLength, minimumDistance));
    pairs(array, finalLength, minimumDistance);
    return 0;
}
