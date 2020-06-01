//
// Created by AndiSwiss on 01.06.20.
//
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *someWork(void *threadName) {
    sleep(1);
    char * name = (char *) threadName;
    printf("This is some work done by thread named '%s'. My thread id is: %ld.\n", name, (long) pthread_self());
    pthread_exit(NULL);
}

int main(void) {

    pthread_t thread;

    char *name = "Endeavor";
    printf("Hello, I am thread #%ld, creating a new thread named '%s'.\n", (long) pthread_self(), name);

    int answer = pthread_create(&thread, NULL, someWork, (void *) name);
    if (answer) {
        // NOTE: according to https://www.man7.org/linux/man-pages/man3/pthread_create.3.html
        // pthread_create(...) returns 0 when successful
        // It returns an error number if an error occured
        printf("ERROR: return code from pthread_create() is %d\n", answer);
    }

    // Last thing for main() to be done:
    pthread_exit(NULL);
}