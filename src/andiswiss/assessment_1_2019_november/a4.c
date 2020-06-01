//
// Created by AndiSwiss on 01.06.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * The result is 8. Because you cannot really pass an array into a function in c. Instead what happens, you pass a
 * pointer to the first value of the array.
 * Here, *m results in 3, then (*m + 1) results in 4, then (*m + 1) * n results in 8;
 *
 * NOTE 1:
 * If the code would be  return (*(m + 1)) * n;, then the result would be 10!
 *
 * NOTE 2: If you would want to properly "send" the whole array for using it, you would also
 * have to send an integer with the length of the array.
 */

int f(int *m, int n) {
    return (*m + 1) * n;
}

int f2(int *m, int n) {
    return (*(m + 1)) * n;
}

int main(void) {
    int i[] = {3, 5};
    int j = 2;
    int k = f(i, j);
    printf("k after calling  f = %d\n", k);

    k = f2(i, j);
    printf("k after calling f2 = %d\n", k);
}


// run with:
//  make a4 && ./out/a4