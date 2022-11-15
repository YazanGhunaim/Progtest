// #include <stdio.h>

// int main()
// {
//     int x[10000];
//     int c, numblanks, numtabs, numnewlines;

//     numblanks = 0;
//     numtabs = 0;
//     numnewlines = 0;

//     int y;
//     printf("Enter some text and press \"Enter\"\n");
//     int j = 0;
//     while ((scanf("%d", &y) == 1) && ((c = getchar()) != EOF))
//     {

//         x[j] = y;
//         if (c == ' ')
//         {
//             ++numblanks;
//         }

//         if (c == '\n')
//         {
//             ++numnewlines;
//         }
//         j++;
//     }
//     int length = (numnewlines+1) * (numblanks/numnewlines);

//     for (int i = 0; i < length+1; i++)
//     {
//         printf("%d  ", x[i]);
//     }

//     printf("\n");
//     printf("The total number of blanks is %i\n", numblanks);
//     // printf("The total number of tabs is %i\n", numtabs);
//     printf("The total number of newlines is %i\n", numnewlines);
// }

#include <stdio.h>
#include <math.h>

int main()
{
    if (fmod(6,3) != 0)
    {
        printf("gau");
    }
    
    printf("%lf", fmod(6,3));

    return 0;
}