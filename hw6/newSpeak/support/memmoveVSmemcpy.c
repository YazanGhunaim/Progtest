#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char str[] = "Start stop";
    printf("%s\n", str);

    // memcpy copies a memory block from one position to another
    memcpy(str, str+6, 4*sizeof(char));
    printf("%s\n", str);

    // takes in same parameters
    memmove(str, str+6, 4*sizeof(char));
    printf("%s\n", str);

    // copy art to beginning
    memmove(str, str+2, 3*sizeof(char));
    printf("%s\n", str);

    // memcopy here has ason error
    memcpy(str, str+2, 3*sizeof(char));
    printf("%s\n", str);

    // memcpy directly copies memory but memmove first copies the source to buffer, then moves that data
    // from buffer to destination... memmove is safer when having overlapping destinations
    // some compilers make memcpy safe aswell so no change noticed, however not guarenteed with every compiler
    

    



    return 0;
}
