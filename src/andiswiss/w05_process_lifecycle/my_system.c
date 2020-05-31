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


void getInput(char *input) {
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
}

int main(void) {
    char input[100] = "0";

    getInput(input);

    while (input[0] != '0' && input[0] != 'O') {
        printf("\nNow executing your command: %s\n", input);
        system(input);

        // read another line
        getInput(input);
    }
    printf("Ending the application.\n");
    return 0;
}


// run with:
// make my_system && ./out/my_system
//
//
// NOTE: When compiling, a warning will appear. But the application should nevertheless work.
//
// NOTE 2: For some strange reasons, 'cd ..' or 'cd out'  or any cd command doesn't work ???
//     On the other hand, all the following commands work flawless, like:
//     ls -la
//     apt-get install nano
//     nano my_system.c
//
