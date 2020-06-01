//
// Created by AndiSwiss on 01.06.20.
//
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct Arguments {
    char *name;
    int astronauts;
    double flightTime;
} Arguments;



void *someWork(void *args) {
    sleep(1);
    Arguments *a = (Arguments *) args;
    printf("Welcome earth! I'm space craft '%s'. I brought %d astronauts to the ISS in %f hours. "
           "Most likely, parts of my software was written in C or is based on C! My thread-id is %ld.\n",
           a->name, a->astronauts, a->flightTime, (long) pthread_self());
    pthread_exit(NULL);
}

int main(void) {
    pthread_t thread;

    Arguments args;
    args.name = "Endeavour";
    args.astronauts = 2;
    args.flightTime = 18.91;

    printf("Hello, I am thread #%ld, launching the first manned falcon 9 into space on May 30th 2020...\n", (long) pthread_self());

    int answer = pthread_create(&thread, NULL, someWork, (void *) &args);
    if (answer) {
        // NOTE: according to https://www.man7.org/linux/man-pages/man3/pthread_create.3.html
        // pthread_create(...) returns 0 when successful
        // It returns an error number if an error occured
        printf("ERROR: return code from pthread_create() is %d\n", answer);
    }

    // Last thing for main() to be done:
    pthread_exit(NULL);
}