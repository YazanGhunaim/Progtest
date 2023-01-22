#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct TResult
{
    struct TResult *m_Next;
    int m_ID;
    char *m_Name;
} TRESULT;
#endif /* __PROGTEST__ */

typedef struct TDatabase
{
    int id1;
    int id2;
    TRESULT *person;
    struct TDatabase *next;
} TDATABASE;

void initAll(TDATABASE *db)
{
    db->id1 = db->id2 = 0;
    db->next = NULL;
    db->person = NULL;
}

void freeResult(TRESULT *res)
{
    while (res)
    {
        TRESULT *next = res->m_Next;
        free(res->m_Name);
        free(res);
        res = next;
    }
}

void doneAll(TDATABASE *db)
{
    TDATABASE *temp = db->next;
    while (temp)
    {
        TDATABASE *next = temp->next;
        free(temp->person->m_Name);
        free(temp->person);
        free(temp);
        temp = next;
    }
}

int existingID(TDATABASE *db, int id)
{
    TDATABASE *temp = db->next;
    while (temp)
    {
        if (temp->person->m_ID == id)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int uniqueID(TDATABASE *db, int id)
{
    TDATABASE *temp = db->next;
    while (temp)
    {
        if (temp->person->m_ID == id)
            return 0;
        temp = temp->next;
    }
    return 1;
}

int addPerson(TDATABASE *db, int id, const char *name, int id1, int id2)
{
    if (id == 0 || !uniqueID(db, id))
        return 0;

    if ((id1 == id2 && id1 > 0 && id2 > 0))
        return 0;

    if (id1 > 0 && id2 > 0 && (!existingID(db, id1) || !existingID(db, id2)))
        return 0;

    TDATABASE *newNode = (TDATABASE *)malloc(sizeof(*newNode));
    newNode->id1 = id1;
    newNode->id2 = id2;
    newNode->next = NULL;
    newNode->person = (TRESULT *)malloc(sizeof(TRESULT));
    newNode->person->m_ID = id;
    newNode->person->m_Name = strdup(name);
    newNode->person->m_Next = NULL;

    if (db->next == NULL)
    {
        db->next = newNode;
        return 1;
    }
    TDATABASE *temp = db->next;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;

    return 1;
}

void getParents(TDATABASE *db, int id, int *id1, int *id2)
{
    TDATABASE *temp = db->next;
    while (temp->person->m_ID != id)
        temp = temp->next;

    *id1 = temp->id1;
    *id2 = temp->id2;
}

TRESULT *getPerson(TDATABASE *db, int id)
{
    if (id == 0)
        return NULL;
    TDATABASE *temp = db->next;
    while (temp->person->m_ID != id)
        temp = temp->next;

    return temp->person;
}

TRESULT *insert(TDATABASE *db, TRESULT *head, int id)
{
    if (id == 0)
        return head;
    TRESULT *newNode = (TRESULT *)malloc(sizeof(*newNode));
    TRESULT *person = getPerson(db, id);
    if (!person)
        return head;
    newNode->m_Name = strdup(person->m_Name);
    newNode->m_ID = person->m_ID;
    newNode->m_Next = NULL;

    if (!head)
    {
        head = newNode;
        return head;
    }
    TRESULT *temp = head;
    while (temp->m_Next)
    {
        temp = temp->m_Next;
    }
    temp->m_Next = newNode;
    return head;
}

// ------------------------------
TRESULT *merge(TRESULT *l1, TRESULT *l2)
{
    if (!l1 && !l2)
        return NULL;
    if (!l1)
        return l2;
    if (!l2)
        return l1;

    TRESULT *newList = (TRESULT *)malloc(sizeof(*newList));
    TRESULT *dummy = newList;

    while (l1 && l2)
    {
        if (l1->m_ID < l2->m_ID)
        {
            dummy->m_Next = l1;
            l1 = l1->m_Next;
        }
        else
        {
            dummy->m_Next = l2;
            l2 = l2->m_Next;
        }
        dummy = dummy->m_Next;
    }

    if (l1)
        dummy->m_Next = l1;
    if (l2)
        dummy->m_Next = l2;

    return newList->m_Next;
}
TRESULT *mergesort(TRESULT *head)
{
    if (!head || !head->m_Next)
        return head;

    TRESULT *prev, *slow, *fast;
    slow = fast = head;
    prev = NULL;
    while (fast && fast->m_Next)
    {
        prev = slow;
        slow = slow->m_Next;
        fast = fast->m_Next->m_Next;
    }
    prev->m_Next = NULL;
    TRESULT *l1 = mergesort(head);
    TRESULT *l2 = mergesort(slow);
    return merge(l1, l2);
}
// ------------------------------

TRESULT *removeDupes(TRESULT *head)
{
    if (!head || !head->m_Next)
        return head;

    TRESULT *temp = head;
    while (temp->m_Next)
    {
        if (temp->m_ID == temp->m_Next->m_ID)
        {
            TRESULT *freeNode = temp->m_Next;
            if (temp->m_Next->m_Next)
            {
                temp->m_Next = temp->m_Next->m_Next;
            }
            else
            {
                temp->m_Next = NULL;
            }
            free(freeNode);
        }
        else
        {
            temp = temp->m_Next;
        }
    }
    return head;
}

TRESULT *ancestors(TDATABASE *db, int id)
{

    if (!existingID(db, id) || !db->next)
        return NULL;

    int id1, id2;
    TRESULT *newList = NULL;
    getParents(db, id, &id1, &id2);
    newList = insert(db, newList, id1);
    newList = insert(db, newList, id2);

    TRESULT *dummy = newList;
    while (dummy)
    {
        getParents(db, dummy->m_ID, &id1, &id2);
        newList = insert(db, newList, id1);
        newList = insert(db, newList, id2);
        dummy = dummy->m_Next;
    }

    newList = mergesort(newList);
    return removeDupes(newList);
}
TRESULT *commonAncestors(TDATABASE *db, int id1, int id2)
{
    if (id1 == 0 || id2 == 0 || !existingID(db, id1) || !existingID(db, id2))
        return NULL;
    TRESULT *one = ancestors(db, id1);
    TRESULT *tempOne = one;
    TRESULT *two = ancestors(db, id2);
    TRESULT *tempTwo = two;

    TRESULT *newList = NULL;
    while (tempOne)
    {
        tempTwo = two;
        while (tempTwo)
        {
            if (tempTwo->m_ID == tempOne->m_ID)
            {
                newList = insert(db, newList, tempOne->m_ID);
            }
            tempTwo = tempTwo->m_Next;
        }
        tempOne = tempOne->m_Next;
    }
    freeResult(one);
    freeResult(two);
    return removeDupes(newList);
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    char name[100];
    TDATABASE a, b;
    TRESULT *l;

    initAll(&a);
    assert(addPerson(&a, 1, "John", 0, 0) == 1);
    strncpy(name, "Jane", sizeof(name));
    assert(addPerson(&a, 2, name, 0, 0) == 1);
    assert(addPerson(&a, 3, "Caroline", 0, 0) == 1);
    assert(addPerson(&a, 4, "Peter", 0, 0) == 1);
    assert(addPerson(&a, 5, "George", 1, 2) == 1);
    assert(addPerson(&a, 6, "Martin", 1, 2) == 1);
    assert(addPerson(&a, 7, "John", 3, 4) == 1);
    assert(addPerson(&a, 8, "Sandra", 3, 4) == 1);
    assert(addPerson(&a, 9, "Eve", 1, 2) == 1);
    assert(addPerson(&a, 10, "Douglas", 1, 4) == 1);
    strncpy(name, "Phillipe", sizeof(name));
    assert(addPerson(&a, 11, name, 6, 8) == 1);
    strncpy(name, "Maria", sizeof(name));
    assert(addPerson(&a, 12, name, 5, 8) == 1);
    l = ancestors(&a, 11);
    assert(l);
    assert(l->m_ID == 1);
    assert(!strcmp(l->m_Name, "John"));
    assert(l->m_Next);
    assert(l->m_Next->m_ID == 2);
    assert(!strcmp(l->m_Next->m_Name, "Jane"));
    assert(l->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_ID == 3);
    assert(!strcmp(l->m_Next->m_Next->m_Name, "Caroline"));
    assert(l->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_ID == 4);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Name, "Peter"));
    assert(l->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_ID == 6);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "Martin"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_ID == 8);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Sandra"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    freeResult(l);
    assert(ancestors(&a, 3) == NULL);
    assert(ancestors(&a, 13) == NULL);
    l = commonAncestors(&a, 11, 12);
    assert(l);
    assert(l->m_ID == 1);
    assert(!strcmp(l->m_Name, "John"));
    assert(l->m_Next);
    assert(l->m_Next->m_ID == 2);
    assert(!strcmp(l->m_Next->m_Name, "Jane"));
    assert(l->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_ID == 3);
    assert(!strcmp(l->m_Next->m_Next->m_Name, "Caroline"));
    assert(l->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_ID == 4);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Name, "Peter"));
    assert(l->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_ID == 8);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "Sandra"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    freeResult(l);
    l = commonAncestors(&a, 10, 9);
    assert(l);
    assert(l->m_ID == 1);
    assert(!strcmp(l->m_Name, "John"));
    assert(l->m_Next == NULL);
    freeResult(l);
    assert(commonAncestors(&a, 7, 6) == NULL);
    l = commonAncestors(&a, 7, 10);
    assert(l);
    assert(l->m_ID == 4);
    assert(!strcmp(l->m_Name, "Peter"));
    assert(l->m_Next == NULL);
    freeResult(l);
    assert(addPerson(&a, 13, "Quido", 12, 11) == 1);
    l = ancestors(&a, 13);
    assert(l);
    assert(l->m_ID == 1);
    assert(!strcmp(l->m_Name, "John"));
    assert(l->m_Next);
    assert(l->m_Next->m_ID == 2);
    assert(!strcmp(l->m_Next->m_Name, "Jane"));
    assert(l->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_ID == 3);
    assert(!strcmp(l->m_Next->m_Next->m_Name, "Caroline"));
    assert(l->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_ID == 4);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Name, "Peter"));
    assert(l->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_ID == 5);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "George"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_ID == 6);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Martin"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_ID == 8);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Sandra"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_ID == 11);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Phillipe"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_ID == 12);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Maria"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    freeResult(l);
    l = commonAncestors(&a, 9, 12);
    assert(l);
    assert(l->m_ID == 1);
    assert(!strcmp(l->m_Name, "John"));
    assert(l->m_Next);
    assert(l->m_Next->m_ID == 2);
    assert(!strcmp(l->m_Next->m_Name, "Jane"));
    assert(l->m_Next->m_Next == NULL);
    freeResult(l);
    assert(addPerson(&a, 1, "Francois", 0, 0) == 0);
    initAll(&b);
    assert(addPerson(&b, 10000, "John", 0, 0) == 1);
    assert(addPerson(&b, 10000, "Peter", 0, 0) == 0);
    assert(addPerson(&b, 20000, "Jane", 10000, 0) == 1);
    assert(addPerson(&b, 30000, "Maria", 10000, 10000) == 0);
    assert(addPerson(&b, 40000, "Joe", 10000, 30000) == 0);
    assert(addPerson(&b, 50000, "Carol", 50000, 20000) == 0);
    assert(addPerson(&b, 12, "Maria", 20000, 10000) == 1);
    l = ancestors(&a, 12);
    assert(l);
    assert(l->m_ID == 1);
    assert(!strcmp(l->m_Name, "John"));
    assert(l->m_Next);
    assert(l->m_Next->m_ID == 2);
    assert(!strcmp(l->m_Next->m_Name, "Jane"));
    assert(l->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_ID == 3);
    assert(!strcmp(l->m_Next->m_Next->m_Name, "Caroline"));
    assert(l->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_ID == 4);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Name, "Peter"));
    assert(l->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_ID == 5);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "George"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next);
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_ID == 8);
    assert(!strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Sandra"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    freeResult(l);
    l = ancestors(&b, 12);
    assert(l);
    assert(l->m_ID == 10000);
    assert(!strcmp(l->m_Name, "John"));
    assert(l->m_Next);
    assert(l->m_Next->m_ID == 20000);
    assert(!strcmp(l->m_Next->m_Name, "Jane"));
    assert(l->m_Next->m_Next == NULL);
    freeResult(l);
    assert(ancestors(&a, 20000) == NULL);
    assert(commonAncestors(&b, 7, 10) == NULL);
    doneAll(&b);

    doneAll(&a);

    return 0;
}
#endif /* __PROGTEST__ */
