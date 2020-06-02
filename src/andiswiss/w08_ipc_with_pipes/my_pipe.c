//
// Created by AndiSwiss on 02.06.20.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 10


int main(void) {
    int pfd[2];  // Array with the two pipe-file-descriptors

    // Create the pipe:
    if (pipe(pfd) == -1) {
        printf("error with pipe: %d\n", errno);
        return errno;
    }

    switch (fork()) {
        case -1:
            printf("error with fork: %d\n", errno);
            return errno;
        case 0:
            // Child, reading data:
            printf("I'm the child with pid %d.\n", getpid());
            char *message = "hello";
            write(pfd[1], message, 5);
//            close(pfd[0]);
            exit(0);
        default:
            // Parent:
            printf("I'm the parent with pid %d.\n", getpid());
            char *received = "";
            read(pfd[0], received, 5);
            printf("Got the following message from child: %s\n", received);
//            close(pfd[1]);
            exit(0);
    }

}

// run with:
// make my_pipe && ./out/my_pipe