//
// Created by Andreas Ambühl on 27.05.20.
//

#include <stdio.h>

int i = 0;

void f() {
    printf("%d\n", i);
    i++;
}

void g(int i); // forward declaration

int main() {
    printf("%d\n", i);
    int i = 23;
    printf("%d\n", i);
    { // block
        printf("%d\n", i);
        int i = 42;
        printf("%d\n", i);
    }
    printf("%d\n", i);
    f();
    printf("%d\n", i);
    g(i); // without the above forward declaration
    // g is implicitly defined as int g(int i);
    printf("%d\n", i);
}

void g(int i) {
    printf("%d\n", i);
    i++;
}


// NOTE: there are no compile errors, but the IDE does mark "Declaration shadows a variable in global scope"