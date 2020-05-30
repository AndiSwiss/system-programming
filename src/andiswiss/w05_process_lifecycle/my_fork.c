//
// Created by AndiSwiss on 30.05.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int main(void) {
    int pid, pid_p, pid_c;

    pid = fork();
    if (pid == 0) {
        // I'm a child:
        pid = getpid();
        pid_p = getppid();
        printf("I'm child pid=%d of parent pid_p=%d\n", pid, pid_p);
        exit(1);
    } else {
        // I'm the parent:
        pid_c = pid;
        pid = getpid();
        printf("I'm parent pid=%d of child pid_c=%d\n", pid, pid_c);
    }
    return 0;
}