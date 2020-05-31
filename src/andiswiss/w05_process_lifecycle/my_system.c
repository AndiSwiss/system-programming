//
// Created by AndiSwiss on 31.05.20.
//
// (not part of a hands-on)

// trying out   int system(const char *cmd);
// https://www.man7.org/linux/man-pages/man3/system.3.html
//
// and gets() and scanf()
// see https://www.tutorialspoint.com/cprogramming/c_input_output.htm


#include <stdio.h>
#include <stdlib.h>


int main(void) {
    char input[100] = "0";

    printf("\n\n\n---\nEnter a cmd-command you want to be executed (for terminating the app, enter 0):\n");

    // COOL: with scanf, you can read multiple arguments, even with different formats.
    // If the user doesn't provide the required format (e.g. a string instead of a int),
    // something else is shown instead (e.g. a 0 when choosing an int)
/*
    int i;
    scanf("%s %d", input, &i);
    printf("\nYou entered: %s and the number %d\n", input, i);
*/

    // But for reading a full line, you can use something like:
    gets(input);

    while (input[0] != '0' && input[0] != 'O') {
        printf("\nNow executing your command: %s\n", input);

        system(input);

        printf("\n---\nEnter a cmd-command you want to be executed (for terminating the app, enter 0):\n");
        gets(input);
    }
    printf("Ending the application.\n");
    return 0;
}


// NOTE: when compiling, a warning will appear. But the application should nevertheless work.
//
// run with:
// make my_system && ./out/my_system

