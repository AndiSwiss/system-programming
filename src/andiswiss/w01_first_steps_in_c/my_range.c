//
// Created by AndiSwiss on 26.05.20.
//

#include <stdio.h>
#include <limits.h>

// see https://github.com/fhnw-syspr-4ibb2/fhnw-syspr-work-01-AndiSwiss



int main(void) {
    // the solution I've found using a library:
    int current = INT_MAX;
    printf("%d, %d\n", current + 1, current);



    // nice solution by tamberg:
    // https://github.com/tamberg/fhnw-syspr/blob/master/01/range.c
    printf("calculating...\n");
    int i = 0;
    int j = -1;
    while (i > j) {
        j = i;
        i++;
    }
    printf("%d, %d\n", i, j);

    printf("calculating...\n");
    unsigned int ui = 1;
    unsigned int uj = 0;
    while (ui > uj) {
        uj = ui;
        ui++;
    }
    printf("unsigned: %d, %d\n", ui, uj);   // stops at ui = 0, uj = -1  ???
    return 0;
}



// run with this command inside Docker:
// make w01b_my_range && ./out/w01b_my_range