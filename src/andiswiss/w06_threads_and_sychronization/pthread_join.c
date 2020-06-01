//
// From https://computing.llnl.gov/tutorials/pthreads
//
//
/*****************************************************************************
* FILE: join.c
* DESCRIPTION:
*   This example demonstrates how to "wait" for thread completions by using
*   the Pthread join routine.  Threads are explicitly created in a joinable
*   state for portability reasons. Use of the pthread_exit status argument is
*   also shown. Compare to detached.c
* AUTHOR: 8/98 Blaise Barney
* LAST REVISED:  01/30/09
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/// On my system (MacBookPro 15" 2018, 2.9 GHz-6-Core Intel Core i9, 32 GB 2400 MHz DDR4),
/// I can easily run something like:
///      #define NUM_THREADS                 40
///      #define WORK_CYCLES_IN_ONE_THREAD   100000000
/// This would take about 50 seconds on average, and all 6 cores work 100%!
/// Though on the activity window of macOS, only 6 of the possible 12 threads are active -> I guess the remaining 6
/// threads have to be accessed via different strategies!
/// Don't forget to use the graphical 'htop' in your terminal to watch the threads and their work!
#define NUM_THREADS                 40
#define WORK_CYCLES_IN_ONE_THREAD   100000000

void *busyWork(void *t) {
    int i;
    long tid;
    double result = 0.0;
    tid = (long) t;
    printf("Thread %ld starting...\n", tid);
    for (i = 0; i < WORK_CYCLES_IN_ONE_THREAD; i++) {
        result += sin(i) * tan(i);
    }
    result *= (int) tid + 1;
    printf("Thread %ld done. Result = %e\n", tid, result);
    pthread_exit((void *) t);
}

int main(int argc, char *argv[]) {
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    long t;
    void *status;

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Main: creating thread %ld\n", t);
        rc = pthread_create(&thread[t], &attr, busyWork, (void *) t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(thread[t], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n", t, (long) status);
    }

    printf("Main: program completed. Exiting.\n");
    pthread_exit(NULL);
}

// run with
// make pthread_join && ./out/pthread_join
//
// and see my notes above   #define NUM_THREADS   40
