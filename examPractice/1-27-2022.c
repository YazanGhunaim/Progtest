#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct tnode
{
  struct tnode *m_Next;
  int m_Val;
} Tnode;

Tnode *createItem(int i, Tnode *next)
{
  Tnode *l = (Tnode *)malloc(sizeof(*l));
  l->m_Val = i;
  l->m_Next = next;
  return l;
}
void delList(Tnode *l)
{
  if (l != NULL)
    delList(l->m_Next);
  free(l);
}
#endif /* __PROGTEST__ */

int totalSize(Tnode **a, int nr)
{
  int length = 0;
  for (int i = 0; i < nr; ++i)
  {
    Tnode *temp = a[i];
    while (temp)
    {
      length++;
      temp = temp->m_Next;
    }
  }
  return length;
}

void fillArray(int *array, Tnode **a, int nr)
{
  int j = 0;
  for (int i = 0; i < nr; ++i)
  {
    Tnode *temp = a[i];
    while (temp)
    {
      array[j++] = temp->m_Val;
      temp = temp->m_Next;
    }
  }
}

int cmp(const int *a, const int *b)
{
  return (*b < *a) - (*a < *b);
}

void insert(Tnode **head, int value)
{
  Tnode *newNode = (Tnode *)malloc(sizeof(*newNode));
  newNode->m_Val = value;
  newNode->m_Next = NULL;

  if (!*head)
    *head = newNode;
  else
  {
    Tnode *temp = *head;
    while (temp->m_Next)
      temp = temp->m_Next;

    temp->m_Next = newNode;
  }
}

Tnode *arrayToList(int *array, int size)
{
  Tnode *head = NULL;
  for (int i = 0; i < size; ++i)
    insert(&head, array[i]);

  return head;
}

int validCheck(Tnode **a, int nr)
{
  for (int i = 0; i < nr; ++i)
  {
    Tnode *temp = a[i];
    while (temp->m_Next)
    {
      if (temp->m_Val > temp->m_Next->m_Val || !temp)
        return 0;
      temp = temp->m_Next;
    }
  }
  return 1;
}

Tnode *compareList(Tnode **a, int nr)
{
  if (!validCheck(a, nr))
    return NULL;

  int size = totalSize(a, nr);
  int *array = (int *)malloc(sizeof(*array) * size);

  fillArray(array, a, nr);
  qsort(array, size, sizeof(array[0]), (int (*)(const void *, const void *))cmp);

  Tnode *result = arrayToList(array, size);
  free(array);

  return result;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{

  Tnode *a[5];
  Tnode *res;

  a[0] = createItem(3,
                    createItem(4,
                               createItem(5, NULL)));
  a[1] = createItem(1,
                    createItem(2,
                               createItem(6,
                                          createItem(7,
                                                     createItem(8,
                                                                createItem(9, NULL))))));

  res = compareList(a, 2);

  assert(res->m_Val == 1);
  assert(res->m_Next->m_Val == 2);
  assert(res->m_Next->m_Next->m_Val == 3);
  assert(res->m_Next->m_Next->m_Next->m_Val == 4);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 5);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 6);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 7);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 8);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 9);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);

  delList(res);
  for (int i = 0; i < 2; i++)
  {
    delList(a[i]);
  }

  a[0] = createItem(1,
                    createItem(7,
                               createItem(24, NULL)));
  a[1] = createItem(3,
                    createItem(5,
                               createItem(17, NULL)));
  a[2] = createItem(-3,
                    createItem(19, NULL));
  res = compareList(a, 3);

  assert(res->m_Val == -3);
  assert(res->m_Next->m_Val == 1);
  assert(res->m_Next->m_Next->m_Val == 3);
  assert(res->m_Next->m_Next->m_Next->m_Val == 5);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 7);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 17);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 19);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 24);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);

  delList(res);
  for (int i = 0; i < 3; i++)
  {
    delList(a[i]);
  }

  a[0] = createItem(15,
                    createItem(19,
                               createItem(23,
                                          createItem(192, NULL))));

  a[1] = createItem(17,
                    createItem(18,
                               createItem(18,
                                          createItem(21, NULL))));
  a[2] = createItem(-3,
                    createItem(19, NULL));
  res = compareList(a, 3);

  assert(res->m_Val == -3);
  assert(res->m_Next->m_Val == 15);
  assert(res->m_Next->m_Next->m_Val == 17);
  assert(res->m_Next->m_Next->m_Next->m_Val == 18);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 18);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 19);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 19);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 21);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 23);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 192);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);

  delList(res);
  for (int i = 0; i < 3; i++)
  {
    delList(a[i]);
  }

  a[0] = createItem(-4,
                    createItem(2,
                               createItem(4,
                                          createItem(7, NULL))));

  a[1] = createItem(12,
                    createItem(18,
                               createItem(20, NULL)));
  a[2] = createItem(-6,
                    createItem(3,
                               createItem(4,
                                          createItem(11,
                                                     createItem(14,
                                                                createItem(15,
                                                                           createItem(19, NULL)))))));

  res = compareList(a, 3);

  int sent[] = {-6, -4, 2, 3, 4, 4, 7, 11, 12, 14, 15, 18, 19, 20};
  Tnode *test = res;
  for (int i = 0; i < 14; i++)
  {
    assert(test->m_Val == sent[i]);
    test = test->m_Next;
  }
  assert(test == NULL);

  delList(res);
  for (int i = 0; i < 3; i++)
  {
    delList(a[i]);
  }

  a[0] = createItem(-4,
                    createItem(2,
                               createItem(4,
                                          createItem(7, NULL))));

  a[1] = createItem(12,
                    createItem(18,
                               createItem(20, NULL)));
  a[2] = createItem(-6,
                    createItem(3,
                               createItem(4,
                                          createItem(11,
                                                     createItem(1,
                                                                createItem(15,
                                                                           createItem(19, NULL)))))));

  res = compareList(a, 3);

  assert(res == NULL);

  delList(res);
  for (int i = 0; i < 3; i++)
  {
    delList(a[i]);
  }

  a[0] = createItem(-4,
                    createItem(2,
                               createItem(4,
                                          createItem(7, NULL))));

  a[1] = createItem(12, NULL);
  a[2] = createItem(3, NULL);
  res = compareList(a, 3);

  assert(res->m_Val == -4);
  assert(res->m_Next->m_Val == 2);
  assert(res->m_Next->m_Next->m_Val == 3);
  assert(res->m_Next->m_Next->m_Next->m_Val == 4);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 7);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 12);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);

  delList(res);
  for (int i = 0; i < 3; i++)
  {
    delList(a[i]);
  }

  a[0] = createItem(15,
                    createItem(19,
                               createItem(19,
                                          createItem(2, NULL))));

  a[1] = createItem(17,
                    createItem(18,
                               createItem(18,
                                          createItem(21, NULL))));
  res = compareList(a, 2);
  assert(res == NULL);
  delList(res);
  for (int i = 0; i < 2; i++)
  {
    delList(a[i]);
  }

  a[0] = createItem(15,
                    createItem(19,
                               createItem(19,
                                          createItem(2, NULL))));

  a[1] = NULL;
  a[2] = createItem(-2,
                    createItem(1,
                               createItem(10,
                                          createItem(11, NULL))));

  res = compareList(a, 3);
  assert(res == NULL);
  delList(res);
  for (int i = 0; i < 3; i++)
  {
    delList(a[i

    ]);
  }

  a[0] = createItem(5, NULL);
  a[1] = createItem(1, NULL);
  a[2] = createItem(-2, NULL);
  a[3] = createItem(69, NULL);
  a[4] = createItem(4, NULL);

  res = compareList(a, 5);

  assert(res->m_Val == -2);
  assert(res->m_Next->m_Val == 1);
  assert(res->m_Next->m_Next->m_Val == 4);
  assert(res->m_Next->m_Next->m_Next->m_Val == 5);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 69);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);

  delList(res);
  for (int i = 0; i < 5; i++)
  {
    delList(a[i]);
  }

  return 0;
}
#endif /* __PROGTEST__ */
