#include <stdio.h>
#include <stdlib.h>

#define INVALID "Invalid input.\n"

typedef struct dominos
{
    char name[65];
    int a, b, c, d;
    int visited;
} DOMINO;

typedef struct matchList
{
    int index1;
    int index2;
    struct matchList *next;
} MATCHLIST;

int readInput(DOMINO **array, int initialSize, int *finalSize)
{
    int total = 0;
    int index = 0;
    DOMINO read;
    // while(scanf("%64[^ ] [ %d , %d , %d , %d ]\n", read.name, &read.a, &read.b, &read.c, &read.d) == 5)
    while (scanf(" %64s [ %d , %d , %d , %d ]", read.name, &read.a, &read.b, &read.c, &read.d) == 5)
    {
        read.visited = 0;
        if (total >= initialSize)
        {
            initialSize = initialSize * 2 + 1;
            *array = (DOMINO *)realloc(*array, sizeof(**array) * initialSize);
        }
        total++;
        (*array)[index++] = read;
    }
    if (!feof(stdin))
    {
        return 0;
    }
    *finalSize = total;
    return 1;
}

int duplicate(DOMINO *one, DOMINO *two)
{
    if (one->a == two->a && one->b == two->b && one->c == two->c && one->d == two->d)
        return 1;
    if (one->a == two->b && one->b == two->c && one->c == two->d && one->d == two->a)
        return 1;
    if (one->a == two->c && one->b == two->d && one->c == two->a && one->d == two->b)
        return 1;
    if (one->a == two->d && one->b == two->a && one->c == two->b && one->d == two->c)
        return 1;
    return 0;
}

MATCHLIST *insert(MATCHLIST *head, int one, int two)
{
    MATCHLIST *newNode = (MATCHLIST *)malloc(sizeof(*newNode));
    newNode->index1 = one;
    newNode->index2 = two;
    newNode->next = NULL;
    if (!head)
    {
        head = newNode;
        return head;
    }
    MATCHLIST *temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;

    return head;
}

void printDupes(MATCHLIST *head, DOMINO *array)
{
    MATCHLIST *dummy = head;
    while (dummy)
    {
        int index = dummy->index1;
        printf("%s", array[index].name);
        MATCHLIST *secondDummy = dummy;
        while (secondDummy)
        {
            if (secondDummy->index1 == index)
            {
                printf(" = %s", array[secondDummy->index2].name);
            }
            secondDummy = secondDummy->next;
        }
        printf("\n");
        if (dummy->index1 == dummy->next->index1 && dummy->next->next)
            dummy->next = dummy->next->next;
        else if (dummy->index1 != dummy->next->index1)
            dummy = dummy->next;
        else
            break;
    }
}

void freelist(MATCHLIST *src)
{
    while (src)
    {
        MATCHLIST *next = src->next;
        free(src);
        src = next;
    }
}

void findDuplicates(DOMINO *array, int size)
{
    int unique = size;
    MATCHLIST *head = NULL;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (duplicate(&array[i], &array[j]) && array[j].visited == 0)
            {
                head = insert(head, i, j);
                array[j].visited = 1;
                unique--;
            }
        }
    }
    printf("Unique: %d\n", unique);
    printDupes(head, array);
    freelist(head);
}

int main()
{
    int initialSize = 3;
    int finalSize = 0;
    DOMINO *array = (DOMINO *)malloc(sizeof(*array) * 3);
    printf("Dominos:\n");
    if (!readInput(&array, initialSize, &finalSize))
    {
        free(array);
        printf(INVALID);
        return 1;
    }
    findDuplicates(array, finalSize);
    free(array);
    return 0;
}
