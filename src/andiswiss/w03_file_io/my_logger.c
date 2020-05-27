//
// Created by Andreas Ambühl on 27.05.20.
//

#include <stdio.h>
#include <fcntl.h>    // needed for open(...)
#include <unistd.h>   // needed for close(...) and more

#define BUFFER_SIZE 128


int main(void) {

    // Open source file
    int uptimeFd = open("/proc/uptime", O_RDONLY);
    if (uptimeFd == -1) {
        printf("ERROR with opening /proc/uptime. -> See next line for error-message:\n");
        perror("open");
        return -1;
    }

    // Open log file
    int logFd = open("./my.log", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (logFd == -1) {
        printf("ERROR with log-file: ./my.log  -> see next line for error-message:\n");
        perror("open");
        return -1;
    }

    // Actual copying of data:
    char buffer[BUFFER_SIZE];
    int r = read(uptimeFd, buffer, BUFFER_SIZE);
    while (r > 0) {
        write(logFd, buffer, r);
        r = read(uptimeFd, buffer, BUFFER_SIZE);
    }

    // close the files
    close(uptimeFd);
    close(logFd);

    return 0;
}




// run with
// make my_logger && ./out/my_logger