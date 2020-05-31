//
// Created by AndiSwiss on 31.05.20.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    if (fork() == 0) {  // This is a compact version of creating a fork and determining if I'm the child or the parent!
        // Child:
        printf("CHILD:  child %d of parent %d.\n", getpid(), getppid());
        exit(0);
    } else {
        printf("PARENT:   parent %d.\n", getpid());
        sleep(20);
        wait(NULL);
    }
}

// run with:
// make my_zombie && ./out/my_zombie
//
// At the same time, look at the processes in a 2nd terminal with:
// ps aux | grep my_zombie