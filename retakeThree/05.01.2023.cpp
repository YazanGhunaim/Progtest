#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "Invalid input.\n"

typedef struct domino
{
    char id[65];
    int sides[4];
    int visited;
} DOMINO;

typedef struct all
{
    DOMINO *dominos;
    int dominoLen;
} ALL;

typedef struct list
{
    int index;
    int equal;
    struct list *next;
} LIST;

int readInput(ALL *x)
{
    int initialSize = 3;
    char bOne;
    char bTwo;
    DOMINO read;
    while (scanf("%64s %c%d,%d,%d,%d%c", read.id, &bOne, &read.sides[0], &read.sides[1], &read.sides[2], &read.sides[3], &bTwo) == 7 && bOne == '[' && bTwo == ']')
    {
        if (x->dominoLen == initialSize)
        {
            initialSize = initialSize * 2 + 1;
            x->dominos = (DOMINO *)realloc(x->dominos, initialSize * sizeof(DOMINO));
        }
        read.visited = 0;
        x->dominos[x->dominoLen] = read;
        (x->dominoLen)++;
    }
    if (!feof(stdin) || x->dominoLen == 0)
    {
        return 0;
    }
    return 1;
}

int equalDomino(DOMINO *a, DOMINO *b)
{
    if (a->sides[0] == b->sides[0] && a->sides[1] == b->sides[1] && a->sides[2] == b->sides[2] && a->sides[3] == b->sides[3])
        return 1;
    if (a->sides[0] == b->sides[3] && a->sides[1] == b->sides[0] && a->sides[2] == b->sides[1] && a->sides[3] == b->sides[2])
        return 1;
    if (a->sides[0] == b->sides[2] && a->sides[1] == b->sides[3] && a->sides[2] == b->sides[0] && a->sides[3] == b->sides[1])
        return 1;
    if (a->sides[0] == b->sides[1] && a->sides[1] == b->sides[2] && a->sides[2] == b->sides[3] && a->sides[3] == b->sides[0])
        return 1;
    return 0;
}

LIST *insert(LIST *head, int i, int j)
{
    LIST *newNode = (LIST *)malloc(sizeof(*newNode));
    newNode->index = i;
    newNode->equal = j;
    newNode->next = NULL;
    if (!head)
    {
        head = newNode;
        return head;
    }
    LIST *temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

void printDupes(LIST *head, ALL *x)
{
    LIST *temp = head;
    while (temp)
    {
        printf("%s", x->dominos[temp->index].id);
        LIST *dummy = temp;
        while (dummy)
        {
            if (dummy->index == temp->index)
            {
                printf(" = %s", x->dominos[dummy->equal].id);
            }
            dummy = dummy->next;
        }
        printf("\n");
        if (temp->index == temp->next->index && temp->next->next)
        {
            temp->next = temp->next->next;
        }
        else if (temp->index != temp->next->index)
        {
            temp = temp->next;
        }
        else
            break;
    }
}

void uniqueDominos(ALL *x)
{
    int unique = x->dominoLen;
    LIST *duplicates = NULL;
    for (int i = 0; i < x->dominoLen; ++i)
    {
        for (int j = i + 1; j < x->dominoLen; ++j)
        {
            if (equalDomino(&x->dominos[i], &x->dominos[j]) && x->dominos[j].visited == 0)
            {
                x->dominos[j].visited = 1;
                duplicates = insert(duplicates, i, j);
                unique--;
            }
        }
    }
    printf("Unique: %d\n", unique);
    printf("Duplicates: \n");
    printDupes(duplicates, x);
}

int main()
{
    ALL x;
    x.dominos = (DOMINO *)malloc(3 * sizeof(DOMINO));
    x.dominoLen = 0;
    if (!readInput(&x))
    {
        printf(INVALID);
        free(x.dominos);
        return 1;
    }
    uniqueDominos(&x);
    return 0;
}
