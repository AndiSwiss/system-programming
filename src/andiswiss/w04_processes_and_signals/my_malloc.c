
/**
 * Starting-code for Hands-on
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define N 33359
// NOTE 1: A lower number than 33359 (at least in my current Docker-configuration) results in throwing NO error -
//      so the 'free(p0)' is not working then as expected!!
//      If the number is 33359 or higher, then the "Segmentation fault" error is thrown as expected.
//      Most likely this is based on the same effect, if you use ../src/andiswiss/tlpi-book/memalloc/free_and_sbrk.c
//      with low values: then the program-break also doesn't move!
//
// NOTE 2: A higher number than 530000000 would result in (also try yourself):
//      Error 12
//      malloc: Cannot allocate memory
//      And later when trying to access those memory slots:  "Segmentation fault"

extern char etext, edata, end; // no include required


void *my_malloc(size_t size) {
    return malloc(size); // TODO: replace
}

void my_free(void *p) {
    free(p); // TODO: replace
}

int main() {
    // Some data about the memory:
    printf("\n&etext = %p\n", (void *) &etext);
    printf("&edata = %p\n", (void *) &edata);
    printf("&end = %p\n", (void *) &end);
    printf("&end - &edata = %ld\n", (long int) (&end - &edata));
    printf("&edata - &etext = %ld\n", (long int) (&edata - &etext));


    printf("\nAllocating the memory with malloc(size):\n");
    int *p = my_malloc(N * sizeof(int));
    if (p == NULL) {
        printf("Error %d\n", errno);
        perror("malloc");
//        return -1;  // -> normally, you would abort the app. But I let it run, to see the subsequent "Segmentation fault"
    }
    // Copy the pointer at the current location - for later usage:
    int *p0 = p;

    printf("\nReading current value and setting a new value:\n");
    for (int i = 0; i < N; i++) {
        // Only setting and printing first 5 and last 5:
        if (i < 5 || i > N - 6) {
            int before = *p;
            // Setting a value:
            *p = i;
            printf("place no %d: %p, value before setting: %d, value after setting: %d\n", i, (void *) p, before,
                   *p); // garbage, if reused
        }
        p++;
    }


    printf("\nAccessing the data BEFORE freeing the memory (should work just fine):\n");
    // Resetting the pointer:
    p = p0;
    for (int i = 0; i < N; i++) {
        // Only accessing and printing first 5 and last 5:
        if (i < 5 || i > N - 6) {
            printf("place no %d: %p, currently in memory: %d\n", i, (void *) p, *p); // garbage, if reused
        }
        p++;
    }

//    my_free(p0);
    my_free(p0);

    printf("\nAccessing the data AFTER freeing the memory -> will immediately result in 'Segmentation fault':\n");
    // Resetting the pointer:
    p = p0;
    printf("Fourth element: at address %p in memory: value = ... (on next line...):\n", (p + 4));
    printf("value = %d\n", *(p + 4));
    for (int i = 0; i < N; i++) {
        // Only setting and printing first 5 and last 5:
        if (i < 5 || i > N - 6) {
            printf("place no %d: %p, currently in memory: %d\n", i, (void *) p, *p); // garbage, if reused
        }
        p++;
    }
    // -> As expected: results immediately in a "Segmentation fault" (BUT only if N is greater than 33358!!)

    return 0;
}


// run with:
// make my_malloc && ./out/my_malloc