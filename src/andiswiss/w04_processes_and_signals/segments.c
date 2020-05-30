//
// Created by tamberg
//

#include <stdio.h>
#include <unistd.h>

extern char etext, edata, end; // no include required

int i; // uninitialised data
char a[1024]; // uninitialised data
char b[] = {0x00, 0x01, 0x02}; // initialised data

void f(void) {
    char c[4096]; // stack frame for f()
    char d[] = {0x00}; // stack frame for f()
}

void g(void) {
    char e[256]; // stack frame for g()
    char *s = "hello"; // stack frame for g()
}

int main() {
    printf("&etext = %p\n", (void *) &etext);
    printf("&edata = %p\n", (void *) &edata);
    printf("&end = %p\n", (void *) &end);
    printf("&end - &edata = %ld\n", (long int) (&end - &edata));
    printf("&edata - &etext = %ld\n", (long int) (&edata - &etext));

    pid_t processID = getpid();
    printf("ProcessID = %d -- go to another terminal and look at the segent-addresses with the following command:\n", processID);
    printf("cat /proc/PID/maps  -> with the current PID:  cat /proc/%d/maps\n", processID);
    printf("CTRL-C to stop\n");
    while(1) {}
}

// run with
// make segments && ./out/segments

// according to slide 8, you can see the size of 'text', 'data' and 'bss' with the following command:
// size ./out/segments

// to see the full map, run the app, then in a second terminal do:
// cat /proc/PID/maps     (where 'PID' is the ID of the process)