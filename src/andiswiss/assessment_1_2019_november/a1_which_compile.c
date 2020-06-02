//
// Created by AndiSwiss on 01.06.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/// Start-time: 19:32


int main(void) {
    /// a: NO
//    int i = malloc(sizeof(int));
    // Would cause compile error
    // Correct would be:
    void *p = malloc(sizeof(int));

    /// b: YES
    char s[] = {'h', 'e', 'l', 'l', 'o'};
    for (int i = 0; i < 5; ++i) {
        printf("%c", s[i]);
    }
    printf("\n");

    /// c: NO
//    byte *b = "hello";
    // There is no type 'byte' in c.
    // Correct would be:
    char *b = "hello";
    printf("%s\n", b);

    /// d: YES
    // because in c, the number 0 evaluates to false in a boolean expression
    // and non-zero numbers evaluate to true
    // when assigning the result of a boolean expression to an integer, false = 0, true = 1
    int j = (0 || 1);  // produces 1
    printf("j = %d\n", j);
    j = (0 || 8);  // also produces 1
    printf("j = %d\n", j);
    j = (0 && 8);  // produces 0
    printf("j = %d\n", j);
    j = (15 && 42);  // produces 1
    printf("j = %d\n", j);
    j = !0;          // produces 1   (note: !0 is true)
    printf("j = %d\n", j);
    j = (!0 && 42);  // produces 1   (note: !0 is true)
    printf("j = %d\n", j);
    j = 427382;  // obviously produces 427382
    printf("j = %d\n", j);
    j = !!427382;  // produces 1   (because of the double negation, the number is first converted to the boolean 0,
                   // then to boolean 1) - this is a nice trick to convert any number not being 0 to a 1.
    printf("j = %d\n", j);
}

// run with:
//  make a1_which_compile && ./out/a1_which_compile