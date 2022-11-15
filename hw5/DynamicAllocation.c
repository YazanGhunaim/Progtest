#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

int *arr = calloc(256,sizeof(int));
//calloc set everything to 0 from the start
//memset(arr,0,sizeof(int)*64);

//what about memory reallocation? what if i have an array and an algorithm to optimizie that array for example shrinks it?

if(arr == NULL) return 1;

//realloc(arr, 64*sizeof(int));
// realloc sometimes frees arr then, malloc(64*sizeof(int));
// get the value returned!
arr = realloc(arr,64 * sizeof(int)); 
if (arr == NULL) return 1;

int i;
for(i = 0; i<64; ++i) {
	printf("%d ", arr[i]);
}
printf("\n");

free(arr);

return 0;
}
