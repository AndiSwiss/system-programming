//
// Created by AndiSwiss on 27.05.20.
//

#include <stdio.h>
#include <fcntl.h>    // needed for open(...)
#include <unistd.h>   // needed for close(...) and more

#define BUFFER_SIZE 128


int main(void) {
    int logFd, uptimeFd;
    ssize_t r;
    char buffer[BUFFER_SIZE];

    // Open log file
    logFd = open("./my.log", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (logFd == -1) {
        printf("ERROR with log-file: ./my.log  -> see next line for error-message:\n");
        perror("open");
        return -1;
    }

    // Instead of just using the flag  | O_APPEND, you can also use lseek to reach the end of the file:
    lseek(logFd, 0, SEEK_END);

    // Continuous logging (once every second):
    while (1) {
        // Open source file
        uptimeFd = open("/proc/uptime", O_RDONLY);
        if (uptimeFd == -1) {
            printf("ERROR with opening /proc/uptime. -> See next line for error-message:\n");
            perror("open");
            return -1;
        }
        // Read and write:
        r = read(uptimeFd, buffer, BUFFER_SIZE);
        close(uptimeFd);
        if (r <= 0) {
            printf("ERROR with reading /proc/uptime. -> See next line for error-message:\n");
            perror("read");
            return -1;
        }
        write(logFd, buffer, r);
        printf("logged: %s\n", buffer);
        sleep(1);
    }

    // close the files
    close(logFd);

    return 0;
}




// run with
// make my_logger && ./out/my_logger