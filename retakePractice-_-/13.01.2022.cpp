#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
    struct TItem *m_Next;
    char m_Digit;
} TITEM;

TITEM *createItem(char digit, TITEM *next)
{
    TITEM *n = (TITEM *)malloc(sizeof(*n));
    n->m_Digit = digit;
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

int valid(TITEM *head)
{
    int total = 0;
    TITEM *temp = head;
    while (temp->m_Next)
    {
        total++;
        if (!temp || !isdigit(temp->m_Digit))
            return 0;
        temp = temp->m_Next;
    }
    if (!isdigit(temp->m_Digit) || (temp->m_Digit == '0' && total > 0))
        return 0;
    return 1;
}

TITEM *addList(TITEM *l1, TITEM *l2)
{
    if (!valid(l1) || !valid(l2))
        return NULL;
    if (!l1)
        return l2;
    if (!l2)
        return l1;

    int carry = 0;
    int currentSum = 0;

    TITEM *newList = (TITEM *)malloc(sizeof(*newList));
    TITEM *dummy = newList;

    while (l1 || l2)
    {
        int l1_Val = (l1) ? l1->m_Digit - '0' : 0;
        int l2_Val = (l2) ? l2->m_Digit - '0' : 0;

        int carry = currentSum / 10;
        currentSum = l1_Val + l2_Val + carry;
        int lastDigit = currentSum % 10;

        TITEM *newNode = (TITEM *)malloc(sizeof(*newNode));
        newNode->m_Digit = lastDigit + '0';
        newNode->m_Next = NULL;
        dummy->m_Next = newNode;
        dummy = dummy->m_Next;
        if (l1)
            l1 = l1->m_Next;
        if (l2)
            l2 = l2->m_Next;
    }
    if (carry)
    {
        TITEM *newNode = (TITEM *)malloc(sizeof(*newNode));
        newNode->m_Digit = carry + '0';
        newNode->m_Next = NULL;
        dummy->m_Next = newNode;
        dummy = dummy->m_Next;
    }
    return newList->m_Next;
}

#ifndef __PROGTEST__

int main(int argc, char *argv[])
{
    TITEM *a, *b, *res;

    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('5', createItem('0', createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('5', createItem('2', createItem('2', NULL)));
    b = createItem('3', createItem('9', NULL));
    res = addList(a, b);
    assert(res->m_Digit == '8');
    assert(res->m_Next->m_Digit == '1');
    assert(res->m_Next->m_Next->m_Digit == '3');
    assert(res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('3', createItem('4', createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    assert(res->m_Digit == '3');
    assert(res->m_Next->m_Digit == '4');
    assert(res->m_Next->m_Next->m_Digit == '5');
    assert(res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);
    return 0;
}

#endif /* __PROGTEST__ */
