//
// Created by tamberg
//

#include <stdio.h>
#include <errno.h>

int *f() {
    return &errno;
}

int main(void) {
    // errno = EINTR;

    *f() = EINTR;
    printf("errno = %d\n", errno);

    return 0;
}