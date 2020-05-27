//
// Created by Andreas Ambühl on 26.05.20.
//

// see https://github.com/fhnw-syspr-4ibb2/fhnw-syspr-work-01-AndiSwiss

#include <stdio.h>

int checkAlphaNumeric(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    // argc is the amount of arguments
    int success = checkAlphaNumeric(argc, argv);
    if (success == -1) {
        return -1;
    }

    for (int i = 0; i < argc; ++i) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(", ");
        }
    }
    printf("\n");
}


int checkAlphaNumeric(int argc, char *argv[]) {
    // check whether it is only alpha-numeric lowercase:
    for (int i = 1; i < argc; ++i) {
        for (char *c = argv[i]; *c != '\0' ; c++) {
            if ((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z') || (*c >= '0' && *c <= '9')) {
                continue;
            }
            printf("ERROR: args must contain [a-z], [A-Z] or [0-9]. But you provided: %c\n", *c);
            return -1;
        }
    }

    // When this is reached, everything is fine:
    return 0;
}

// run with:
// make w01c_my_args && ./out/w01c_my_args
// e.g.:
// make w01c_my_args && ./out/w01c_my_args "hi" ccc 32

// The following will produce an error:
// make w01c_my_args && ./out/w01c_my_args "hi" ccc 32.22
