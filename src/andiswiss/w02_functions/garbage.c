//
// Created by tamberg
//

#include <stdio.h>

void keep_secret() {
    int secret = 1337;
    printf("address of the secret:   &secret = %p\n", &secret);
}

void show_secret() {
    //printf("%d\n", secret); // not visible
    int garbage; // not initialised
    printf("address of the garbage: &garbage = %p  -- THE SAME ADDRESS!!\n", &garbage);
    printf("%d  (before initializing - exposing the previous value from secret!!)\n", garbage);

    // ALWAYS good to initialize for not having funny values:
    garbage = 0;
    printf("%d     (after initializing - safer!)\n", garbage);
}

int main() {
    keep_secret();
    show_secret();
}