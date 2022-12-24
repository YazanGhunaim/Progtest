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

int cmpName(const TITEM *a, const TITEM *b)
{
  return strcmp(a->m_Name, b->m_Name);
}

int cmpNameInsensitive(const TITEM *a, const TITEM *b)
{
  return strcasecmp(a->m_Name, b->m_Name);
}

int cmpNameLen(const TITEM *a, const TITEM *b)
{
  size_t la = strlen(a->m_Name), lb = strlen(b->m_Name);
  return (lb < la) - (la < lb);
}
#endif /* __PROGTEST__ */

TITEM *newItem(const char *name, TITEM *next)
{
  TITEM *newItem = (TITEM *)malloc(sizeof(*newItem));
  newItem->m_Name = strdup(name);
  memset(newItem->m_Secret, 0, 24);
  newItem->m_Next = next;

  return newItem;
}

TITEM *merge(TITEM *l1, TITEM *l2, int (*cmpFn)(const TITEM *, const TITEM *))
{
  if (!l1)
    return l2;
  if (!l2)
    return l1;

  TITEM *newList = (TITEM *)malloc(sizeof(*newList));
  TITEM *temp = newList;

  while (l1 && l2)
  {
    if (cmpFn(l1, l2) > 0)
    {
      temp->m_Next = l2;
      l2 = l2->m_Next;
    }
    else
    {
      temp->m_Next = l1;
      l1 = l1->m_Next;
    }
    temp = temp->m_Next;
  }

  if (l1)
    temp->m_Next = l1;
  if (l2)
    temp->m_Next = l2;

  return newList->m_Next;
}

TITEM *mergeDecreasing(TITEM *l1, TITEM *l2, int (*cmpFn)(const TITEM *, const TITEM *))
{
  if (!l1)
    return l2;
  if (!l2)
    return l1;

  TITEM *newList = (TITEM *)malloc(sizeof(*newList));
  TITEM *temp = newList;

  while (l1 && l2)
  {
    if (cmpFn(l1, l2) < 0)
    {
      temp->m_Next = l2;
      l2 = l2->m_Next;
    }
    else
    {
      temp->m_Next = l1;
      l1 = l1->m_Next;
    }
    temp = temp->m_Next;
  }

  if (l1)
    temp->m_Next = l1;
  if (l2)
    temp->m_Next = l2;

  return newList->m_Next;
}

TITEM *sortListCmp(TITEM *l, int ascending, int (*cmpFn)(const TITEM *, const TITEM *))
{

  if (ascending)
  {
    if (!l || !l->m_Next)
      return l;

    // split list to two halves
    TITEM *slow, *fast, *prev;
    prev = NULL;
    slow = fast = l;

    while (fast && fast->m_Next)
    {
      prev = slow;
      slow = slow->m_Next;
      fast = fast->m_Next->m_Next;
    }
    prev->m_Next = NULL;

    // first_half = l
    // second_half = slow
    l = sortListCmp(l, ascending, cmpFn);
    slow = sortListCmp(slow, ascending, cmpFn);

    return merge(l, slow, cmpFn);
  }
  else
  {
    if (!l || !l->m_Next)
      return l;

    // split list to two halves
    TITEM *slow, *fast, *prev;
    prev = NULL;
    slow = fast = l;

    while (fast && fast->m_Next)
    {
      prev = slow;
      slow = slow->m_Next;
      fast = fast->m_Next->m_Next;
    }
    prev->m_Next = NULL;

    // first_half = l
    // second_half = slow
    l = sortListCmp(l, ascending, cmpFn);
    slow = sortListCmp(slow, ascending, cmpFn);

    return mergeDecreasing(l, slow, cmpFn);
  }
  return NULL;
}
void freeList(TITEM *src)
{
  while (src)
  {
    TITEM *temp = src->m_Next;
    free(src->m_Name);
    free(src);
    src = temp;
  }
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
  TITEM *l;
  char tmp[50];

  assert(sizeof(TITEM) == sizeof(TITEM *) + sizeof(char *) + 24 * sizeof(char));
  l = NULL;
  l = newItem("BI-PA1", l);
  l = newItem("BIE-PA2", l);
  l = newItem("NI-PAR", l);
  l = newItem("lin", l);
  l = newItem("AG1", l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpName);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameInsensitive);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = newItem("AAG.3", l);
  assert(l && !strcmp(l->m_Name, "AAG.3"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 0, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "BIE-PA2"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  l = NULL;
  strncpy(tmp, "BI-PA1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "BIE-PA2", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "NI-PAR", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "lin", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "AG1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpName);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameInsensitive);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  strncpy(tmp, "AAG.3", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AAG.3"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 0, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "BIE-PA2"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
