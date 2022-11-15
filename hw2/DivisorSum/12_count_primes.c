/* cont prime numbers - test the efficiency of various primality test algorithms.
 * compile with -O2 and -lm compiler switches
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>

/* only two divisors */
unsigned isPrime1(unsigned n) {
  unsigned i;
  unsigned cntDivisors = 0;
  if (n < 2)
    return 0;
  for (i = 1; i <= n; i++)
    if (n % i == 0)
      cntDivisors++;
  if (cntDivisors == 2)
    return 1;
  else
    return 0;
}

/* return when the first divisor is found */
unsigned isPrime2(unsigned n) {
  unsigned i;
  if (n < 2)
    return 0;
  for (i = 2; i < n; i++)
    if (n % i == 0)
      return 0;
  return 1;
}

/* test divisors between 2 and n/2 */
unsigned isPrime3(unsigned n) {
  unsigned i;
  if (n < 2)
    return 0;
  for (i = 2; i <= n / 2; i++)
    if (n % i == 0)
      return 0;
  return 1;
}

/* test divisors between 2 and sqrt(n) */
unsigned isPrime4(unsigned n) {
  unsigned i;
  unsigned max = (unsigned)sqrt(n);
  if (n < 2)
    return 0;
  for (i = 2; i <= max; i++)
    if (n % i == 0)
      return 0;
  return 1;
}

/* sieve of Eratostenes */ 
typedef unsigned long long TULL;
/* # of bits in one array element */
#define ULLONG_BITS (sizeof (unsigned long long) * 8)
    
void setAllTrue(TULL *bSet, unsigned dim) {
  unsigned i;
  for (i = 0; i < dim; i++) 
    bSet[i] = ULLONG_MAX;
}
    
void setFalse(TULL *bSet, unsigned i) {
  bSet[i / ULLONG_BITS] &= ~ (1ULL << (i % ULLONG_BITS));        
}

unsigned isTrue(TULL *bSet, unsigned i) {
  if ((bSet[i / ULLONG_BITS] & (1ULL << (i % ULLONG_BITS))) != 0ULL) 
    return 1;
  return 0;
}

unsigned sieve(unsigned n) {
  unsigned dim = n / ULLONG_BITS + 1;
  TULL *bSet = (unsigned long long *) malloc(dim * sizeof ( *bSet ) ); 
  unsigned i, j, cnt = 0, max = sqrt(n);
  
  setAllTrue(bSet, dim);
  for (i = 2; i <= max; i++) {
    if (isTrue(bSet, i)) {  /* prime found */
      cnt++;
      for(j = i * i; j <= n; j += i)
        setFalse(bSet, j);  /* not a prime */
    }        
  }
  for (i = max + 1; i <= n; i++)  /* remaining primes greater than max */
    if(isTrue(bSet, i))
      cnt++;
  free(bSet);      
  return cnt;          
}
    
void primesTest (unsigned cnt, unsigned(alg)(unsigned), double timeLimit) {
  unsigned i;
  clock_t begin = clock();
  unsigned cntPrimes = 0;
  unsigned upTo = 1;
  printf("\nPrimes%d\n", cnt);
  for (i = 1; ; i++) {
    if (alg(i))
      cntPrimes++;
    if (i == upTo) {
      double secs = (double)(clock() - begin)/CLOCKS_PER_SEC;
      printf("Limit: %9d # primes: %8d, "
		           "time: %5.3f sec, "
		           "speed: %12.0f num/sec\n",
		           i, cntPrimes, secs, i / secs);
      if ( secs > timeLimit ) 
        break;
      upTo *= 2;
    }  
  }    
}

void sieveTest (unsigned cnt, double timeLimit) {
  unsigned upTo;
  printf("\nSieve\n");
  for ( upTo = 1; ; upTo *= 2 ) {
    clock_t begin = clock();
    unsigned cntPrimes = sieve(upTo);
    double secs = (double)(clock() - begin)/CLOCKS_PER_SEC;
    printf("Limit: %9d # primes: %8d, "
           "time: %5.3f sec, "
           "speed: %12.0f num/sec\n",
		         upTo, cntPrimes, secs, upTo / secs);
    if ( secs > timeLimit ) 
      break;
  }
}  

int main(void) {
  primesTest (1, isPrime1, 3.0 );
  primesTest (2, isPrime2, 3.0 );
  primesTest (3, isPrime3, 3.0 );
  primesTest (4, isPrime4, 3.0 );
  sieveTest  (5, 3.0);
  return EXIT_SUCCESS;
}
 
