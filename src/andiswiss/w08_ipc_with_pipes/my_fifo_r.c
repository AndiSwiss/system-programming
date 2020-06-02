//
// Created by AndiSwiss on 02.06.20.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>     // needed for flags like O_RDONLY
#include <errno.h>

#define BUF_SIZE 1024



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

    printf("Reading from other process...\n");
    // Read from the file
    char buf[BUF_SIZE];
    ssize_t r = read(fd, buf, BUF_SIZE);
    if (r == -1) {
        printf("error with read: %d\n", errno);
        perror("read");
        exit(-1);
    }

    printf("Received message:\n");
    printf("%s\n", buf);             // Note: in sample solution, this output is done char by char!

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