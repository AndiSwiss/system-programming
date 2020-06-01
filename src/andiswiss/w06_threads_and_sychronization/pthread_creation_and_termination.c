//
// From https://computing.llnl.gov/tutorials/pthreads
//
/******************************************************************************
* FILE: hello.c
* DESCRIPTION:
*   A "hello world" Pthreads program.  Demonstrates thread creation and
*   termination.
* AUTHOR: Blaise Barney
* LAST REVISED: 08/09/11
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS     5

void *PrintHello(void *threadid) {
    sleep(3);
    long tid;
    tid = (long) threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {

    printf("\n---\nTo see the threads, open a second terminal and type   top -H -p <pid>\n");
    printf("pid = %d\n", getpid());
    printf("Starting in 5\n");
    sleep(1);
    printf("Starting in 4\n");
    sleep(1);
    printf("Starting in 3\n");
    sleep(1);
    printf("Starting in 2\n");
    sleep(1);
    printf("Starting in 1\n");
    sleep(1);

    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for (t = 0; t < NUM_THREADS; t++) {
        sleep(2);
        long threadSelf = (long) pthread_self();
        printf("In main: I am thread #%ld, creating thread %ld\n", threadSelf, t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *) t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Last thing that main() should do */
    pthread_exit(NULL);
}

// run with:
// make pthread_creation_and_termination && ./out/pthread_creation_and_termination
//
// To see the threads, open a second terminal and type   top -H -p <pid>
//
// OR even cooler: use the more graphical tool 'htop' -> install with:
// apt-get install htop
// To enable thread views in htop, launch htop, and press F2 to enter htop setup menu.
// Choose "Display option" under "Setup" column, and toggle on "Tree view" and "Show custom thread names" options.
// Press F10 to exit the setup.
// Note: I found this information on: https://unixhealthcheck.com/blog?id=465