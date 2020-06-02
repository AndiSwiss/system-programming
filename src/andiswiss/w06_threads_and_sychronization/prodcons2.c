//
// From http://www.cs.fsu.edu/~baker/realtime/restricted/notes/prodcons.html
//
// Files prodcons0.c to prodcons3.c
//

/** example of single producer and multiple consumers

   This version uses a mutex and a condition
   variable for synchroniztion.
   This enables us to have multiple producers
   and/or consumers.  We chose to just have
   multiple consumers in this example.
   Compare it against prodcons1.

 */

#define _XOPEN_SOURCE 500
//#define _REENTRANT
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
//#include <values.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#define BUF_SIZE 10

int b[BUF_SIZE];
int in = 0, out = 0;

#define N_CONSUMERS 6
int arguments[N_CONSUMERS];
/* arguments[i] = i */
pthread_t consumer_id[N_CONSUMERS];
pthread_t producer;

pthread_mutex_t M;
pthread_mutexattr_t mattr;
pthread_cond_t  C;
pthread_condattr_t cattr;

void * consumer_body (void *arg) {
/* create one unit of data and put it in the buffer
   Assumes arg points to an element of the array id_number,
   identifying the current thread.
 */
    int tmp;
    int self = *((int *) arg);

    fprintf(stdout, "consumer thread starts\n");
    for (;;) {
        /* enter critical section */
        pthread_mutex_lock (&M);
        /* wait for data in the buffer */
        while (out == in)
            if (pthread_cond_wait (&C, &M)) {
                fprintf (stdout, "pthread_cond_wait: consumer\n");
                exit (-1);
            }
        tmp = b[out];
        /* wake up the producer if the buffer was full; the producer
           will stay blocked until we exit the critical section, below
         */
        if (((in + 1) % BUF_SIZE) == out) pthread_cond_signal (&C);
        out = (out + 1) % BUF_SIZE;
        /* exit critical section */
        pthread_mutex_unlock (&M);
        /* with the output outside the critical section
           we should expect some interleaving and reordering
         */
        fprintf (stdout, "thread %d:", self);
        fprintf (stdout, "%d\n", tmp); fflush (stdout);
    }
    fprintf(stdout, "consumer thread exits\n");
    return NULL;
}
void * producer_body (void * arg) {
/* takes one unit of data from the buffer
 */
    int i;
    fprintf(stdout, "producer thread starts\n");
    for (i = 0; i < 100; i++) {
        /* enter critical section */
        pthread_mutex_lock (&M);
        /* wait for space in buffer */
        while (((in + 1) % BUF_SIZE) == out)
            if (pthread_cond_wait (&C, &M)) {
                fprintf (stdout, "pthread_cond_wait: producer\n");
                exit (-1);
            }
        /* put value i into the buffer */
        b[in] = i;
        in = (in + 1) % BUF_SIZE;
        /* leave critical section */
        pthread_mutex_unlock (&M);
        /* wake up at least one consumer */
        pthread_cond_signal (&C);
    }
    return NULL;
}

int main () {
    int i, result;
    pthread_attr_t attrs;
    sigset_t set;

    /* initialize the mutex M and condition variable C */

    pthread_mutex_init (&M, NULL);
    pthread_cond_init (&C, NULL);

    /* start with default attributes */
    pthread_attr_init (&attrs);
    /* add an attribute that will cause us to use all processors
       if we have a machine with multiple processors
     */
    pthread_attr_setscope (&attrs, PTHREAD_SCOPE_SYSTEM);

    /* create producer thread */
    if ((result = pthread_create (
            &producer, /* place to store the id of new thread */
            &attrs,
            producer_body,
            NULL)))  /* no need for argument */ {
        fprintf (stdout, "pthread_create: %d\n", result);
        exit (-1);
    }
    fprintf(stdout, "producer thread created\n");
    /* create consumer threads */
    for (i = 0; i < N_CONSUMERS; i++) {
        arguments[i] = i;
        if ((result = pthread_create (
                &consumer_id[i],
                &attrs,
                consumer_body,
                &arguments[i]))) {
            fprintf (stdout, "pthread_create: %d\n", result);
            exit (-1);
        }
    }
    fprintf(stdout, "consumer threads created\n");

    /* Put the main thread to sleep so that the program will
       not terminate right away. This gives the other threads
       a chance to run indefinitely.  We can still kill the
       process with SIGINT or a signal that cannot be masked. */
    sigfillset (&set);
    sigdelset (&set, SIGINT);
    sigsuspend (&set);
    return 0;
}





