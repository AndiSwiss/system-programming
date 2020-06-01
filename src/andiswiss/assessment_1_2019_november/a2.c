//
// Created by AndiSwiss on 01.06.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(void) {
    /**
     * x is a pointer of type int
     * y is an int (integer)
     *
     * Since g accepts only a pointer of type int:
     * x can be directly passed into g(x)
     * For y, you have to get the address with &:  g(&y)
     *
     * Since x is using malloc:
     * x is stored in the heap
     * y is stored in the stack   (?)
     */

}


// run with:
//  make a2 && ./out/a2