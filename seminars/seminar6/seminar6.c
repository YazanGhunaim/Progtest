#ifndef __PROGTEST__
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdint.h>
#endif /* __PROGTEST__ */

long long avg3(long long a, long long b, long long c)
{
  long long remainderSum = a % 3 + b % 3 + c % 3;
  long long x = remainderSum % 3;
  long long y = a / 3 + b / 3 + c / 3 + remainderSum / 3;

  int minus = -(y > 0 && x < 0);
  int plus = +(y < 0 && x > 0);
  if (a == b && b == c)
  {
    return a;
  }
  else
  {
    return y + minus + plus;
  }
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
  assert(avg3(1, 2, 3) == 2);
  assert(avg3(-100, 100, 30) == 10);
  assert(avg3(1, 2, 2) == 1);
  assert(avg3(-1, -2, -2) == -1);
  assert(avg3(LLONG_MAX, LLONG_MAX, LLONG_MAX) == LLONG_MAX);
  assert(avg3(-9144612404012802320, -158591018938588160, -2026565360190200832) == -3776589594380530437);
  assert(avg3(9223372036854775800, 9223372036854775800, -7) == 6148914691236517197);
  assert(avg3(9223372036854775800, 9223372036854775800, -4611686018427387912) == 4611686018427387896);
  assert(avg3(9223372036854775800, 9223372036854775800, 9223372036854775801) == 9223372036854775800);
  assert(avg3(9223372036854775800, 9223372036854775801, -4611686018427387913) == 4611686018427387896);
  assert(avg3(9223372036854775800, 9223372036854775800, -8) == 6148914691236517197);
  assert(avg3(9223372036854775800, -6, -4611686018427387907) == 1537228672809129295);
  assert(avg3(9223372036854775800, -6, -2) == 3074457345618258597);
  assert(avg3 ( 9223372036854775800, -8, -4 ) == 3074457345618258596);

  return 0;
}
#endif /* __PROGTEST__ */
