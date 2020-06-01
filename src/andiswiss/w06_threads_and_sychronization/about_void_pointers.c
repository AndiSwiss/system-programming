//
// Created by AndiSwiss on 01.06.20.
//

// What exactly are void pointers in C?
// e.g. https://www.geeksforgeeks.org/void-pointer-c-cpp/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a = 10;
    char b = 'x';
    typedef struct {
        int x;
        int y;
    } Point;

    Point p;
    p.x = 42;
    p.y = 77;

    char *name = "Andi";

    // Now, let's try a void pointer:

    void *anything;

    // Assign it, don't forget the & to get the memory-location of the integer a:
    anything = &a;

    // Note: the following is not marked wrong by CLion, but when trying to
    // compile with make, it doesn't work and it would complain:
    //  warning: format '%s' expects argument of type 'char *', but argument 2 has type 'void *'
//    printf("anything = %s\n", anything);


    // Instead you have to cast to the actual format the void-Pointer now has:
    printf("\n*(int *) anything = %d\n", *(int *) anything);

    // You can reassign the void-pointer to anything you want, e.g.
    anything = &p;

    // Assign it to a string (note: name is already a pointer, so no more &):
    anything = name;

    // Slightly weird: the following compiles and runs just fine, but prints out
    // the number 2036624967, if name was "Andi"
    printf("\n*(int *) anything = %d\n", *(int *) anything);

    // When correctly casting, it prints out the name:
    // IMPORTANT: in comparison to the int-cast, there is no additional * in front of the
    // casting (remember, what a "String" in C is:  char *):
    printf("(char *) anything = %s\n", (char *) anything);


    // So let's try to assign to a typedef struct (don't forget the &):
    anything = &p;
    // Now, it's special, because the first element inside the typedef struct Point is actually
    // an int, so the casting works, but maybe not as expected:
    printf("\n*(int *) anything = %d\n", *(int *) anything);

    // To access a specific element of the Point:
    // First cast to (Point *), then get the element:
    printf("((Point *) anything)->y = %d\n", ((Point *) anything)->y);


    // Void pointers are also used in other contexts, such as
    // -  malloc() returns void *, which can be typecasted to any type like int *, char *, ...
    // e.g.:
    int n = 5;
    int *numbers = malloc(sizeof(int) * n);


    // Or another application: generic functions in C, e.g. qsort():
    // https://www.geeksforgeeks.org/comparator-function-of-qsort-in-c/
    // where the comparator function uses void-pointers.

    // and there are many more applications; be creative!
}



// run with:
//  make about_void_pointers && ./out/about_void_pointers