//
// Created by Andreas Ambühl on 26.05.20.
//
#include <stdio.h>
#include <stdlib.h>   // needed for the malloc(...)!!

typedef struct node {
    struct node *left;
    struct node *right;
    char *label;
} Node;

int printChildren(Node node);

void goThroughDescendants(Node node);

int main(void) {
    // Reserve memory on heap:
    Node *root = malloc(sizeof(Node));
    Node *childL = malloc(sizeof(Node));
    Node *childR = malloc(sizeof(Node));
    Node *grandchildLL = malloc(sizeof(Node));
    Node *grandchildLR = malloc(sizeof(Node));
    Node *grandchildRL = malloc(sizeof(Node));
    Node *grandchildRR = malloc(sizeof(Node));
    Node *greatgrandchildLLL = malloc(sizeof(Node));
    Node *greatgrandchildLLR = malloc(sizeof(Node));
    Node *greatgrandchildLRL = malloc(sizeof(Node));
    Node *greatgrandchildLRR = malloc(sizeof(Node));
    Node *greatgrandchildRLL = malloc(sizeof(Node));
    Node *greatgrandchildRLR = malloc(sizeof(Node));
    Node *greatgrandchildRRL = malloc(sizeof(Node));
    Node *greatgrandchildRRR = malloc(sizeof(Node));

    // Labels:
    root->label = "root";
    childL->label = "childL";
    childR->label = "childR";
    grandchildLL->label = "grandchildLL";
    grandchildLR->label = "grandchildLR";
    grandchildRL->label = "grandchildRL";
    grandchildRR->label = "grandchildRR";
    greatgrandchildLLL->label = "greatgrandchildLLL";
    greatgrandchildLLR->label = "greatgrandchildLLR";
    greatgrandchildLRL->label = "greatgrandchildLRL";
    greatgrandchildLRR->label = "greatgrandchildLRR";
    greatgrandchildRLL->label = "greatgrandchildRLL";
    greatgrandchildRLR->label = "greatgrandchildRLR";
    greatgrandchildRRL->label = "greatgrandchildRRL";
    greatgrandchildRRR->label = "greatgrandchildRRR";

    // Assign children:
    root->left = childL;
    root->right = childR;
    childL->left = grandchildLL;
    childL->right = grandchildLR;
    childR->left = grandchildRL;
    childR->right = grandchildRR;
    grandchildLL->left = greatgrandchildLLL;
    grandchildLL->right = greatgrandchildLLR;
    grandchildLR->left = greatgrandchildLRL;
    grandchildLR->right = greatgrandchildLRR;
    grandchildRL->left = greatgrandchildRLL;
    grandchildRL->right = greatgrandchildRLR;
    grandchildRR->left = greatgrandchildRRL;
    grandchildRR->right = greatgrandchildRRR;

    // According to sample solution, you should also assign NULL to no yet defined children:
    // But it didn't seam to be necessary, because it seems to be set to NULL initially
    // otherwise my code would fail in method printChildren(..)  in  if (node.left != NULL)...
//    greatgrandchildLLL->left = NULL;
//    greatgrandchildLLL->right = NULL;
    //...

    printChildren(*root);

    // a recursively defined function:
    goThroughDescendants(*root);

    printf("A specific greatgrandchild: %s\n", root->right->left->right->label);

    printf("childL (before free): %s\n", root->left->label);

    // Don't forget to free the memory:
    free(root);
    free(childL);
    free(childR);
    free(grandchildLL);
    free(grandchildLR);
    free(grandchildRL);
    free(grandchildRR);
    free(greatgrandchildLLL);
    free(greatgrandchildLLR);
    free(greatgrandchildLRL);
    free(greatgrandchildLRR);
    free(greatgrandchildRLL);
    free(greatgrandchildRLR);
    free(greatgrandchildRRL);
    free(greatgrandchildRRR);

    // Not possible anymore:
//    printf("childL (after free): %s\n", root->left->label);

    return 0;
}

// print out some children:
int printChildren(Node node) {
    int success = -1;
    if (node.left != NULL) {
        printf("%s\n", node.left->label);
        success = 0;
    }
    if (node.right != NULL) {
        printf("%s\n", node.right->label);
        success = 0;
    }
    return success;
}

void goThroughDescendants(Node node) {
    Node *p = &node;
    Node *pL = p->left;
    Node *pR = p->right;
    int successL = printChildren(*pL);
    int successR = printChildren(*pR);

    // Recursive calls:
    if (successL == 0) goThroughDescendants(*p->left);
    if (successR == 0) goThroughDescendants(*p->right);
}


// run with:
// make w01d_my_tree && ./out/w01d_my_tree