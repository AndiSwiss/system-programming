//
// Created by AndiSwiss on 01.06.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * IDEA:
 * Firstly, I reverse the order of the given args in an outer for-loop
 *
 * VERSION 1:
 * Secondly, Since we may use strlen(..), I first create an array for each word, filling it in the reverse order with
 * each character
 *
 * VERSION 2:
 * A more compact version: I just point to the last character of the word, then reducing the pointer each time by 1.
 */

void version1(char *word) {
    int len = (int) strlen(word);
    char reversed[len];
    int pos = len - 1;
    // store each char
    for (char *c = word; *c != '\0'; c++) {
        reversed[pos--] = *c;
    }
    // print each word:
    for (int j = 0; j < len; ++j) {
        printf("%c", reversed[j]);
    }
    printf(" ");
}

void version2(char *word) {
    int len = (int) strlen(word);
    for (int i = len - 1; i >= 0; --i) {
        char *c = word + i;
        printf("%c", *c);
    }
    printf(" ");
}

int main(int argc, char *argv[]) {
    printf("The args for your application %s are:\n", argv[0]);
    for (int i = argc - 1; i > 0; i--) {
//        version1(argv[i]);
        version2(argv[i]);
    }
    printf("\n");
    return 0;
}


// run with something like
//  make a3 && ./out/a3 This is just a test.