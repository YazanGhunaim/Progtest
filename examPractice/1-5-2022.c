#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct Titem
{
  struct Titem *m_Next;
  char m_Digit;
} TITEM;

TITEM *createItem(char i, TITEM *next)
{
  TITEM *l = (TITEM *)malloc(sizeof(*l));
  l->m_Digit = i;
  l->m_Next = next;
  return l;
}
TITEM *createList(const char *x)
{
  int i = 0;
  TITEM *item = NULL;
  while (x[i])
  {
    item = createItem(x[i], item);
    i++;
  }
  return item;
}
void delList(TITEM *l)
{
  while (l)
  {
    TITEM *tmp = l->m_Next;
    free(l);
    l = tmp;
  }
}
#endif /* __PROGTEST__ */

int validList(TITEM *head)
{
  if (!head)
    return 0;
  TITEM *temp = head;
  while (temp)
  {
    if (!isdigit(temp->m_Digit))
      return 0;
    temp = temp->m_Next;
  }
  return 1;
}

int validArray(TITEM **array, int size)
{
  for (int i = 0; i < size; ++i)
  {
    if (!validList(array[i]))
      return 0;
  }
  return 1;
}

TITEM *reverse(TITEM *head)
{
  TITEM *current, *prev, *next;
  current = head;
  prev = next = NULL;

  while (current)
  {
    next = current->m_Next;
    current->m_Next = prev;
    prev = current;
    current = next;
  }
  return prev;
}

TITEM **reverseArray(TITEM **array, int size)
{
  for (int i = 0; i < size; ++i)
  {
    array[i] = reverse(array[i]);
  }
  return array;
}

int length(TITEM *head)
{
  int length = 0;
  TITEM *temp = head;
  while (temp)
  {
    length++;
    temp = temp->m_Next;
  }
  return length;
}

int compareList(TITEM *l1, TITEM *l2)
{
  TITEM *temp1, *temp2;
  temp1 = l1;
  temp2 = l2;

  while (temp1 && temp2)
  {
    if (temp1->m_Digit > temp2->m_Digit)
      return 1;
    if (temp1->m_Digit < temp2->m_Digit)
      return -1;
    temp1 = temp1->m_Next;
    temp2 = temp2->m_Next;
  }
  return 0;
}

TITEM *getResult(TITEM **array, int size)
{
  TITEM *max = array[0];
  for (int i = 1; i < size; ++i)
  {
    if (length(array[i]) > length(max))
      max = array[i];
    if (length(array[i]) == length(max))
    {
      if (compareList(array[i], max) == 1)
        max = array[i];
    }
  }
  return max;
}

TITEM *maxOf(TITEM **x, int nr)
{
  if (!validArray(x, nr))
    return NULL;

  x = reverseArray(x, nr);
  TITEM *result = getResult(x, nr);
  return result;
}

#ifndef __PROGTEST__
int main(void)
{

  TITEM *a[5];
  TITEM *res;

  //----- Basic test ------------------------------------------ -----
  a[0] = createList("191");
  a[1] = createList("113");
  a[2] = createList("197");
  res = maxOf(a, 3);
  assert(res == a[2]);

  for (int i = 0; i < 3; i++)
    delList(a[i]);

  //----- Ordinal higher number ---------------------------------------- -
  a[0] = createList("313");
  a[1] = createList("1191");
  a[2] = createList("997");
  res = maxOf(a, 3);

  assert(res == a[1]);

  for (int i = 0; i < 3; i++)
    delList(a[i]);

  //----- Bad input ------------------------------------------ ------
  a[0] = createList("222");
  a[1] = NULL;
  a[2] = createList("4333");
  a[3] = createList("1");
  res = maxOf(a, 4);

  assert(res == NULL);

  for (int i = 0; i < 4; i++)
    delList(a[i]);

  //----- Bad value ----------------------------------------- ----
  a[0] = createList("29a");
  a[1] = createList("11");
  res = maxOf(a, 2);

  assert(res == NULL);

  for (int i = 0; i < 2; i++)
    delList(a[i]);

  // //----- Same number ----------------------------------------- ------
  a[0] = createList("27986");
  a[1] = createList("3256");
  a[2] = createList("27986");
  a[3] = createList("17000");
  res = maxOf(a, 4);

  assert(res == a[0]);

  for (int i = 0; i < 4; i++)
    delList(a[i]);

  //----- Zero ---------------------------------------------------- -------------
  a[0] = createList("0");
  a[1] = createList("0");
  a[2] = createList("0");
  a[3] = createList("0");
  a[4] = createList("0");
  res = maxOf(a, 5);

  assert(res == a[0]);

  for (int i = 0; i < 5; i++)
    delList(a[i]);

  //----- Unsigned Long Long Int ------------------------------------
  a[0] = createList("0");
  a[1] = createList("18446744073709551615");
  a[2] = createList("1112367822345622");
  a[3] = createList("9991234530632948235");
  a[4] = createList("1213004921032");
  res = maxOf(a, 5);

  assert(res == a[1]);

  for (int i = 0; i < 5; i++)
    delList(a[i]);

  //----- More like Unsigned Long Long Int ----------------------------
  a[0] = createList("50230529401950984100481491404914091408580");
  a[1] = createList("50230529401950123123123234492492042044242");
  a[2] = createList("50230529401950984100480123032931110119944");
  a[3] = createList("50230529401950123123123234492400000000000");
  a[4] = createList("50230531000000000000000000000000000000000");
  res = maxOf(a, 5);

  assert(res == a[4]);

  for (int i = 0; i < 5; i++)
    delList(a[i]);

  //----- Greater than Unsigned Long Long Int different long --------------
  a[0] = createList("253051330239013091349049023023");
  a[1] = createList("253051330239013091349049023024");
  a[2] = createList("2094241212100000000000100100");
  a[3] = createList("999919103904248923023");
  a[4] = createList("9999999999999999999999999999");
  res = maxOf(a, 5);

  assert(res == a[1]);

  for (int i = 0; i < 5; i++)
    delList(a[i]);
  return 0;
}
#endif /* __PROGTEST__ */
