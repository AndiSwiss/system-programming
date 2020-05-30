//
// Created by tamberg
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("%lu\n", sizeof(size_t));
    printf("%lu\n", sizeof(char));
    for (int n = 0; n < 32; n++) {
        size_t size = n * sizeof(char);
        void *p = malloc(size);
        size_t *ps = p;
        printf("n = %d, *ps = %lu\n", n, *(--ps));
//        printf("n = %d, *ps = %d\n", n, *((int *) p - 1));
        free(p);
    }
}