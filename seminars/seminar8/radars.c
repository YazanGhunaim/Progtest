/*
List of targets and radars:
T 5.0 7.0
T 6 8
T -3 2
R 2 3 5
T 4 -1
R 0 0 10
T 1 2
Coverage:
Radar #0: 3
Radar #1: 5
*/
#include <stdio.h>
#include <stdlib.h>

#define invalid "Invalid input.\n"

int readInput(char input, double x, double y, int rangeOfRadar, int *targetsNum, int *radarsNum);

int main()
{

    int numOfTargets = 0;
    int numOfRadars = 0;

    char input = '\0';

    double x = 0;
    double y = 0;
    double range = 0;

    printf("List of targets and radars:\n");

    readInput(input, x, y, range, &numOfTargets, &numOfRadars);

    return EXIT_SUCCESS;
}

int readInput(char input, double x, double y, int rangeOfRadar, int *targetsNum, int *radarsNum)
{
    int numOfTargets = 0;
    int numOfRadars = 0;

    char radar = 'R';
    char target = 'T';
    char buffer;

    while (scanf("%c", &input) == 1)
    {
        scanf("%c", &buffer);
        if (input == radar)
        {
            scanf("%lf %lf %lf", &x, &y, &rangeOfRadar);
            radarsNum++;
        }
        else if (input == target)
        {
            scanf("%lf %lf %lf", &x, &y);
            targetsNum++;
        }
        else
        {
            printf(invalid);
            return EXIT_FAILURE;
        }
    }
    if (!feof(stdin))
    {
        printf(invalid);
        return EXIT_FAILURE;
    }

    *targetsNum = numOfTargets;
    *radarsNum = numOfRadars;

    return EXIT_SUCCESS;
}
