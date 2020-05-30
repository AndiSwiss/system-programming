//
// Created by AndiSwiss on 26.05.20.
//
#include <stdio.h>
#include <stdbool.h>

#define PI 3.14159

void printBoolean(bool b);

void pointerStuff();

void structStuff();

void typedefStuff();

int main(void) {
    printf("%f\n", PI);

    int n1 = 0;
    n1--;
    printf("n1 is now %d\n", n1);

    unsigned int n2 = 0;
    n2--;
    printf("n2 is now %d\n", n2);  // ?? WHY ??

    float f;
    double d;
    long double ld;

    printf("sizeof(float)=%lu, sizeof(double)=%lu, sizeof(long double)=%lu\n",
           sizeof(f), sizeof(d), sizeof(ld));

    // only with the #include <stdbool.h>, we can have a boolean type
    bool b;
    b = true;
    printBoolean(b);  // my custom method
    b = false;
    printBoolean(b);  // my custom method


    // slide 15
    int n5 = 2.3;   // the .3 falls away


    // TODO: stuff from screenshots from slides

    pointerStuff();
    structStuff();
    typedefStuff();

    return 0;
}


void printBoolean(bool b) {
    printf("%s\n", b ? "true" : "false");
}

void pointerStuff() {
    int i = 23;
    int *p;
    p = &i;
    int j = *p;
    printf("pointerStuff: %d, %p, %d, %d\n", i, (void *) p, *p, j);
    printf("casts of pointer: (void *) p = %p, (int *) p = %p, p = %p\n", (void *) p, (int *) p, p);
}

void structStuff() {
    struct point {
        int x;
        int y;
    };
    struct point p = {3, 2};
    struct point q;
    q.x = p.y;
    printf("structStuff: point p: (%d, %d)\n", p.x, p.y);
    printf("structStuff: point p: (%d, %d)\n", q.x, q.y);
}

void typedefStuff() {
    typedef struct point {int x; int y;} Point;
    typedef struct rectangle {Point a; Point b;} Rectangle;
    Point p = {3, 2};
    Point q;
    q.x = p.y;
    Rectangle r;
    r.a = p;
    r.b = q;
    printf("typedefStuff: Rectangle: a = (%d, %d), b = (%d, %d)\n", r.a.x, r.a.y, r.b.x, r.b.y);

}
// run this with
// make w01a_various_stuff && ./out/w01a_various_stuff