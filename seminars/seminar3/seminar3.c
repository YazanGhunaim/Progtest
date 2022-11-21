// this program convers color from RGB format into hexadecimal format

#include <stdio.h>
#include <stdlib.h>
#include<string.h> 

int main()
{

unsigned int x, y, z;
char rgb[4];
char comma;
char bracket1;
char bracket2;
// int s = scanf("%3s%c%d%c%d%c%d%c", rgb, &bracket1, &x, &comma, &y, &comma, &z, &bracket2);
// printf("s = %d\n rgb = %s\n bracker 1 = %c x = %d c1 =%c y = %d c2 = %c z = %d bracket 2 =%c\n", s,rgb, bracket1, x, comma, y, comma, z, bracket2);
printf("Type color in RGB format:\n");
if (scanf("%3s %c %u %c %u %c %u %c", rgb, &bracket1, &x, &comma, &y, &comma, &z, &bracket2) != 8 || strcmp(rgb,"rgb") != 0 || x > 255 || y > 255 || z >255 || bracket1 != '(' || bracket2 !=')')
{
    printf("Invalid input.\n");
}
else {
    printf("#%.2X%.2X%.2X\n", x,y,z);
}

    return EXIT_SUCCESS;
}
