//
// Created by Andreas Ambühl on 27.05.20.
//

#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

Point create_point(int x, int y);


int main(void) {
    Point origin = create_point(0, 0);
    printf("(%d, %d)\n", origin.x, origin.y);

    // NOTE: the parameters of point anyhow get initialized to 0:
    Point p2;
    printf("(%d, %d)\n", p2.x, p2.y);
    p2.x++;
    p2.y  += 7;
    printf("(%d, %d)\n", p2.x, p2.y);


    return 0;
}


Point create_point(int x, int y) {
    Point p = {x, y};
    return p;
}
