#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main()
{

  // char *string = malloc(sizeof(char) * length);  this is the case for 1 string

  // for array of strings

  char **strings; // we will dynamically allocatie memory in 2 steps

  int total = 0; // total number of strings

  printf("Enter number of strings: ");
  scanf("%d", &total);

  strings = malloc(total * sizeof(char *)); // pointer to some block of memory thats able to store "number" of pointers

  // ask user for each string

  char buffer[BUFFER_SIZE];
  int length = 0;

  // use fgets to get strings

  while (getchar() != '\n')
    ;

  printf("\n");

  for (int i = 0; i < total; i++)
  {
    printf("enter string %d: ", i);
    fgets(buffer, BUFFER_SIZE, stdin);
    length = strlen(buffer);
    // move up null terminator to remove \n character "abc\n" -> "abc\0"
    buffer[length - 1] = '\0';
    strings[i] = malloc(length * sizeof(char));
    strcpy(strings[i], buffer);
  }

  printf("\n resulting strings array\n\n");

  for (int i = 0; i < total; ++i)
  {
    printf("string[%d] = %s\n", i, strings[i]);
  }
  printf("\n");

  /* free each string pointer in a loop */
  for (int i = 0; i < total; i++)
    free(strings[i]);

  /* free pointer to strings */
  free(strings);

  return 0;
}
