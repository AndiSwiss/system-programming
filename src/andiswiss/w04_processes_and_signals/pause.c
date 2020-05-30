//
// Created by tamberg
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int flag = 0;
// ATTENTION: 'volatile' in C and C++ means something very different than in Java or C#
// -> see:
// https://de.wikipedia.org/wiki/Volatile_(Informatik)
// https://en.wikipedia.org/wiki/Volatile_(computer_programming)
// https://barrgroup.com/embedded-systems/how-to/c-volatile-keyword
// and other sources

void handle(int signal) {
    flag = 1;
}

int main() {
    signal(SIGINT, handle);
    pause(); // wait for signals
    printf("flag = %s\n", flag ? "true" : "false");
    printf("flag = %d\n", flag);
}
