
/**
 * Starting-code for Hands-on
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define N 33359

#define USE_CUSTOM_METHODS 1
// Set to 1, if you want to use the custom methods my_malloc(..) and my_free(..)
// Set to 0, if you want to user the standard methods malloc(..) and free(..)


// NOTE 1: There is a different behaviour when using the standard malloc(..) and free(..) as opposed to
//      the custom my_malloc(..) and my_free(..):
// NOTE 1b: Using the custom methods, my_free(p) is always working as expected: Any subsequent access to the memory
//      immediately results in a "Segmentation fault"
// NOTE 1a: Using the standard methods, a lower number than N=33359 (at least in my current Docker-configuration) results
//      in throwing NO error - so the 'free(p0)' is not working then as expected!!
//      If the number is N=33359 or higher, then the "Segmentation fault" error is thrown as expected.
//      Most likely this is based on the same effect, if you use ../src/andiswiss/tlpi-book/memalloc/free_and_sbrk.c
//      with low values: then the program-break also doesn't move!

extern char etext, edata, end; // no include required


void *my_malloc(size_t size) {
    // Standard code:
//        return malloc(size);

    // Custom code:
    printf("Running my_malloc with size=%zu\n", size);
    // NOTE: size is of 'unsigned long' -> in printf, you can use that with %zu
    printf("Current program-break is at:   %p  - (= break between heap and not yet allocated memory)\n", sbrk(0));
    // Advancing the current program break by 'size':
    void *p = sbrk(size);
    if (p == (void *) -1) {
        printf("error %d\n", errno);
        perror("sbrk");
        exit(-1);
    }
    printf("Advanced program-break to:     %p\n", sbrk(0));
    return p;
}

void my_free(void *p) {
//    free(p); // TODO: replace
    printf("Running my_free(..). Pointer p = %p\n", p);
    printf("Current program-break is at:   %p  - (= break between heap and not yet allocated memory)\n", sbrk(0));
    int answer = (int) brk(p);
    if (answer == -1) {
        printf("error %d\n", errno);
        perror("brk");
        exit(-1);
    }
    printf("Changed program-break back to: %p\n", sbrk(0));
}

int main() {
    // Some data about the memory:
    printf("\n&etext = %p\n", (void *) &etext);
    printf("&edata = %p\n", (void *) &edata);
    printf("&end = %p\n", (void *) &end);
    printf("&end - &edata = %ld\n", (long int) (&end - &edata));
    printf("&edata - &etext = %ld\n", (long int) (&edata - &etext));


    int *p;
    if (USE_CUSTOM_METHODS == 1) {
        printf("\nAllocating the memory with the CUSTOM method my_malloc(..):\n");
        p = my_malloc(N * sizeof(int));
    } else {
        printf("\nAllocating the memory with the STANDARD method malloc(..):\n");
        p = malloc(N * sizeof(int));
    }

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
            int before = (int) *p;
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


    if (USE_CUSTOM_METHODS == 1) {
        printf("\nFreeing the memory with the CUSTOM method my_free(p0):\n");
        my_free(p0);
    } else {
        printf("\nFreeing the memory with the STANDARD method free(p0):\n");
        free(p0);
    }


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
    // -> As expected: results immediately in a "Segmentation fault"

    return 0;
}


// run with:
// make my_malloc && ./out/my_malloc