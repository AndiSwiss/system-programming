//
// Created by AndiSwiss on 30.05.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    int pid, pid_p, pid_c;

    pid = fork();
    if (pid == 0) {
        // I'm a child:
        pid = getpid();
        pid_p = getppid();
        printf("I'm child pid=%d of parent pid_p=%d\n", pid, pid_p);
        sleep(1);
        exit(1);
    } else {
        // I'm the parent:
        pid_c = pid;
        pid = getpid();
        printf("\nI'm parent pid=%d of child pid_c=%d\n", pid, pid_c);
        // additions as seen from tamberg:
        int status;
        wait(&status);
        printf("\nDone waiting for child, status %d\n", WEXITSTATUS(status));
        sleep(1);
        printf("\n");
    }
    return 0;
}

// NOTE: most of the times, parent prints its statement first, but sometimes, child is first!
//
// run with:
// make my_fork && ./out/my_fork
// -> will print  <defunkt>  (in comparison, run the same with my_fork: there, it's not a zombie!  (though you have to be quick!)