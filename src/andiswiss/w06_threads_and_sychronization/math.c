//
// Created by AndiSwiss on 01.06.20.
//

#include <stdio.h>
#include <math.h>


/** Problems with sin, tan and so forth:
 * The math library is not correctly compiled and included, when not using the
 * -lm  flag in the compiler
 * -> so added this flag to the makefile
 *
 * Without the flag  -lm   -> the compiler aborts with the error
 *   undefined reference to `sin'
 *
 * See also https://stackoverflow.com/questions/5005363/undefined-reference-to-sin
 */



int main (void) {
    double x, result, piValue;
    x = 45;
    piValue = M_PI / 180;
    result = sin(x * piValue);
    printf("The sine of %lf is %lf degrees\n", x, result);

    return 0;
}
