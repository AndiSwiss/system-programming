//
// Created by AndiSwiss on 27.05.20.
//

#include <stdio.h>
#include <fcntl.h>    // needed for open(...)
#include <unistd.h>   // needed for close(...) and more

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("ERROR! -- Correct usage:   my_copy source-file target-file\n");
        return -1;
    }

    char *src = argv[1], *target = argv[2];

    printf("my_copy called with src=%s, target=%s\n", src, target);

    // Open source file
    int srcFd = open(src, O_RDONLY);
    if (srcFd == -1) {
        printf("ERROR with source-file: %s  -> see next line for error-message:\n", src);
        perror("open");
        return -1;
    }

    // Open target file
    int targetFd = open(target, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (targetFd == -1) {
        printf("ERROR with target-file: %s  -> see next line for error-message:\n", target);
        perror("open");
        // close the already open source-file:
        close(srcFd);
        return -1;
    }

    // Actual copying of data:
    char buffer[BUFFER_SIZE];
    int r = read(srcFd, buffer, BUFFER_SIZE);
    while (r > 0) {
        write(targetFd, buffer, r);
        r = read(srcFd, buffer, BUFFER_SIZE);
    }

    // close the files
    close(srcFd);
    close(targetFd);

    printf("Copying was successful.\n");
    return 0;
}


// run with
// make my_copy && ./out/my_copy fileA.txt fileB.txt