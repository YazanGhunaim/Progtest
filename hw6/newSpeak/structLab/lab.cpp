#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    double x;
    double y;
} point;

typedef struct
{
    point p1;
    point p2;
    point p3;
    char fillColor[64];
    char strokeColor[64];
} Triangle;

typedef struct
{
    point p;
    double width;
    double height;
    char fillColor[64];
    char strokeColor[64];
} Rectangle;

typedef struct
{
    double width;
    double height;
    Rectangle *Rectangle = NULL;
    size_t capacityRectangles, numRectangles;
    Triangle *triangles = NULL;
    size_t capacityTriangles, numTriangles;
} SVG;

void addTriangle(point p1, point p2, point p3, const char *fillColor, const char *strokeColor, SVG *svg)
{
    Triangle tri;
    tri.p1 = p1;
    tri.p2 = p2;
    tri.p3 = p3;
    strcpy(tri.fillColor, fillColor);
    strcpy(tri.strokeColor, strokeColor);

    if (svg->numTriangles >= svg->capacityTriangles)
    {
        if (svg->capacityTriangles == 0)
        {
            svg->capacityTriangles++;
        }

        svg->capacityTriangles *= 2;
        svg->triangles = (Triangle *)realloc(svg->triangles, svg->capacityRectangles * sizeof(*(svg->triangles)));

        svg->triangles[svg->numTriangles] = tri;
        (svg->numTriangles)++;
        return;
    }
}

void addRectangle(point p1, double width, double height, const char *fillColor, const char *strokeColor, SVG *svg)
{
    Rectangle rec;
    strcpy(tri.fillColor, fillColor);
    strcpy(tri.strokeColor, strokeColor);

    if (svg->numTriangles >= svg->capacityTriangles)
    {
        if (svg->capacityTriangles == 0)
        {
            svg->capacityTriangles++;
        }

        svg->capacityTriangles *= 2;
        svg->triangles = (Triangle *)realloc(svg->triangles, svg->capacityRectangles * sizeof(*(svg->triangles)));

        svg->triangles[svg->numTriangles] = tri;
        (svg->numTriangles)++;
        return;
    }
}

int main()
{

    return 0;
}