#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem *m_Next;
  char *m_Name;
  char m_Secret[24];
} TITEM;

#endif /* __PROGTEST__ */

/* ---implement the following functions:--- */

// newItem:
/*
This function is a helper function that eases the creation of a linked list. The function dynamically allocates the new item,
it initializes the fields, and finally, it returns the pointer to that newly created item.
Fields m_Next and m_Name must be initialized from the corresponding parameters, field m_Secret is to be filled with zero bytes ('\0').
*/

TITEM *newItem(const char *name, TITEM *next)
{
  TITEM *newNode = (TITEM *)malloc(sizeof(TITEM));

  newNode->m_Next = next;
  // using strdup to dynamically allocate space for the string and copy its contents
  // ! REMEMBER TO FREE THIS MEMORY !
  newNode->m_Name = strdup(name);
  // filling m_Secret with 0 bytes
  memset(newNode->m_Secret, 0, 24);
  return newNode;
}

// sortList:
/*
The function is used to sort the elements in the given linked list.
The parameter is a pointer to the first element of the list to sort (l) and the requested sort order (ascending).
The function re-arranges the elements in the list such that the elements follow the requested sort order.
The function must not free the elements in the original list (and return their copies). Instead, the function must use the existing elements,
it just needs to modify the links. Return value is the pointer to the first element of the newly re-arranged list.
The sorting uses element name (m_Name) as the sort key. The strings are compared in the case sensitive way.
The sort order is either ascending (parameter ascending is not zero), or the sort order is descending (parameter ascending is zero).
The function must perform stable sorting.
*/

// comparator function for sorting
int cmpA(const void *a, const void *b)
{
  const TITEM *x = (TITEM *)a, *y = (TITEM *)b;
  // compare the names of the items
  return strcmp(x->m_Name, y->m_Name);
}
int cmpD(const void *a, const void *b)
{
  const TITEM *x = (TITEM *)a, *y = (TITEM *)b;
  // compare the names of the items
  return -strcmp(x->m_Name, y->m_Name);
}

// merge two sorted lists
TITEM *merge(TITEM *a, TITEM *b, int (*cmp)(const void *, const void *))
{
  // create a new list and a pointer to the last item
  TITEM *l = NULL, *last = NULL;

  // merge the lists until one of them is empty
  while (a && b)
  {
    // compare the first items in the lists
    if (cmp(a, b) <= 0)
    {
      // add the item from the first list to the new list
      if (last)
        last->m_Next = a;
      else
        l = a;
      last = a;
      a = a->m_Next;
    }
    else
    {
      // add the item from the second list to the new list
      if (last)
        last->m_Next = b;
      else
        l = b;
      last = b;
      b = b->m_Next;
    }
  }

  // add the remaining items from the non-empty list
  if (a)
    last->m_Next = a;
  if (b)
    last->m_Next = b;

  // return the new list
  return l;
}

// sort a linked list using merge sort
TITEM *sortList(TITEM *l, int ascending)
{
  if (ascending)
  {
    // base case: the list has 0 or 1 items
    if (!l || !l->m_Next)
      return l;

    // split the list in two parts
    TITEM *a = l, *b = l->m_Next;
    while (b && b->m_Next)
    {
      a = a->m_Next;
      b = b->m_Next->m_Next;
    }
    b = a->m_Next;
    a->m_Next = NULL;

    // sort the two parts
    a = sortList(l, ascending);
    b = sortList(b, ascending);

    // merge the sorted parts
    return merge(a, b, cmpA);
  }
  else
  {
    // base case: the list has 0 or 1 items
    if (!l || !l->m_Next)
      return l;

    // split the list in two parts
    TITEM *a = l, *b = l->m_Next;
    while (b && b->m_Next)
    {
      a = a->m_Next;
      b = b->m_Next->m_Next;
    }
    b = a->m_Next;
    a->m_Next = NULL;

    // sort the two parts
    a = sortList(l, ascending);
    b = sortList(b, ascending);

    // merge the sorted parts
    return merge(a, b, cmpD);
  }

  return NULL;
}

// freeList:
/*
The function deallocates the memory used by the linked list.
The parameter is a pointer to the first element in the list.
*/

void freeList(TITEM *src)
{
  while (src)
  {
    TITEM *next = src->m_Next;
    free(src->m_Name);
    free(src);
    src = next;
  }
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
  TITEM *l;
  char tmp[50];

  assert(sizeof(TITEM) == sizeof(TITEM *) + sizeof(char *) + 24 * sizeof(char));
  l = NULL;
  l = newItem("PA1", l);
  l = newItem("PA2", l);
  l = newItem("UOS", l);
  l = newItem("LIN", l);
  l = newItem("AG1", l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "LIN"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "UOS"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortList(l, 1);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "LIN"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "UOS"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = newItem("programming and algorithmic I", l);
  l = newItem("AAG", l);
  assert(l && !strcmp(l->m_Name, "AAG"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "programming and algorithmic I"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "LIN"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "UOS"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortList(l, 0);
  assert(l && !strcmp(l->m_Name, "programming and algorithmic I"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "UOS"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "LIN"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "AAG"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  l = NULL;
  strncpy(tmp, "PA1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "PA2", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "UOS", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "LIN", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "AG1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "LIN"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "UOS"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortList(l, 1);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "LIN"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "UOS"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  strncpy(tmp, "programming and algorithmic I", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "AAG", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AAG"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "programming and algorithmic I"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "LIN"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "UOS"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortList(l, 0);
  assert(l && !strcmp(l->m_Name, "programming and algorithmic I"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "UOS"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "LIN"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "AAG"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
