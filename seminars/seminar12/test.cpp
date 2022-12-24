#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem * m_Next;
  int      m_Val;
} TITEM;

typedef struct TData
{
  TITEM * m_First;
  TITEM * m_Last;
} TDATA;

#endif /* __PROGTEST__ */

// adds a new element to the beginning of the list
void insertStart ( TDATA * l, int x )
{
  TITEM * newNode = (TITEM *)malloc(sizeof(TITEM));

  newNode -> m_Val = x;
  newNode -> m_Next = l -> m_First;

  l -> m_First = newNode;
}
void insertEnd   ( TDATA * l, int x )
{
  TITEM * newNode = (TITEM *)malloc(sizeof(TITEM));

  newNode -> m_Val = x;
  newNode -> m_Next = NULL;

  if (!l -> m_First)
  {
    l -> m_First = newNode;
    l -> m_Last = newNode;
  }
  else {
    l -> m_Last -> m_Next = newNode;
    l -> m_Last = newNode;
  }

  l -> m_Last = newNode;
}
int  removeMax   ( TDATA * l )
{
}
void destroyAll  ( TDATA * l )
{
  /* TODO */
}

#ifndef __PROGTEST__
int main ( void )
{
  TDATA a;
  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, 1 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 1 );
  insertEnd ( &a, 3 );
  insertEnd ( &a, 4 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 5 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 5
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  // assert ( removeMax ( &a ) == 1 );
  // assert ( a . m_First != NULL
  //          && a . m_First -> m_Val == 1
  //          && a . m_First -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Val == 2
  //          && a . m_First -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Val == 1
  //          && a . m_First -> m_Next -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
  //          && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  // destroyAll ( &a );

  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, 1 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 3 );
  insertEnd ( &a, 0 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 3 );
  insertStart ( &a, 1 );
  insertStart ( &a, 2 );
  insertStart ( &a, 3 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 3
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  // assert ( removeMax ( &a ) == 3 );
  // assert ( a . m_First != NULL
  //          && a . m_First -> m_Val == 2
  //          && a . m_First -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Val == 1
  //          && a . m_First -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Val == 1
  //          && a . m_First -> m_Next -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 2
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
  //          && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
  //          && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  // assert ( removeMax ( &a ) == 3 );
  // assert ( a . m_First != NULL
  //          && a . m_First -> m_Val == 1
  //          && a . m_First -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Val == 1
  //          && a . m_First -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Val == 0
  //          && a . m_First -> m_Next -> m_Next -> m_Next == NULL
  //          && a . m_Last == a . m_First -> m_Next -> m_Next );
  // assert ( removeMax ( &a ) == 2 );
  // assert ( a . m_First != NULL
  //          && a . m_First -> m_Val == 0
  //          && a . m_First -> m_Next == NULL
  //          && a . m_Last == a . m_First );
  // destroyAll ( &a );

  // a . m_First = a . m_Last = NULL;
  // insertEnd ( &a, -1 );
  // insertEnd ( &a, -2 );
  // insertEnd ( &a, -10000 );
  // insertEnd ( &a, -1 );
  // insertEnd ( &a, -300 );
  // assert ( removeMax ( &a ) == 2 );
  // assert ( a . m_First != NULL
  //          && a . m_First -> m_Val == -2
  //          && a . m_First -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Val == -10000
  //          && a . m_First -> m_Next -> m_Next != NULL
  //          && a . m_First -> m_Next -> m_Next -> m_Val == -300
  //          && a . m_First -> m_Next -> m_Next -> m_Next == NULL
  //          && a . m_Last == a . m_First -> m_Next -> m_Next );
  // destroyAll ( &a );

  return 0;
}
#endif /* __PROGTEST__ */
