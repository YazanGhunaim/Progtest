#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Author: Yazan Ghunaim*/
/*-------------------------------- Macros/Preprocessors ----------------------------------------*/
#define invalid "Invalid input.\n"
#define minimum 2       // minimum number of airplanes in input should be 2
#define BUFFER_SIZE 200 // max number of characters an airplane name could have
#define EPSILON 1e-12
/*-------------------------------- Macros/Preprocessors ----------------------------------------*/

/*----------------------------- Declaring Function Signatures ----------------------------------*/

/*-------------------------- All functions Explained Under Main --------------------------------*/
double *pushInArrayX(double *xArray, size_t *pSize, size_t *pCapacity, double newItem);
double *pushInArrayY(double *yArray, size_t *pSize, size_t *pCapacity, double newItem);
double distance(double x[], double y[], int point1, int point2);
void fillDistanceArray(double distanceArray[], double x[], double y[], int lengthOfDistanceArray, int lengthOfX);
void minimumDistance(double distanceArray[], int n, double *minDist);
int numberOfPairs(double distance[], int n, double minDist);
void pairs(char *names[], double x[], double y[], double minDist, int lengthOfX, int lengthOfDistanceArray);
/*----------------------------- Declaring Function Signatures ----------------------------------*/

int main()
{
    double pointx = 0;
    double pointy = 0;

    double *xArray = NULL;
    double *yArray = NULL;

    size_t numberSizeX = 0;
    size_t numberCapacityX = 0;

    size_t numberSizeY = 0;
    size_t numberCapacityY = 0;

    char buffer[BUFFER_SIZE];
    char **names = NULL;

    int count = 0;
    int length = 0;

    // initial size of names array
    int initialSize = 3;
    double minDist = 0;

    names = (char **)malloc((initialSize) * sizeof(char *));
    /*-------------------------------- Gathering user input ---------------------------------------*/
    printf("Plane coordinates:\n");
    while (scanf("%lf,%lf:%199s", &pointx, &pointy, buffer) == 3)
    {
        if (count >= initialSize)
        {
            initialSize = 2 * initialSize + 1;
            names = (char **)realloc(names, initialSize * sizeof(char *));
        }
        length = strlen(buffer);
        names[count] = (char *)malloc((length + 1) * sizeof(char));
        strcpy(names[count], buffer);
        xArray = pushInArrayX(xArray, &numberSizeX, &numberCapacityX, pointx);
        yArray = pushInArrayY(yArray, &numberSizeY, &numberCapacityY, pointy);
        count++;
    }
    // if file end is not EOF or airplanes inputed less than 2, print invalid
    if (!feof(stdin) || count < minimum)
    {
        // freeing each string pointer in a loop
        for (size_t i = 0; i < numberSizeX; i++)
            free(names[i]);
        // freeing pointer to strings
        free(names);
        free(xArray);
        free(yArray);
        printf(invalid);
        return 1;
    }
    /*-------------------------------- Gathering user input ---------------------------------------*/

    // the size of the distances between points is calculated here as combination selecting two out of number of planes
    int sizeOfDistanceArray = (numberSizeX) * (numberSizeX - 1) / 2;
    // declaring distanceArray
    double *distanceArray = (double *)malloc((sizeOfDistanceArray * 2 + 1) * sizeof(*distanceArray));
    // filling up the distanceArray with all possible combinations of points
    fillDistanceArray(distanceArray, xArray, yArray, sizeOfDistanceArray, numberSizeX);
    // printing out the minimum distance
    minimumDistance(distanceArray, sizeOfDistanceArray, &minDist);
    // printing out the number of airplane pairs with distance equal to minimum
    printf("Pairs found: %d\n", numberOfPairs(distanceArray, sizeOfDistanceArray, minDist));
    // if there are pairs with distance equal to min print them
    if (numberOfPairs(distanceArray, sizeOfDistanceArray, minDist) > 0)
    {
        pairs(names, xArray, yArray, minDist, numberSizeX, sizeOfDistanceArray);
    }

    /*--------------------------------- Freeing Dynamically Allocated Memory --------------------------*/
    // freeing distance array
    free(distanceArray);
    // freeing each string pointer in a loop
    for (size_t i = 0; i < numberSizeX; i++)
        free(names[i]);
    // freeing pointer to strings
    free(names);
    free(xArray);
    free(yArray);
    /*--------------------------------- Freeing Dynamically Allocated Memory --------------------------*/
    return 0;
}

/*
    pushInArray ->  @parameters:
                        - pointer to double array (xArray) ~ stores x coordinates
                        - pointer of type size_t which keeps track of the size of the array
                        - pointer of type size_t which keeps track and updates the capacity of the array
                        - double newItem -> the item we are pushing to the array (x coordinate)

                    @brief:
                        - on every call, checks if the size is greater than or equal to the capacity, and
                          if so, the capacity is increased by x2 + 1 "inspired by tutorials"
                        - then the array is reallocated with the new capacity
                        - the new x coordinate is then added as the last element
                        - the size is increased
                        - pointer to the array is the returned (xArray)
*/
double *pushInArrayX(double *xArray, size_t *pSize, size_t *pCapacity, double newItem)
{
    if (*pSize >= *pCapacity)
    {
        // increasing capacity
        *pCapacity = 2 * (*pCapacity) + 1;
        xArray = (double *)realloc(xArray, *pCapacity * sizeof(xArray[0]));
    }
    xArray[*pSize] = newItem;
    (*pSize)++;
    return xArray;
}

/*
    pushInArray ->  @parameters:
                        - pointer to double array (yArray) ~ stores y coordinates
                        - pointer of type size_t which keeps track of the size of the array
                        - pointer of type size_t which keeps track and updates the capacity of the array
                        - double newItem -> the item we are pushing to the array (y coordinate)

                    @brief:
                        - on every call, checks if the size is greater than or equal to the capacity, and
                          if so, the capacity is increased by x2 + 1 "inspired by tutorials"
                        - then the array is reallocated with the new capacity
                        - the new y coordinate is then added as the last element
                        - the size is increased
                        - pointer to the array is the returned (yArray)
*/
double *pushInArrayY(double *yArray, size_t *pSize, size_t *pCapacity, double newItem)
{
    if (*pSize >= *pCapacity)
    {
        // increasing capacity
        *pCapacity = 2 * (*pCapacity) + 1;
        yArray = (double *)realloc(yArray, *pCapacity * sizeof(yArray[0]));
    }
    yArray[*pSize] = newItem;
    (*pSize)++;
    return yArray;
}

double distance(double x[], double y[], int point1, int point2)
{
    return sqrt(pow(x[point2] - x[point1], 2) + pow(y[point1] - y[point2], 2));
}

/*
    fillDistanceArray ->  @parameters:
                                - distanceArray -> the array we are filling up with distances between each combination of points in our input
                                - array of x coordinates
                                - array of y coordinates
                                - desired length/size of distanceArray... calculated in main using nC2
                                - length of xarray which is also the number of lines in our input / number of planes
                          @brief:
                                - goes through each index up to lengthOfDistanceArray and according to what index
                                    its on calculates the correct distance of said point, and places in in the array
*/
void fillDistanceArray(double distanceArray[], double x[], double y[], int lengthOfDistanceArray, int lengthOfX)
{
    int index = 0;
    for (int i = 0; i < lengthOfDistanceArray; i++)
    {
        int count = i + 1;
        for (int j = 0, k = count; j < lengthOfDistanceArray && k < lengthOfX; j++)
        {
            distanceArray[index] = distance(x, y, i, k);
            index++;
            k++;
        }
    }
}

void minimumDistance(double distanceArray[], int n, double *minDist)
{

    double min = distanceArray[0];

    for (int i = 1; i < n; i++)
    {
        if (min > distanceArray[i])
            min = distanceArray[i];
    }
    printf("Minimum airplane distance: %lf\n", min);
    *minDist = min;
}

/*
    @brief:
            - iterates through the array and updates answer by
              +1 everytime it find a distance equal to minDist
 */
int numberOfPairs(double distance[], int n, double minDist)
{

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (fabs(distance[i] - minDist) <= EPSILON * (fabs(minDist) + fabs(distance[i])))
        {
            ans++;
        }
    }

    return ans;
}
/*
    @brief:
        - same overall flow as filldistanceArray function but when we stumble upon
          a distance equal to min we print the corresponding pair
*/
void pairs(char *names[], double x[], double y[], double minDist, int lengthOfX, int lengthOfDistanceArray)
{
    int index = 0;
    for (int i = 0; i < lengthOfDistanceArray; i++)
    {
        int count = i + 1;
        for (int j = 0, k = count; j < lengthOfDistanceArray && k < lengthOfX; j++)
        {
            if (fabs(distance(x, y, i, k) - minDist) <= EPSILON * (fabs(minDist) + fabs(minDist)))
            {
                printf("%s - %s\n", names[i], names[k]);
            }

            index++;
            k++;
        }
    }
}
