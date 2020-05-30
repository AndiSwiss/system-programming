//
// Created by AndiSwiss on 27.05.20.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

Point *create_point(int x, int y);


int main(void) {
    Point *origin = create_point(0, 0);
    origin->x = 14;
    origin->y = 77;
    printf("(%d, %d)\n", origin->x, origin->y);

    // don't forget to free the memory:
    free(origin);


    // NOTE: the parameters of point anyhow get initialized to 0:
    Point p2;
    printf("(%d, %d)\n", p2.x, p2.y);
    p2.x++;
    p2.y  += 7;
    printf("(%d, %d)\n", p2.x, p2.y);


    return 0;
}


Point *create_point(int x, int y) {
    Point *p = malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}
