//
// Created by AndiSwiss on 02.06.20.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>      // needed for flags like O_RDONLY
#include <errno.h>


int main(void) {
    char *file = "tmp_fifo";

    // Open the file for writing:
    int fd = open(file, O_WRONLY);
    if (fd == -1) {
        printf("error with open: %d\n", errno);
        perror("open");
        exit(-1);
    }


    // Write a message to the file:
    char buf[] = "Hello, my name is Andi\n";
    size_t size = sizeof(buf) / sizeof(buf[0]);

    ssize_t w = write(fd, buf, size);
    if (w == -1) {
        printf("error with write: %d\n", errno);
        perror("write");
        exit(-1);
    }

    // Close the file
    if (close(fd) == -1) {
        printf("error with close: %d", errno);
        perror("close");
        exit(-1);
    }

    printf("Sending seemed to be successful. Sent %zd bytes.\n", w);


    return 0;
}


// First run the other corresponding file:
// make my_fifo_r && ./out/my_fifo_r
//
// Then, in a second terminal open this file:
// make my_fifo_w && ./out/my_fifo_w
