//
// From http://www.cs.fsu.edu/~baker/realtime/restricted/notes/prodcons.html
//
// Files prodcons0.c to prodcons3.c
//

/** example of single producer and multiple consumers

   This uses a ring-buffer and no other means of mutual exclusion.
   It works because the shared variables "in" and "out" each
   have only a single writer.  It is an excellent technique for
   those situations where it is adequate.

   If we want to go beyond this, e.g., to handle multiple producers
   or multiple consumers, we need to use some more powerful means
   of mutual exclusion and synchronization, such as mutexes and
   condition variables.

 */

#define _XOPEN_SOURCE 500
//#define _REENTRANT
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
//#include <values.h>
#include <limits.h>
#include <errno.h>
#include <sched.h>

#define BUF_SIZE 10
int b[BUF_SIZE];
int in = 0, out = 0;

pthread_t consumer;
pthread_t producer;

void * consumer_body (void *arg) {
/* create one unit of data and put it in the buffer
   Assumes arg points to an element of the array id_number,
   identifying the current thread. */
    int tmp;
    int self = *((int *) arg);

    fprintf(stderr, "consumer thread starts\n");
    for (;;) {
        /* wait for buffer to fill */
        while (out == in);
        /* take one unit of data from the buffer */
        tmp = b[out];
        out = (out + 1) % BUF_SIZE;
        /* copy the data to stdout */
        fprintf (stdout, "thread %d: %d\n", self, tmp);
    }
    fprintf(stderr, "consumer thread exits\n");
    return NULL;
}

void * producer_body (void * arg) {
/* takes one unit of data from the buffer */
    int i;
    fprintf(stderr, "producer thread starts\n");
    for (i = 0; i < INT_MAX; i++) {
        /* wait for space in buffer */
        while (((in + 1) % BUF_SIZE) == out);
        /* put value i into the buffer */
        b[in] = i;
        in = (in + 1) % BUF_SIZE;
    }
    return NULL;
}

int main () {
    int result;
    pthread_attr_t attrs;

    /* use default attributes */
    pthread_attr_init (&attrs);

    /* create producer thread */
    if ((result = pthread_create (
            &producer, /* place to store the id of new thread */
            &attrs,
            producer_body,
            NULL))) {
        fprintf (stderr, "pthread_create: %d\n", result);
        exit (-1);
    }
    fprintf(stderr, "producer thread created\n");

    /* create consumer thread */
    if ((result = pthread_create (
            &consumer,
            &attrs,
            consumer_body,
            NULL))) {
        fprintf (stderr, "pthread_create: %d\n", result);
        exit (-1);
    }
    fprintf(stderr, "consumer thread created\n");

    /* give the other threads a chance to run */
    sleep (10);
    return 0;
}