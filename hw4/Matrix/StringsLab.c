#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//char name[] = {'F','i','t','\0'}; // \0 is the zero byte aka terminating zero in strings
//printf("Hello\0world.\n); --> Hello
// char name2[] = "FIT" --> size 4

//const char *msg = "Invalid input.\n" pointer to some memory which is hardcoded in the program


//strlen(name) --> 3
//sizeof(name) --> 4



bool isPalindrom(const char * str) {
	int h = strlen(str) - 1;
	int l = 0;
 
	while (h>0)
	{
		if(str[i++] != str[h--]) {
			return 0;
		}	
	}
return 1;
}


void reverseString(char * str) {}
bool checkPassword(const char * password) {}

char passwordInProgram[] = "MyVerySecretpassword";

void stringTest() {
	char name[100];
 	if (scanf("%99s", name) != 1) { //%99s limits characters to 99 with \0 its 100
	printf("rip\n");
	return;
	 }
}


int main() {
printf("lenght of tomas is %lu\n", strlen("tomas"));
//encoding 
 stringTest();
 return 0;
}
