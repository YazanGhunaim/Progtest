#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SIEVE_MAX 1000

void sieve ( char data [ ], size_t n ) {
	for ( size_t i = 0; i < n; ++ i ) {
		data [ i ] = 1;
	}
	data [ 0 ] = data [ 1 ] = 0;

	for ( size_t i = 2; i < sqrt ( n ); ++ i ) {
		if ( data [ i ] ) {
			for ( size_t j = i * i; j < n; j += i ) {
				data [ j ] = 0;
			}
		}
	}

}

int main ( ) {
	size_t count = 0;
	size_t n;
	printf ( "Max:\n" );
	if ( scanf ( "%zu", & n) != 1 ) {
		printf ( "Invalid input.\n" );
		return EXIT_FAILURE;
	}
	char * data = (char *) malloc ( n * sizeof ( * data ) );

	sieve ( data, n );

	/*for ( size_t i = 0; i < n; ++ i ) {
		if ( data [ i ] ) {
			printf ( "%zu\n", i );
			++ count;
		}
	}*/
	printf ( "%d", data[n-1] );
	// printf ( "Count: %zu\n", count );

	free ( data );
	return EXIT_SUCCESS;
}
