//
// Created by tamberg
// Edited by AndiSwiss
//

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle(int sig) {
    printf("HANDLER: The handler was called with sig = %d.\n", sig);
    printf("HANDLER: Doing some work in the handler...\n");
    sleep(2);
    printf("HANDLER: Finished work in the handler...\n");
}

int main(void) {
    signal(SIGUSR1, handle);
    pid_t id = fork();
    if (id == 0) { // child
        printf("CHILD: I'm child %d of parent %d\n", getpid(), getppid());
        sleep(2);
        kill(getppid(), SIGUSR1); // synchronisation point
        sleep(1);
        printf("CHILD: ... more work ...\n");
        sleep(2);
        printf("CHILD: ... more work ...\n");
        sleep(2);
        printf("CHILD: ... more work ...\n");
        exit(0);
    } else { // parent
        //signal(SIGUSR1, handle);
        printf("PARENT: I'm parent %d of child %d\n", getpid(), id);
        pause(); // block until child passed synchronisation point AND the handler FINISHED it's work!
        printf("PARENT: Received signal\n");
        wait(NULL); // block until child process terminated
    }
    return 0;
}