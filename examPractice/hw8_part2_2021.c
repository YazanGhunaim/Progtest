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
  db->id1 = 0;
  db->id2 = 0;
  db->person = NULL;
  db->next = NULL;
}

int uniqueID(TDATABASE *db, int id)
{
  if (!db)
    return 0;
  TDATABASE *dummy = db;
  while (dummy)
  {
    if (dummy->person && dummy->person->m_ID == id)
      return 0;
    dummy = dummy->next;
  }
  return 1;
}

int existingID(TDATABASE *db, int id)
{
  if (!db)
    return 0;
  TDATABASE *current = db;
  while (current)
  {
    if (current->person && current->person->m_ID == id)
      return 1;

    current = current->next;
  }
  return 0;
}

int addPerson(TDATABASE *db, int id, const char *name, int id1, int id2)
{
  // if id is non zero or the id is not of a unique person in the database
  if (id == 0 || !uniqueID(db, id))
    return 0;
  // parent ID is either 0 (the parent is not known) or non-zero (identifying a known person in the database)
  if (!(id1 >= 0) || !(id2 >= 0))
    return 0;
  // parent #1 and parent #2 must not be the same person.
  if ((id1 == id2) && (id1 != 0 && id2 != 0))
    return 0;
  if (id1 != 0 && id2 != 0 && (!existingID(db, id1) || !existingID(db, id2)))
    return 0;

  TDATABASE *newNode = (TDATABASE *)malloc(sizeof(*newNode));
  newNode->id1 = id1;
  newNode->id2 = id2;
  newNode->person = (TRESULT *)malloc(sizeof(TRESULT));
  newNode->person->m_ID = id;
  newNode->person->m_Name = strdup(name);
  newNode->person->m_Next = NULL;
  newNode->next = NULL;

  // if its the first addition in the database
  if (db->next == NULL)
  {
    db->next = newNode;
    return 1;
  }
  else if (db->next)
  {
    TDATABASE *temp = db->next;
    while (temp->next)
    {
      temp = temp->next;
    }
    temp->next = newNode;
    return 1;
  }
  return 0;
}

void getParents(TDATABASE *head, int id, int *id1, int *id2)
{
  TDATABASE *temp = head;

  while (temp->next->person->m_ID != id)
    temp = temp->next;

  *id1 = temp->next->id1;
  *id2 = temp->next->id2;
}

TRESULT *findPerson(TDATABASE *db, int id)
{
  if (id == 0)
    return NULL;

  TDATABASE *dummy = db;

  while (dummy->next->person->m_ID != id)
    dummy = dummy->next;

  return dummy->next->person;
}

TRESULT *addHuman(TDATABASE *db, TRESULT *head, int id)
{
  TRESULT *newNode = (TRESULT *)malloc(sizeof(*newNode));
  TRESULT *parent = findPerson(db, id);
  if (!parent)
    return head;
  newNode->m_ID = parent->m_ID;
  newNode->m_Name = strdup(parent->m_Name);
  newNode->m_Next = NULL;

  if (!head)
  {
    head = newNode;
    return head;
  }

  TRESULT *dummy = head;
  while (dummy->m_Next)
    dummy = dummy->m_Next;

  dummy->m_Next = newNode;

  return head;
}

// ---------------------------

int cmpID(TRESULT **a, TRESULT **b)
{
  return ((*b)->m_ID < (*a)->m_ID) - ((*a)->m_ID < (*b)->m_ID);
}

int lengthOfList(TRESULT *head)
{
  int length = 0;
  TRESULT *dummy = head;
  while (dummy)
  {
    length++;
    dummy = dummy->m_Next;
  }
  return length;
}

TRESULT **listToArray(TRESULT *head, int size)
{
  TRESULT **array = (TRESULT **)malloc(sizeof(*array) * size);
  TRESULT *dummy = head;

  for (int i = 0; i < size; ++i)
  {
    array[i] = dummy;
    dummy = dummy->m_Next;
  }
  return array;
}

TRESULT *arrayToList(TRESULT **array, int size)
{
  TRESULT *head = NULL;
  TRESULT *tail = NULL;

  for (int i = 0; i < size; ++i)
  {
    if (!head)
    {
      head = array[i];
      tail = head;
    }
    else
    {
      tail->m_Next = array[i];
      tail = tail->m_Next;
    }
    // set the next pointer to NULL so we avoid loops
    array[i]->m_Next = NULL;
  }
  return head;
}
// ------------------------------------------

void removeDuplicates(TRESULT *head)
{
  if (!head)
    return;
  TRESULT *curr = head;
  while (curr->m_Next)
  {
    if (curr->m_ID == curr->m_Next->m_ID)
    {
      TRESULT *temp = curr->m_Next;
      curr->m_Next = curr->m_Next->m_Next;
      free(temp);
    }
    else
    {
      curr = curr->m_Next;
    }
  }
}

void print(TRESULT *head)
{
  TRESULT *temp = head;
  while (temp)
  {
    printf("%s\n", temp->m_Name);
    temp = temp->m_Next;
  }
}

TRESULT *ancestors(TDATABASE *db, int id)
{
  // if said person does not exist in our database
  if (!existingID(db, id))
    return NULL;

  int id1, id2;
  // getting the persons parensts
  getParents(db, id, &id1, &id2);

  TRESULT *newList = NULL;
  newList = addHuman(db, newList, id1);
  newList = addHuman(db, newList, id2);

  TRESULT *dummy = newList;
  while (dummy)
  {
    getParents(db, dummy->m_ID, &id1, &id2);
    newList = addHuman(db, newList, id1);
    newList = addHuman(db, newList, id2);
    dummy = dummy->m_Next;
  }

  int size = lengthOfList(newList);
  TRESULT **array = listToArray(newList, size);
  qsort((void *)array, size, sizeof(array[0]), (int (*)(const void *, const void *))cmpID);
  newList = arrayToList(array, size);
  removeDuplicates(newList);
  return newList;
}

int existsInList(int target, TRESULT *head)
{
  TRESULT *dummy = head;
  while (dummy)
  {
    if (target == dummy->m_ID)
      return 1;

    dummy = dummy->m_Next;
  }
  return 0;
}

TRESULT *insert(TRESULT *head, TRESULT *data)
{
  if (!head)
  {
    head = data;
    data->m_Next = NULL;
    return head;
  }
  TRESULT *dummy = head;
  while (dummy->m_Next)
    dummy = dummy->m_Next;

  dummy->m_Next = data;
  data->m_Next = NULL;
  return head;
}

TRESULT *commonList(TRESULT *l1, TRESULT *l2)
{
  TRESULT *newList = NULL;
  TRESULT *dummy = l1;

  int total = 0;
  while (dummy)
  {
    if (existsInList(dummy->m_ID, l2))
    {
      TRESULT *temp = dummy->m_Next;
      newList = insert(newList, dummy);
      dummy = temp;
      total++;
    }
    else
    {
      dummy = dummy->m_Next;
    }
  }
  if (total == 0)
    return NULL;

  return newList;
}

TRESULT *commonAncestors(TDATABASE *db, int id1, int id2)
{
  if (!existingID(db, id1) || !existingID(db, id2))
    return NULL;

  TRESULT *personOne = ancestors(db, id1);
  TRESULT *personTwo = ancestors(db, id2);

  if (!personOne || !personTwo)
    return NULL;

  TRESULT *newList = commonList(personOne, personTwo);
  return newList;
}

void freeResult(TRESULT *res)
{
  while (res)
  {
    TRESULT *temp = res->m_Next;
    free(res->m_Name);
    free(res);
    res = temp;
  }
}

void doneAll(TDATABASE *db)
{
  if (!db)
    return;
  while (db)
  {
    TDATABASE *temp = db->next;
    if (db->person)
    {
      free(db->person->m_Name);
      freeResult(db->person);
    }
    free(db);
    db = temp;
  }
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

  // doneAll(&a);

  return 0;
}
#endif /* __PROGTEST__ */
