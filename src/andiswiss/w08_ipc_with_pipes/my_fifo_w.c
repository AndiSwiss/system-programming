//
// Created by AndiSwiss on 02.06.20.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>      // needed for flags like O_RDONLY
#include <errno.h>

void writeMessage() {

}

int main(void) {
    char *file = "tmp_fifo";

    // Open the file for writing:
    int fd = open(file, O_WRONLY);
    if (fd == -1) {
        printf("error with open: %d\n", errno);
        perror("open");
        exit(-1);
    }


    // Write two messages to the file:
    char msg1[] = "Hello, my name is Andi. I want to tell you a little story...\n";
    size_t size = sizeof(msg1) / sizeof(msg1[0]);
    ssize_t w1 = write(fd, msg1, size);
    if (w1 == -1) {
        printf("error with write: %d\n", errno);
        perror("write");
        exit(-1);
    }

    char msg2[] = "Well, think of a story yourself; I already had to be creative for composing this code :-)\n";
    size = sizeof(msg2) / sizeof(msg2[0]);
    ssize_t w2 = write(fd, msg2, size);
    if (w2 == -1) {
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

    printf("Sending seemed to be successful. Sent %zd bytes.\n", w1 + w2);


    return 0;
}


// First run the other corresponding file:
// make my_fifo_r && ./out/my_fifo_r
//
// Then, in a second terminal open this file:
// make my_fifo_w && ./out/my_fifo_w
