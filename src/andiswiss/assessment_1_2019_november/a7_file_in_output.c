//
// Created by AndiSwiss on 01.06.20.
//

/**
 * Based on ../src/andiswiss/w03_file_io/my_copy.c
 */



#include <stdio.h>
#include <fcntl.h>    // needed for open(...)
#include <unistd.h>   // needed for close(...) and more
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("ERROR! -- Correct usage:   a7_file_in_output source-file target-file\n");
        return -1;
    }

    char *src = argv[1], *target = argv[2];

    // Open source file
    int srcFd = open(src, O_RDONLY);
    if (srcFd == -1) {
        printf("ERROR with source-file: %s  -> see next line for error-message:\n", src);
        perror("open");
        return -1;
    }

    // Open target file
    int targetFd = open(target, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    // NOTE: the O_TRUNC-flag erases any previously existing content!

    if (targetFd == -1) {
        printf("ERROR with target-file: %s  -> see next line for error-message:\n", target);
        perror("open");
        // close the already open source-file:
        close(srcFd);
        return -1;
    }

    // Reading all the data at once
    char buffer[BUFFER_SIZE];
    int r = read(srcFd, buffer, BUFFER_SIZE);
    printf("%d bytes read from source-file.\n", r);


    // Writing the data
    if (r < BUFFER_SIZE) {
        int pos = 0;
        char *add[] = {"Legs", "4", "2", "4", "4"};

        // go through all the lines:
        for (int i = 0; i < 5; ++i) {
            // get length of current line:
            int len = 0;
            while (buffer[pos] != '\n') {
                pos++;
                len++;
            }
            // write original content of one line:
            write(targetFd, &buffer[pos - len], len);

            // add new content of that line:
            write(targetFd, ", ", 2);
            write(targetFd, add[i], strlen(add[i]));
            write(targetFd, "\n", 1);

            // Advance position to the next line:
            pos++;
        }
    } else {
        printf("read bytes %d is larger than BUFFER_SIZE = %d -> need a different strategy!\n", r, BUFFER_SIZE);
    }



    // close the files
    close(srcFd);
    close(targetFd);

    printf("\n--- Result: Reading target file with 'system(cat %s);':\n", argv[2]);
    char command[100];
    strcpy(command, "cat ");
    strcat(command, argv[2]);
    system(command);


    return 0;
}


// run with:
//  make a7_file_in_output && ./out/a7_file_in_output table.csv table2.csv