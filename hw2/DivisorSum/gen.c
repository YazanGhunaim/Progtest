#include <stdio.h>
#include <stdlib.h>

int main ( ) {
printf("%d", 9000);
	for ( int i = 0; i < 9000; ++ i ) {
		printf ( "%d\n", rand ( ) % 9000 );
	}
}
