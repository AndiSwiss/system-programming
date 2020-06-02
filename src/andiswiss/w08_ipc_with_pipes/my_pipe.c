//
// Created by AndiSwiss on 02.06.20.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 10




int main(void) {
    // Array with the two pipe-file-descriptors
    // pdf[0]: for reading (the receiver)
    // pdf[1]: for writing (the sender)
    int pfd[2];

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
            close(pfd[0]);
            char message[] = "hello";
            size_t size = sizeof(message) / sizeof(message[0]);
            // introduce sleep, to ensure, that the parent is in fact waiting for the child:
            sleep(1);
            write(pfd[1], message, size);
            close(pfd[0]);
            exit(0);
        default:
            // Parent:
            close(pfd[1]);

            /// VERSION, IF YOU KNOW, how many bytes, you will expect:
//            char received[5];
//            read(pfd[0], received, 5);
//            printf("\nGetting the following message from child: %s\n", received);


            /// Dynamic version, if yo DON't know, how many bytes you would get (adapted from sample solution):
            char title[] = "\nGetting the following message from child: ";
            write(STDOUT_FILENO, title, sizeof(title) / sizeof(title[0]));
            char received[1];
            while (read(pfd[0], received, 1) == 1) {
                write(STDOUT_FILENO, received, 1);
            }
            write(STDOUT_FILENO, "\n", 1);


            close(pfd[1]);
            exit(0);
    }

}

// run with:
// make my_pipe && ./out/my_pipe