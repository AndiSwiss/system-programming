//
// Created by AndiSwiss on 04.06.20.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


void *routine(void *arg) {
    int n = atoi(arg);
    printf("In thread 'routine': You provided the number %d\n", n);

    return "routineDone";
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        pthread_t thread;
        pthread_create(&thread, NULL, routine, argv[1]);

        // The following code is NEEDED, otherwise, the routine somehow get's stuck and does not do the printf()!!
//        pthread_join(thread, NULL);

        // Or if you want to get the return Value:
        void *retVal;
        pthread_join(thread, &retVal);

        printf("retVal after joining the threads was: %s\n", (char *) retVal);
    } else {
        printf("ERROR: please provide a number as argument\n");
    }

    return 0;
}

// run with:
// make pthread_example && ./out/pthread_example 42