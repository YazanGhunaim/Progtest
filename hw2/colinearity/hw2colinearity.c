/*Point A:
1 2
Point B:
3 4
Point C:
5 6
There exists a line connecting all three points.
Point B is in the middle.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-10

double readNumber();
int onLine(double a, double b, double c, double d, double e, double f); // determines if they line on a common straigh line
int equalGradient(double a, double b, double c, double d, double e, double f);
void middle(double a, double b, double c, double d, double e, double f);
void identical(double a, double b, double c, double d, double e, double f);

int main()
{

    double x1, x2, x3, y1, y2, y3;

    printf("Point A:\n");
    x1 = readNumber();
    y1 = readNumber();

    printf("Point B:\n");
    x2 = readNumber();
    y2 = readNumber();

    printf("Point C:\n");
    x3 = readNumber();
    y3 = readNumber();

    identical(x1, y1, x2, y2, x3, y3);

    if (onLine(x1, y1, x2, y2, x3, y3) == 1)
    {
        printf("There exists a line connecting all three points.\n");
        middle(x1, y1, x2, y2, x3, y3);
    }
    else
    {
        printf("No line connects all points.\n");
    }

    return EXIT_SUCCESS;
}

double readNumber()
{
    double x;
    if (scanf("%lf", &x) != 1)
    {
        printf("Invalid input.\n");
        exit(1);
    }

    return x;
}

int onLine(double a, double b, double c, double d, double e, double f)
{
    if (equalGradient(a, b, c, d, e, f) == 1)
    {
        return 1;
    }
    return 0;
}
// x1 y1 x2 y2 x3 y3
// a   b  c  d  e  f
int equalGradient(double a, double b, double c, double d, double e, double f)
{
    double gradient1, gradient2;

    gradient1 = (d - b) * (e - a);
    gradient2 = (c - a) * (f - b);

    if (fabs(gradient1 - gradient2) <= fabs(gradient1) * EPSILON)
    {
        return 1;
    }

    return 0;
}

void middle(double a, double b, double c, double d, double e, double f)
{
    if (a != c && c != e)
    {
        if (a > c)
        {
            if (c > e)
                // return c;
                printf("Point B is in the middle.\n");
            else if (a > e)
                // return e;
                printf("Point C is in the middle.\n");
            else
                // return a;
                printf("Point A is in the middle.\n");
        }
        else
        {
            if (a > e)
                // return a;
                printf("Point A is in the middle.\n");
            else if (c > e)
                // return e;
                printf("Point C is in the middle.\n");
            else
                // return c;
                printf("Point B is in the middle.\n");
        }
    }

    else
    {
        if (b > d)
        {
            if (d > f)
                // return d;
                printf("Point B is in the middle.\n");
            else if (b > f)
                // return f;
                printf("Point C is in the middle.\n");
            else
                // return b;
                printf("Point A is in the middle.\n");
        }
        else
        {
            if (b > f)
                // return b;
                printf("Point A is in the middle.\n");
            else if (d > f)
                // return f;
                printf("Point C is in the middle.\n");
            else
                // return d;
                printf("Point B is in the middle.\n");
        }
    }
}

// a    c      e
// x1  x2      x3
// y1  y2      y3
// b   d       f
void identical(double a, double b, double c, double d, double e, double f)
{
    if ((a == c && b == d) || (c == e && d == f) || (a == e && b == f))
    {
        printf("Some points are identical.\n");
        exit(1);
    }
}
