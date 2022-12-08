#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
/*
int arr[3][3] = {
	{1,2,3}
	{1,2,3}
	{1,2,3}
}
*/

int **arr = malloc(sizeof(int * ) * 3);
for(int i =0; i< 3; ++i) {
  arr[i] = malloc(sizeof(int) * 3);	
}

for(int i = 0; i < 3;++i) {
	free(arr[i]);
	arr[i] = NULL;
}
free(arr);
arr = NULL;

return 0;
}
