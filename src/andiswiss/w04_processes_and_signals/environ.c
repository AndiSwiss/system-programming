//
// Created by tamberg
// Extended by AndiSwiss
//


#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

void print_environ() {
    char** p = environ;
    while (*p != NULL) {
        printf("%s\n", *p);
        p++;
    }
}

void setenv_const() {
    int overwrite = 0; // don't overwrite the value if the name exists
    setenv("MY_CONST_VAR", "hola", overwrite); // requires _BSD_SOURCE
}

void putenv_heap() {
    const int N = 18;
    char *my_var = (char *) malloc(N * sizeof(char));
    strcpy(my_var, "MY_HEAP_VAR=hello");
    putenv(my_var); // string must be heap allocated
}

void getenv_both() {
    char *term = getenv("TERM");
    printf("TERM=%s\n", term);
    char *my_heap_var = getenv("MY_HEAP_VAR");
    printf("MY_HEAP_VAR=%s\n", my_heap_var);
    char *my_const_var = getenv("MY_CONST_VAR");
    printf("MY_CONST_VAR=%s\n", my_const_var);
}

int main() {
    print_environ();
    setenv_const();
    putenv_heap();
    sleep(1);
    // Note: if you enable   'print_environ' AFTER the setting of the environment variables, they will get listed:
    printf("\n-------------------\nAFTER setting the env-variables (coming in 2 seconds...):\n");
    sleep(2);
    print_environ();
    sleep(1);
    printf("\n-------------------\nGetting some env-variables (coming in 2 seconds...):\n");
    sleep(2);
    getenv_both();
    return 0;
}