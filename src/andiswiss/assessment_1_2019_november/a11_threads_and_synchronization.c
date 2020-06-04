//
//
//


/// -> for a possible solution, see file `../exams/assessment1.pdf`

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
    pthread_mutex_unlock(&m);
}


int main(void) {
    printf("B\n");
    pthread_t thread;
    pthread_mutex_lock(&m);
    pthread_create(&thread, NULL, start, NULL);
    sleep(1);
    printf("C\n");
//    pthread_cond_wait(&c, &m);
    printf("D\n");
    pthread_mutex_unlock(&m);
}

/**
 * Prints:
 * B    -> this is printed right at the beginning before anything else happens
 * C    -> TODO: FINISH ANALYZING!! main() did lock the mutex, so the second thread has to wait
 * A    ->
 * D
 */