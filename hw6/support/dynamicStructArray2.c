#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int x;
	int y;
	char *description;
} Point;

int main()
{
	int length = 3;

	Point *array;

	array = malloc(length*sizeof(*array));

	array[0].x = 1;
	array[0].y = 1;
	// allocating 10 bytes "10 characters"
	array[0].description = malloc(10);
	strcpy(array[0].description, "Point 1");

	array[1].x = 2;
	array[1].y = 2;
	array[1].description = malloc(10);
	strcpy(array[1].description, "Point 2");

	array[2].x = 3;
	array[2].y = 3;
	array[2].description = malloc(10);
	strcpy(array[2].description, "Point 3");

	printf("Dynamic Struct Array...\n");
	for(int i = 0; i < length; ++i){
		printf("(%d, %d)", array[i].x,array[i].y);
		printf("- %s\n", array[i].description);
	}

	for (int i = 0; i < length; ++i)
	{
		free(array[i].description);
	}

	free(array);
}
