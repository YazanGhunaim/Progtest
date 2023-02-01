#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INVALID "Invalid input.\n"
#define EPSILON 10e-12

typedef struct plane
{
    double x, y;
    char name[200];
} PLANE;

typedef struct all
{
    PLANE *array;
    int planeLen;
} ALL;

int readInput(ALL *x)
{
    int initialSize = 3;
    PLANE read;
    while (scanf("%lf,%lf: %199s", &read.x, &read.y, read.name) == 3)
    {
        if (x->planeLen == initialSize)
        {
            initialSize = initialSize * 2 + 1;
            x->array = (PLANE *)realloc(x->array, initialSize * sizeof(PLANE));
        }
        x->array[x->planeLen] = read;
        (x->planeLen)++;
    }
    if (!feof(stdin))
    {
        return 0;
    }
    return 1;
}

double distance(double x, double y, double x2, double y2)
{
    return sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
}

void distanceArray(ALL *x, double *array, int size)
{
    int index = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            array[index++] = distance(x->array[i].x, x->array[i].y, x->array[j].x, x->array[j].y);
        }
    }
}

double minimumDistance(double *array, int size)
{
    double min = array[0];
    for (int i = 1; i < size; ++i)
    {
        if (array[i] < min)
            min = array[i];
    }
    int pairs = 0;
    for (int j = 0; j < size; ++j)
    {
        if (array[j] == min)
            pairs++;
    }
    printf("Minimum airplane distance: %lf\n", min);
    printf("Pairs found: %d\n", pairs);
    return min;
}

void pairs(ALL *x, double min)
{
    for (int i = 0; i < x->planeLen; ++i)
    {
        for (int j = i + 1; j < x->planeLen; ++j)
        {
            double distanceValue = distance(x->array[i].x, x->array[i].y, x->array[j].x, x->array[j].y);
            if (fabs(distanceValue - min) <= EPSILON * fabs(min + distanceValue))
            {
                printf("%s - %s\n", x->array[i].name, x->array[j].name);
            }
        }
    }
}

int main()
{
    ALL x;
    x.array = (PLANE *)malloc(sizeof(PLANE) * 3);
    x.planeLen = 0;
    printf("Plane coordinates:\n");
    if (!readInput(&x))
    {
        free(x.array);
        printf(INVALID);
        return 1;
    }

    int distanceArraySize = x.planeLen * (x.planeLen - 1) / 2;
    double *distance = (double *)malloc(distanceArraySize * sizeof(*distance));
    distanceArray(&x, distance, x.planeLen);
    double minimum = minimumDistance(distance, distanceArraySize);

    pairs(&x, minimum);
    free(x.array);
    free(distance);
    return 0;
}
