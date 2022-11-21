#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main()
{
size_t size;
printf("Choose size:\n");
if(scanf("%zd", &size) != 1) {
 printf("Invalid input.");
 return EXIT_FAILURE;
}

int * array =  (int *) malloc(size * sizeof( * array));

memset(array, 0, size*sizeof(* array));

for(size_t i = 0; i < size; ++i) {
 printf("%d\n", array[i]);
}

return 0;
}
