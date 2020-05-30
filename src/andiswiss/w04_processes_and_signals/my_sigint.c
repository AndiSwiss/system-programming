//
// Created by AndiSwiss on 30.05.20.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>


// Method signature from slide 30 of the script.
void handle(int signal) {
    printf("\n------------------\n");
    printf("Received signal %d\n", signal);
    printf("------------------\n");
    printf("NOTE: while you normally can kill a program with 'ctrl-c', this is not happening anymore :-)\n");
    printf("If you want to successfully kill this app, you have to do the following:\n");
    printf("- Open a second terminal, go in to the same docker environment\n");
    printf("- Then best list all current processes with 'top'\n");
    printf("- Then write  'pkill my_sigint'  or  'kill PID'  (where PID is your process-id, here: %d\n", getpid());
}

int main(void) {
    signal(SIGINT, handle);  // -> see https://www.man7.org/linux/man-pages/man7/signal.7.html
    // There, it says that 'SIGINT' is 'Interrupt from keyboard'!

    printf("Waiting for  'ctrl + c'\n");

    while (1) {
        sleep(1);
    }

}

// run with:
// make my_sigint && ./out/my_sigint