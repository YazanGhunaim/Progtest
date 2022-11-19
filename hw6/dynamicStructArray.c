/*https://www.youtube.com/watch?v=lq8tJS3g6tY&t=443s*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
} Point;

int main()
{
	Point p1;

	// using the stack
	p1.x = 4;
	p1.y = 5;

	printf("Static Point struct:\n(%d, %d)\n", p1.x,p1.y);

	// using heap for 1 point
	Point *p2;

	p2 = malloc (sizeof(* p2));

	p2 -> x = 5;
	p2 -> y = 2;

	printf("Dynamic Point Struct:\n(%d, %d)\n", p2->x,p2->y);

	free(p2);

	// using heap for an array of point structs

	int length = 3;

	Point *array;

	array = malloc(length * sizeof(*array));

	// access to first point struct
	// we can use the dot operator without derefrencing the pointer because array[0] is
	// equivalent to (*(array + 2)) "Pointer Arithmetic"
	array[0].x = 1;
	array[0].y = 1;

	array[1].x = 2;
	array[1].y = 2;

	array[2].x = 3;
	array[2].y = 3;

	printf("Dynamic Struct Array...\n");
	for(int i = 0; i < length; ++i)
		printf("(%d, %d)\n", array[i].x,array[i].y);

	// reallocating
	length = 4;

	array = realloc(array, sizeof(*array) * length);

	array[3].x = 4;
	array[3].y = 4;

	printf("Reallocated Dynamic Struct Array...\n");
	for(int i = 0; i < length; ++i)
		printf("(%d, %d)\n", array[i].x,array[i].y);

	free(array);
}
