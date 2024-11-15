#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node * newNode(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;

}

// Function to insert a new node at the beginning
void insertFront(struct Node** head_ref, int new_data) {
    struct Node* new_node = newNode(new_data);
    new_node->next = (*head_ref);
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;
    (*head_ref) = new_node;
}

// Function to insert a new node at the end
void insertEnd(struct Node** head_ref, int new_data) {
    struct Node* new_node = newNode(new_data);
    struct Node* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;

}

// Function to print the linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;

    insertFront(&head, 2);
    insertFront(&head, 1);
    insertEnd(&head, 3);
    insertEnd(&head, 4);

    printList(head);

    return 0;
}