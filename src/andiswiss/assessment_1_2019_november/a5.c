//
// Created by AndiSwiss on 01.06.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * 1: YES
 * 2: NO
 * 3: YES
 * 4: YES
 */

int incNotIncing(int i) { return i++; }
// NOTE!! The above method does NOT increment the return value, because the increment happens AFTER the return!!
// Correct would be:
int inc(int i) { return ++i; }



int add(int a, int b) { return a + b; }

int eval(int a, int b, int (*op)(int, int)) { return op(a, b); }


int main(void) {
    printf("1: YES: %d\n", eval(inc(3), 3, add));  // result: 6
    printf("2:  NO: %d\n", eval(add(3, 3), 323434, inc)); // it would compile (with a warning),
    // but it executes and prints 6, ignoring whatever the second argument (here 323434) for eval(...) is!
    printf("3: YES: %d\n", eval(add(3, 3), inc(3), add)); // result: 10
    printf("4: YES: %d\n", eval(eval(3, 3, add), 3, add));  // result: 9

}


// run with:
//  make a5 && ./out/a5