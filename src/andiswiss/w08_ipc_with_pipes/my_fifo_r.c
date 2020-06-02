//
// Created by AndiSwiss on 02.06.20.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>     // needed for flags like O_RDONLY
#include <errno.h>

#define BUF_SIZE 16


int main(void) {
    char *file = "tmp_fifo";


    // If previous attempts might have failed, the file may be still on the file system. Hence remove it:
    if (remove(file) == 0) {
        printf("Removed already existing file %s.\n", file);
    }

    // Create the file:
    if (mkfifo(file, S_IRUSR | S_IWUSR) == -1) {
        printf("error with mkfifo: %d\n", errno);
        perror("mkfifo");
        exit(-1);
    }

    // Open the file  - this will block until a second process opens the file with open() with O_WRONLY
    printf("\nWaiting for sender to send a message...\n");
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        printf("error with open: %d\n", errno);
        perror("open");
        exit(-1);
    }

    printf("Receiving message:\n");
    // Read from the file
    char buf[BUF_SIZE];
    ssize_t r = read(fd, buf, BUF_SIZE);
    if (r == -1) {
        printf("error with read: %d\n", errno);
        perror("read");
        exit(-1);
    }

    while (r != 0) {
//        printf("%s", buf);
        // Note: This simple solution of just printing the buffer as a string, doesn't work nice on longer messages:
        // When exceeding the buffer size, it prints funny things after the defined BUF_SIZE (here: 16), such as:
        // Hello, my name iP�T��s Andi. I want tP�T��o tell you a litP�T��tle story...
        //
        // Better: print char by char:
        for (int i = 0; i < r; ++i) {
            printf("%c", buf[i]);
        }

        r = read(fd, buf, BUF_SIZE);
        if (r == -1) {
            printf("error with read: %d\n", errno);
            perror("read");
            exit(-1);
        }
    }

    // Close the file (maybe not needed, e.g. this is not present in the sample solution)
    if (close(fd) == -1) {
        printf("error with close: %d", errno);
        perror("close");
        exit(-1);
    }

    // Remove the file when done:
    if (remove(file) == -1) {
        printf("error with remove: %d", errno);
        perror("remove");
        exit(-1);
    }
}

// run with:
// make my_fifo_r && ./out/my_fifo_r
//
// in a second terminal open the corresponding file:
// make my_fifo_w && ./out/my_fifo_w