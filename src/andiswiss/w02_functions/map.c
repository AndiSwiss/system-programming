//
// Created by tamberg
//

#include <stdio.h>

// Function declarations:
int inc(int i);

void map(int a[], int len, int (*f)(int));

void map2(int a[], int (*f)(int));


int main() {
    int a[] = {0, 0, 7};
    int len = sizeof a / sizeof a[0]; // # of elements
    map(a, len, inc); // inc is a function pointer
    printf("after map:  {%d, %d, %d}\n", a[0], a[1], a[2]);


    printf("\nsizeof a = %d, sizeof a[0] = %d, \n", (int) sizeof a, (int) sizeof a[0]);
    printf("actual length of array: sizeof a / sizeof a[0] = %d\n", (int) (sizeof a / sizeof a[0]));

    double aDouble = 3.9999999;
    int anInt = aDouble;  // works without casting, but CLion shows a small warning
    printf("aDouble=%f, anInt=%d\n", aDouble, anInt);
    // NOTE: in this print, only 6 digits after the comma are shown -> so it's rounded up
    // where the anInt obviously is always rounded down!

    map2(a, inc);
//    printf("after map2: {%d, %d, %d}\n", a[0], a[1], a[2]);
    return 0;
}

int inc(int i) {
    printf("inc\n");
    return i + 1;
}

void map(int *a, int len, int (*f)(int)) {
    printf("map\n");
    for (int i = 0; i < len; i++) {
        a[i] = f(a[i]);
    }
}

void map2(int a[], int (*f)(int)) {
    printf("\nmap2-function -- doesn't really work:\n");
    printf("sizeof a=%lu\n", sizeof &a);
    // IMPORTANT: above doesn't work, always prints 8 instead of 12, regardless of whether you do
    //  sizeof a     OR   sizeof &a
    // BECAUSE: when passing an array into a function, it's just reduced to the pointer to the first element!
    //  see also https://riptutorial.com/c/example/1125/array-length
    //  or https://www.geeksforgeeks.org/using-sizof-operator-with-array-paratmeters/

    // So the following would also get the wrong length -> len would always be 2!!
//    int len = sizeof &a / sizeof a[0];


    // following idea might work for strings, but not for regular arrays -> would result in a stack overflow!
//    int len = 0;
//    while (a[len] != '\0') {
//        len++;
//    }


    for (int i = 0; i < 5; ++i) {
        printf("current value: %d\n", a[i]);
        // -> you just get random values, which represent the current memory there
        // -> so, this approach also doesn't work!
    }

//    printf("len = %d\n", len);
//    map(a, len, f);
}
