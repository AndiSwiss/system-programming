//
// Created by AndiSwiss on 29.05.20.
//
#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t processID = getpid();
    pid_t parentID = getppid();
    printf("processID=%d, parentID=%d\n", processID, parentID);

    while (1){

    }

    return 0;
}