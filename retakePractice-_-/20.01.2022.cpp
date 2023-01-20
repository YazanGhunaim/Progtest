#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
    struct TItem *m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;

TITEM *createItem(int mul, int pow, TITEM *next)
{
    TITEM *n = (TITEM *)malloc(sizeof(*n));
    n->m_Mul = mul;
    n->m_Pow = pow;
    n->m_Next = next;
    return n;
}

void deleteList(TITEM *l)
{
    while (l)
    {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

int valid(TITEM *a)
{
    if (!a)
        return 0;
    TITEM *temp = a;
    while (temp->m_Next)
    {
        if (temp->m_Mul == 0)
            return 0;
        if (temp->m_Pow >= temp->m_Next->m_Pow)
            return 0;
        temp = temp->m_Next;
    }
    return 1;
}

TITEM *addPoly(TITEM *a, TITEM *b)
{
    if (!valid(a) || !valid(b))
        return NULL;
    if (!a)
        return b;
    if (!b)
        return a;

    TITEM *newList = (TITEM *)malloc(sizeof(*newList));
    TITEM *dummy = newList;

    int sum = 0;
    int pow = 0;
    int total = 0;
    while (a && b)
    {
        if (a->m_Pow > b->m_Pow)
        {
            sum = a->m_Mul;
            pow = a->m_Pow;
            a = a->m_Next;
        }
        else if (a->m_Pow < b->m_Pow)
        {
            sum = b->m_Mul;
            pow = b->m_Pow;
            b = b->m_Next;
        }
        else
        {
            sum = a->m_Mul + b->m_Mul;
            pow = a->m_Pow;
            a = a->m_Next;
            b = b->m_Next;
        }
        if (sum)
        {
            total++;
            TITEM *newNode = (TITEM *)malloc(sizeof(*newNode));
            newNode->m_Pow = pow;
            newNode->m_Mul = sum;
            newNode->m_Next = NULL;
            dummy->m_Next = newNode;
            dummy = dummy->m_Next;
        }
    }
    if (total)
        return newList->m_Next;
    TITEM *newNode = (TITEM *)malloc(sizeof(*newNode));
    newNode->m_Mul = 0;
    newNode->m_Pow = 0;
    newNode->m_Next = NULL;
    dummy->m_Next = newNode;
    dummy = dummy->m_Next;

    return newList->m_Next;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    TITEM *a, *b;
    TITEM *res;

    a = createItem(2, 1, NULL);
    b = createItem(0, 0, NULL);
    res = addPoly(a, b);
    assert(res->m_Mul == 2);
    assert(res->m_Pow == 1);
    assert(res->m_Next == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(2, 1, NULL);
    b = createItem(3, 1, createItem(4, 2, createItem(2, 3, createItem(1, 0, NULL))));

    res = addPoly(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(2, 1, NULL);
    b = createItem(3, 1, createItem(4, 1, NULL));
    res = addPoly(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(3, 0, createItem(2, 1, createItem(9, 3, NULL)));
    b = createItem(0, 0, createItem(4, 2, createItem(-1, 3, NULL)));
    res = addPoly(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(3, 0, createItem(2, 1, createItem(5, 3, NULL)));
    b = createItem(-7, 0, createItem(-2, 1, createItem(-5, 3, NULL)));
    res = addPoly(a, b);
    assert(res->m_Mul == -4);
    assert(res->m_Pow == 0);
    assert(res->m_Next == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(3, 1, createItem(-2, 2, createItem(4, 3, NULL)));
    b = createItem(-3, 1, createItem(2, 2, createItem(-4, 3, NULL)));
    res = addPoly(a, b);
    assert(res->m_Mul == 0);
    assert(res->m_Pow == 0);
    assert(res->m_Next == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    return 0;
}
#endif /* __PROGTEST__ */
