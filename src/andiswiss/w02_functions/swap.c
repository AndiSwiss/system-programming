#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    printf("The values are *x=%d, *y=%d, the pointers x=%p, y=%p \n", *a, *b, &a, &b);
}

int main(void) {
    int x = 3, y = 7;
    printf("Before swap: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("After swap: x=%d, y=%d\n", x, y);
    return 0;
}