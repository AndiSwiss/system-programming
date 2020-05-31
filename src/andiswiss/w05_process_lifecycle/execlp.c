//
// Created by tamberg
// Edited by AndiSwiss
//

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        sleep(1);
        execlp("curl", "-v", "tmb.gr", NULL);
        // Does not return
        // & don't forget to add NULL at the end of the list of args! Otherwise, the compiler says:
        //  ... warning: missing sentinel in function call [-Wformat=]   execlp("curl", "-v", "tmb.gr");
    }
    printf("waiting...\n");
    fflush(stdout);
    wait(NULL); // wait for child to exit
    printf("\ndone.\n");
    return 0;
}