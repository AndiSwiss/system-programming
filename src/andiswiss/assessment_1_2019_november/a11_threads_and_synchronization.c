//
// Initial version by tamberg
// Additional printf() and EXPLANATION by andiswiss
//


/**
 * EXPLANATION:
 *
 * Prints:
 * B    -> This is printed right at the beginning before anything else happens
 * C    -> See slide 17 of Syspr06ThreadsUndSynchronisation.pdf:
 *          A 'mutex' protects access to shared resources (mutex = 'mutual exclusion').
 *          Condition variables enable threads to inform each other about changes of a shared resource.
 *          For correct sequence, see slide 21.
 *          Slide 25: A condition variable is always used together with a mutex, which protects the variable.
 *          Slide 27: in pthread_cond_wait, the mutex is UNLOCKED and the thread is suspended until the condition variable
 *             changes. After that, the mutex is LOCKED again
 *          Slide 28: pthread_cond_signal(&c);    -> signal 1 waiting thread
 *                    pthread_cond_broadcast(&c); -> signal all waiting threads
 * A    -> Once the main() unlocks the mutex, function start() can continue -> happens in pthread_cond_wait(..)!!!
 * D    -> With pthread_cond_wait(&c, &m); -> as soon as function start() sends the unlock, main() COULD continue, but
 *         it seems that it has to wait for start() to unlock the mutex, so that pthread_cond_wait() can again lock the
 *         the mutex and main() can continue and print "D"
 */


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void *start(void *arg) {
    printf("entering function start() - BEFORE mutex lock!!\n");
    pthread_mutex_lock(&m);
    printf("A\n");
    pthread_cond_signal(&c);
    printf("start() just sent the cond_signal\n");
    sleep(2);
    printf("start() ended it's sleep\n");
    pthread_mutex_unlock(&m);
    printf("start() unlocked the mutex\n");   // this doesn't get printed anymore ?!?
}


int main(void) {
    printf("B\n");
    pthread_t thread;
    pthread_mutex_lock(&m);
    pthread_create(&thread, NULL, start, NULL);
    sleep(1);
    printf("C\n");
    pthread_cond_wait(&c, &m);    // Here, the process waits for the other method to send the signal with  pthread_cond_signal(&c);
    printf("D\n");
    pthread_mutex_unlock(&m);
}
