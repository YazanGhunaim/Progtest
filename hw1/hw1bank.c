#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    double creditRate;
    double debitRate;
    double transaction = 1;
    double balance = 0;
    int day = 1;
    int numOfDays = 0;
    int prevDay = 0;             // stores previous value of day
    int whileIterations = 0; // to count number of times while loop ran
    char comma;

    printf("Enter credit interest rate [%%]:\n");
    if (scanf("%lf", &creditRate) != 1)
    {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("Enter debet interest rate [%%]:\n");
    if (scanf("%lf", &debitRate) != 1)
    {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("Enter transactions:\n");

    while (transaction != 0)
    {

        if (scanf("%d %c %lf", &day, &comma, &transaction) != 3 || comma != ',')
        {
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
        whileIterations++;

        if (whileIterations > 1)
            if (prevDay > day)
            {
                printf("Invalid input.\n");
                return EXIT_FAILURE;
            }
        {
            if (balance > 0)
            {
                numOfDays = day - prevDay;
                for (int i = 0; i < numOfDays; i++)
                {
                    balance += balance * (creditRate / 100);
                    balance = floor(100 * balance) / 100;
                }
            }
            else if (balance <= 0)
            {
                numOfDays = day - prevDay;
                for (int i = 0; i < numOfDays; i++)
                {
                    balance += balance * (debitRate / 100);
                    balance = ceil(100 * balance) / 100;
                }
            }
        }

        balance += transaction;
        prevDay = day;

        if (transaction == 0)
        {
            break;
        }
    }
    printf("Balance: %.2lf\n", balance);

    return EXIT_SUCCESS;
}
