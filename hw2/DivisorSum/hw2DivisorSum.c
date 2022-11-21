/*Intervals:
? 1 10
4
8
Total: 2*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

unsigned primeSumDivisor(unsigned n);
void questionMark(int x, int y, int z); // x start y end z total
void hash(int x, int y, int z);         // x start y end z total
int SumOfdivisors(int n);
void sieve(char data[], size_t n);

int main()
{
    char startSymbol, buffer;
    unsigned int start = 0, end = 0, total = 0;
    // size_t count = 0;
    // size_t n;
    
//   printf("%d %d %d", SumOfdivisors(8), SumOfdivisors(4), SumOfdivisors(279));
    // unsigned char *data = (unsigned char *)malloc((n + 7) / 8 * sizeof(*data));
    printf("Intervals:\n");

    while (scanf("%c %u %u", &startSymbol, &start, &end) == 3)
    {
        if ((startSymbol != '?' && startSymbol != '#') || end < start || start < 1)
        {
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
        switch (startSymbol)
        {
        case '?':
            questionMark(start, end, total);
            scanf("%c", &buffer);
            break;
        case '#':
            hash(start, end, total);
            scanf("%c", &buffer);
            break;
        }
    }
    if (!feof(stdin))
    {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void sieve(char data[], size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        data[i] = 1;
    }
    data[0] = data[1] = 0;

    for (size_t i = 2; i < sqrt(n); ++i)
    {
        if (data[i])
        {
            for (size_t j = i * i; j < n; j += i)
            {
                data[j] = 0;
            }
        }
    }
}

int SumOfdivisors(int n)
{
    int result = 0;
    int max = sqrt(n);
    for (int i = 2; i <= max; ++i)
    {

        if (n % i == 0)
        {
            // if both divisors are same then
            // add it only once
            if (i == (n / i))
                result += i;
            // else add both
            else
                result += (i + n / i);
        }
    }

    // Add 1 to the result as 1 is also
    // a divisor
    return (result + 1);
}

unsigned primeSumDivisor(unsigned n)
{
    size_t x = SumOfdivisors(n)+1;
    size_t i = x;
    char *data = (char *)malloc((x+1) * sizeof(*data));

    sieve(data, x);

    if (data[i - 1])
    {
        free(data);
        return 1;
    }
    free(data);
    return 0;
}

// unsigned primeSumDivisor(unsigned n)
// {
//     unsigned x = SumOfdivisors(n);
//     unsigned i;

//     if (x < 2)
//         return 0;
//     if (x == 2)
//         return 1;
//     if (x % 2 == 0)
//         return 0;
//     unsigned max = (unsigned)sqrt(x);
//     for (i = 3; i <= max; i += 2)
//         if (x % i == 0)
//             return 0;
//     return 1;
// }

void questionMark(int x, int y, int z)
{

    for (int i = x; i <= y; ++i)
    {

        if (primeSumDivisor(i) == 1)
        {
            printf("%d\n", i);
            ++z;
        }
    }
    printf("Total: %d\n", z);
}

void hash(int x, int y, int z)
{
    for (int i = x; i <= y; ++i)
    {

        if (primeSumDivisor(i) == 1)
        {
            ++z;
        }
    }
    printf("Total: %d\n", z);
}
