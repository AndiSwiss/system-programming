

#include "./linked_f.c"

//Function declaration if NOT using #include "linked_f.c"
//void f(void);


int main() {
    f();
    return 0;
}

// NOTE: this doesn't compile with make, UNLESS:
//  you omit the function declaration, and INSTEAD use  #include "linked_f.c"
// when using make,  only compile the linked_main!!
// -> make linked_main

// For successful compiling AND linking, use the following commands:
// mkdir out
// gcc -o ./out/linked_app linked_main.c linked_f.c