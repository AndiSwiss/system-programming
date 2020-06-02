//
// Created by AndiSwiss on 01.06.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * Allocate a node in the heap. Initialize the 'next' with NULL.
 * If the list is NULL, just set the node in the list.
 * Otherwise, iterate through the list, don't forget to keep track of the last visited node
 * As soon as you reach a node where you see with strcmp(..), that you are too far, attach the
 * new node to the previous node.
 * In the new node, point to the next node.
 */


typedef struct node {
    struct node *next;
    char *item;
} Node;

static Node *list = NULL;


void insert(char *item) {
    Node *node = malloc(sizeof(Node));
    node->item = item;
    node->next = NULL;

    if (list == NULL) {
        list = node;
    } else if (strcmp(item, list->item) < 0) {
        // put the node in front of the list:
        node->next = list;
        list = node;
    } else {
        Node *current = list;
        while (current->next != NULL) {
            if (strcmp(item, list->next->item) < 0) {
                node->next = current->next;
                current->next = node;
                return;
            }
            // otherwise, advance a node:
            current = current->next;
        }
        // otherwise, just append the node at the end of the list:
        current->next = node;
    }
}


int main(void) {
    insert("Dorothea");
    insert("Theodor");
    insert("Bertha");
    insert("Dan");
    insert("Zulu");
    insert("Bob");
    insert("Andi");

    int count = 1;
    printf("Node %d: %s\n", count, list->item);
    Node *current = list;
    while (current->next != NULL) {
        count++;
        current = current->next;
        printf("Node %d: %s\n", count, current->item);
    }

    return 0;
}


// run with:
//  make a6_sort_a_list_of_nodes && ./out/a6_sort_a_list_of_nodes