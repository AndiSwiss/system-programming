//
// From http://www.cs.fsu.edu/~baker/realtime/restricted/notes/prodcons.html
//
// Files prodcons0.c to prodcons3.c
//

/** prodcons3.c

   The fourth in an evolutionary series of producer-consumer
   implementations.  It may be helpful to first read the code
   of the examples prodcons0, prodcons1, and prodcons2.

   This version extends the previous examples by taking a more
   object-oriented approach, attaching the mutex and condition
   variable to a buffer structure.

   It also contains more detailed comments, explaining the
   POSIX thread operations.

   This is an illustration of how the the POSIX thread primitives
   can be used to program a pair of Producer and Consumer threads.
   Annotations are provided to explain semantics of the primitives.
   The producer thread reads from standard input and passes a line
   of text at a time to the consumer thread.  The consumer thread
   then prints out the line, shifted to upper case.  The two threads
   communicate through a shared buffer, using POSIX condition
   variables to synchronize, and a POSIX mutex to protect the
   shared data.

   The effect of this program is to wait for input from the
   standard input.  After it has received some number of lines of
   input (between 1 and 4, depending on the thread scheduling policy)
   it will start producing lines of output.  It will produce one
   line of output for each line of input, but may not always strictly
   alternate between input and output (due to the buffer).
   The output lines should be the same as the input
   lines, except that all letters have been shifted to uppercase.
   To terminate the program enter a Control-d (ASCII EOT) character.

   The exact behavior will vary according to the thread scheduling
   policy that is in force.

   Warning:  The technique used here is still only adequate for a single
   producer and a single consumer.  (What is the problem if we have
   more than one producer or consumer?)

   Because we are using a ring buffer structure, we almost do not need
   the mutex and condition variables.  The reason we need it is that
   we have two writers for the count of items in the buffer, and so
   must lock the buffer while the count is being tested and updated.

*/

#define _XOPEN_SOURCE 500
//#define _REENTRANT
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

/* pthread.h contains the prototypes of the pthread primitives.
   The names beginning with "pthread_" are declared in this file,
   and are standard POSIX thread operations.  The implementation
   of these operations is provided by the Pthread library, which
   must be linked with this program.  See the file "Makefile" for
   more details.
 */
#include <pthread.h>

#define BNUM 4               /* number of lines in the buffer */
#define BSIZE 256            /* length of each line */

/* shared_buffer_t is used as a cyclic buffer.
   The indices next_in and next_out chase one another around the
   buffer, in a cyclic fashion (modulo BNUM).
*/
typedef struct shared_buffer {
    pthread_mutex_t lock;      /* protects the buffer */
    pthread_cond_t             /* the POSIX condition variable type */
    new_data_cond,           /* to wait when the buffer is empty */
    new_space_cond;          /* to wait when the buffer is full */
    char c[BNUM][BSIZE];       /* an array of lines, to hold the text */
    int next_in,               /* next available line for input */
    next_out,              /* next available line for output */
    count;                 /* the number of lines occupied */
} shared_buffer_t;

/* sb_init should be called to initialize each shared_buffer_t.
   It initializes the state of the buffer to empty.
   It MUST be called before other operations are performed on the object.
   It must NOT be called more than once per object.
 */
void sb_init(shared_buffer_t *sb)
{
    sb->next_in = sb->next_out = sb->count = 0;    /* (1) */
    pthread_mutex_init(&sb->lock, NULL);           /* (2) */
    pthread_cond_init(&sb->new_data_cond, NULL);   /* (3) */
    pthread_cond_init(&sb->new_space_cond, NULL);
}

/*
(1) When both postion markers are at the same position, the buffer is empty.

(2) pthread_mutex_init() initializes the specified mutex.
    It MUST be called before other operations are performed on the object.
    It must NOT be called more than once per object.

(3) pthread_cond_init() initializes the specified condition variable.
    It MUST be called before other operations are performed on the object.
    It must NOT be called more than once per object.
 */


/* producer is intended to be the body of a thread.
   It repeatedly reads the next line of text from the standard input,
   and puts it into the buffer pointed to by the parameter sb.
   It terminates when it encounters an EOF character in input.
   The EOF character is passed on to the consumer.
 */
void * producer(void * arg)
{ int i,k = 0;
    shared_buffer_t *sb = (shared_buffer_t *) arg;

    pthread_mutex_lock(&sb->lock);                           /* (1) */
    for (;;) {
        while (sb->count == BNUM)                              /* (2) */
            pthread_cond_wait(&sb->new_space_cond, &sb->lock);
        pthread_mutex_unlock(&sb->lock);                       /* (3) */
        k = sb->next_in;
        i = 0;
        do {  /* read one line of data into the buffer slot */
            if ((sb->c[k][i++] = getc(stdin)) == EOF) {
                sb->next_in = (sb->next_in + 1) % BNUM;
                pthread_mutex_lock(&sb->lock);
                sb->count++;
                pthread_mutex_unlock(&sb->lock);
                pthread_cond_signal(&sb->new_data_cond);           /* (4) */
                pthread_exit(NULL);                                /* (5) */
            }
        } while ((sb->c[k][i-1] != '\n') && (i < BSIZE));
        sb->next_in = (sb->next_in + 1) % BNUM;
        pthread_mutex_lock(&sb->lock);
        sb->count++;
        pthread_cond_signal(&sb->new_data_cond);               /* (6) */
    }
}

/*
(1) pthread_mutex_lock() locks the specified mutex.
    It blocks until the mutex is available, and returns with the
    mutex locked.  It must NOT be called if the calling thread
    has previously locked the mutex and has not since unlocked it.

    In this case, the mutex being locked is the one protecting
    the shared buffer, sb.

(2) Pthread_cond_wait() atomically releases the
    the mutex (the buffer lock, in this case) if it blocks.
    The calling thread must already holding the specified mutex locked.
    It will not return until we have the mutex locked again.
    A special feature of this primitive is that it is subject to
    so-called "spurious wakeups".  Thus, one always must
    enclose it within what looks like a busy-wait loop, which
    checks the logical condition for which the thread is waiting,
    and calls pthread_cond_wait() again if the condition is not
    yet satisfied.

    In this case, the condition for which we wait is the buffer
    having at least one free slot.

(3) pthread_mutex_unlock() releases the specified mutex.
    It returns with the mutex unlocked.  It does not block.
    It may ONLY be called if the calling thread has previously
    locked the mutex and has not since unlocked it.

(4) phread_cond_signal() signals any thread that
    is waiting on the specified condition variable.  If there is
    no thread waiting, the signal is lost.  If there is more than
    one thread waiting, at least one will wake up.  It is possible
    that other threads may also wake up --- one of the ways
    spurious wakeups may occur, as mentioned above.

(5) Pthread_exit() causes the calling thread to terminate.

    In this case, the reason for termination is that we have detected
    an end-of-file condition.
 */


/* consumer is intended to be the body of a thread.
   It repeatedly takes a line of text from the buffer which
   is pointed to by sb, converts it to upper case, and writes it to
   standard output.
   It terminates when it encounters an EOF character.
 */
void * consumer(void *arg)
{ int i, k = 0;
    shared_buffer_t *sb = (shared_buffer_t *) arg;

    pthread_mutex_lock(&sb->lock);                             /* L */
    for (;;) {                                                 /* L */
        while (sb->count == 0)                                   /* L */
            pthread_cond_wait(&sb->new_data_cond, &sb->lock);      /* L */
        pthread_mutex_unlock(&sb->lock);                         /* L */
        k = sb->next_out;
        i = 0;
        do { /* process next line of text from the buffer */
            if (sb->c[k][i] == EOF) {
                pthread_exit(NULL);
            }
            putc(toupper(sb->c[k][i++]), stdout);
        } while ((sb->c[k][i-1] != '\n') && (i < BSIZE));
        sb->next_out = (sb->next_out + 1) % BNUM;
        pthread_mutex_lock(&sb->lock);                           /* L */
        sb->count--;                                             /* L */
        pthread_cond_signal(&sb->new_space_cond);                /* L */
    }                                                          /* L */
}

/* The lines marked with L indicate the critical section, where
   the mutex is held locked.  Note that it extends around and
   back to be beginning of the loop, but excludes the center
   of the loop body, where the I/O is going on.
 */

/* the main program
 */
int main()
{ pthread_t th1, th2;  /* the two thread objects */
    shared_buffer_t sb;  /* the buffer */

    sb_init(&sb);
    pthread_create(&th1, NULL, producer, &sb);  /* (1) */
    pthread_create(&th2, NULL, consumer, &sb);
    pthread_join(th1, NULL); pthread_join(th2, NULL);            /* (2) */
    return 0;
}

/*
(1) pthread_create creates a new thread.
    The third parameter is a pointer to the function which the
    new thread should execute.  This function pointer must be a pointer
    of the type "pthread_func_t, that is a pointer to a function of the form

    void * (void *arg);

    That is, it has a single parameter, which must be of some pointer type.
    The formal return type is void *.

    In this case, we pass the address of the shared buffer
    as the parameter, and ignore the return value.

(2) pthread_join causes the caller to block until the specified
    thread has terminated.

    In this case, we use it to wait until the producer and consumer
    have terminated.  We could probably have just waited for the
    consumer to terminate, since we expect the producer to terminate
    first.

(3) pthread_detach allows the system resources (e.g. runtime stack space)
    associated with the specified thread to be returned to the system.

    In this case, we could probably skip it, since we are ready to
    shut down the whole process anyway.  In other situations it is
    more important.

 */