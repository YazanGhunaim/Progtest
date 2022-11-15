#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{

    double a, b;
    char op, eq;

    printf("Type formula:\n");

    if (scanf("%lf %c %lf %c", &a, &op, &b, &eq) != 4 || eq != '=')
    {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    switch (op)
    {
    case '+':
        printf("%g\n", a + b);
        break;
    case '-':
        printf("%g\n", a - b);
        break;
    case '*':
        printf("%g\n", a * b);
        break;
    case '/':
        if (b == 0)
        {
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
        else if (a < 0 && b < 0)
        {
            printf("%g\n", floor(a / b));
            return EXIT_SUCCESS;
        }
        else if (a < 0 || b < 0)
        {
            printf("%g\n", ceil(a / b));
        return EXIT_SUCCESS;}
        else
        {
            printf("%g\n", floor(a / b));
            return EXIT_SUCCESS;
        }

        printf("%g\n", a / b);
        break;

    default:
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
