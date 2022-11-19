#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define invalid "Invalid input.\n"
#define maxChar 4096

typedef int (*Compare)(const void *, const void *);

typedef struct
{
    int shelfID;
    char goods[maxChar];
} shelf;

int readGoods(shelf **array, int id, int *initialSize, int *length)
{
    int count = *length;
    int first = 1;
    char buffer;
    char c = 0;

    while ((c = getchar()) != EOF)
    {
        if (count >= (*initialSize))
        {
            (*initialSize) = 2 * (*initialSize) + 1;
            (*array) = (shelf *)realloc((*array), (*initialSize) * sizeof(**array));
        }
        if (first)
        {
            (*array)[count].goods[0] = c;
            if (c == '#')
            {
                if (scanf("%d", &id) == 1)
                {
                    fgets(&(*array)[count].goods[0], maxChar, stdin);
                    (*array)[count].shelfID = id;
                    count++;
                    *length = count;
                }
                else
                {
                    printf(invalid);
                    return 1;
                }
            }
            else
            {
                fgets(&(*array)[count].goods[0], maxChar, stdin);
                (*array)[count].shelfID = id;
                count++;
                *length = count;
                first = 0;
            }
        }
        else
        {
            (*array)[count].goods[0] = c;
            if (c == '#')
            {
                if (scanf("%d", &id) == 1)
                {
                    fgets(&(*array)[count].goods[0], maxChar, stdin);
                    (*array)[count].shelfID = id;
                    count++;
                    *length = count;
                }
                else
                {
                    printf(invalid);
                    return 1;
                }
            }
            else
            {
                fgets(&(*array)[count].goods[1], maxChar, stdin);
                (*array)[count].shelfID = id;
                count++;
                *length = count;
            }
        }
    }
    return 1;
}

int main()
{
    shelf *array;

    int initialSize = 3;
    int length = 0;
    int first = 1;
    int id;

    array = (shelf *)malloc(initialSize * sizeof(*array));

    while (scanf("#%d", &id) == 1)
    {
        if (first && id != 0)
        {
            printf(invalid);
            return 1;
        }
        else
        {
            readGoods(&array, id, &initialSize, &length);
            first = 0;
        }
    }

    // printf("%d", length);

    printf("\n");
    for (int i = 0; i < length; i++)
    {
        printf("num: %d, id: %d, good: %s\n", i, array[i].shelfID, array[i].goods);
    }

    return 0;
}
