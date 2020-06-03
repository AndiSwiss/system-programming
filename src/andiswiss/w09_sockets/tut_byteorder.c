//
// from https://www.tutorialspoint.com/unix_sockets/socket_quick_guide.htm
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    union {
        short s;
        char c[sizeof(short)];
    } un;


    un.s = 0x070a;

    if (sizeof(short) == 2) {
        if (un.c[0] == 7 && un.c[1] == 10)
            printf("big-endian\n");

        else if (un.c[0] == 10 && un.c[1] == 7)
            printf("little-endian\n");

        else
            printf("unknown\n");
    } else {
        printf("sizeof(short) = %lu\n", sizeof(short));
    }

    exit(0);
}