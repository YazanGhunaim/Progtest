#include <stdio.h>

int NumOfDigits(int x);

int main()
{
int limit;

printf("Limit:\n");
if(scanf("%d", &limit) != 1 || limit <= 0){
  printf("Invalid input.\n");
  return 1;
}

int biggest = (limit * limit);
int width = NumOfDigits(biggest) + 1;
char bar = '|';
char dash = '-';

printf("%*c",width,bar);
for(int k = limit; k>=1; k--){
  printf("%*d", width, k);
}
printf("\n");

for(int d = 1;  d <= width-1; d++){
  printf("%c", dash);
}
printf("+");
for(int l = 1; l <= limit*width; l++){
  printf("%c",dash);
}
printf("\n");

for(int i = 1; i <= limit; i++)
{
 printf("%*d%c", width-1, i, bar);
 for(int j = limit; j >= i; j--)
 {  
   printf("%*d", width,i * j);
 }
printf("\n");
}

return 0;
}

int NumOfDigits(int x){
  int i = 0;
  while(x!=0)
  {
    x/=10;
    i++;
  }
  return i;
}
