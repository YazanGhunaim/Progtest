#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INVALID "Invalid input.\n"

typedef struct stock
{
    char EON[102];
    int supply;
} STOCK;

typedef struct all
{
    STOCK *stocks;
    int stocksLen;
} ALL;

int findStock(ALL *x, char lookup[101])
{
    for (int i = 0; i < x->stocksLen; ++i)
    {
        if (strcmp(x->stocks[i].EON, lookup) == 0)
        {
            return i;
            break;
        }
    }
    return -1;
}

int valid(char EAN[102])
{
    int length = strlen(EAN);
    if (length < 5 || length > 100)
        return 0;
    for (int i = 0; i < length; ++i)
    {
        if (!isdigit(EAN[i]))
            return 0;
    }
    return 1;
}

int readInput(ALL *x)
{
    int initialSize = 3;
    STOCK read;
    char mode;
    printf("Goods:\n");
    while (scanf("\n%c", &mode) == 1)
    {
        if (mode != '+' && mode != '-')
        {
            return 0;
        }
        if (mode == '+')
        {
            scanf("%dx %101s", &read.supply, read.EON);
            if (!valid(read.EON))
            {
                return 0;
            }
            if (read.supply <= 0)
            {
                break;
            }
            int index = findStock(x, read.EON);
            if (index != -1)
            {
                x->stocks[index].supply += read.supply;
                printf("> %dx\n", x->stocks[index].supply);
            }
            else if (index == -1)
            {
                if (x->stocksLen == initialSize)
                {
                    initialSize = initialSize * 2 + 1;
                    x->stocks = (STOCK *)realloc(x->stocks, initialSize * sizeof(STOCK));
                }
                x->stocks[x->stocksLen] = read;
                printf("> %dx\n", x->stocks[x->stocksLen].supply);
                (x->stocksLen)++;
            }
        }
        if (mode == '-')
        {
            scanf("%dx %101s", &read.supply, read.EON);
            if (!valid(read.EON))
            {
                return 0;
            }
            if (read.supply <= 0)
            {
                break;
            }
            int index = findStock(x, read.EON);
            if (index != -1)
            {
                if (read.supply > x->stocks[index].supply)
                {
                    printf("> Insufficient stock\n");
                    continue;
                }
                x->stocks[index].supply -= read.supply;
                printf("> %dx\n", x->stocks[index].supply);
            }
            else if (index == -1)
            {
                printf("> Insufficient stock\n");
            }
        }
    }
    if (!feof(stdin) || x->stocksLen == 0)
    {
        return 0;
    }
    return 1;
}

int main()
{
    ALL x;
    x.stocks = (STOCK *)malloc(sizeof(STOCK) * 3);
    x.stocksLen = 0;
    if (!readInput(&x))
    {
        printf(INVALID);
        free(x.stocks);
        return 1;
    }

    free(x.stocks);
    return 0;
}
