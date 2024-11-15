#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

typedef struct Node node;

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
    // printf("printing the list: \n");
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

node * grredy_solver(node * head, int no_of_towns, int d) {

    node * stations_head = NULL, * j, * i = head;
    insertEnd(&stations_head, head->data+d);
    j = stations_head;
    i = head->next;
    // printf("\n i = %d\n", i->data);
    // printf("\n j = %d\n", j->data);

    for (size_t t = 1; t < no_of_towns; t++)
    {
        if (i->data <= (j->data+d)){
            i = i->next;
            continue;
        }
        else {
            insertEnd(&stations_head, i->data+d);
            // printList(stations_head);
            j = j-> next;
        }
        i = i->next;
    }
    return stations_head;
}

int main() {
    struct Node* head = NULL;

    // insertFront(&head, 2);
    // insertFront(&head, 1);
    // insertEnd(&head, 3);
    // insertEnd(&head, 4);

    // printList(head);

    int no_of_towns;
    printf("Enter number of towns: ");
    scanf("%d", &no_of_towns);

    printf("\nEnter the town coordiantes below: \n");

    for (size_t i = 0; i < no_of_towns; i++)
    {
        int temp;
        scanf("%d", &temp);
        // node * got_a_node = newNode(temp);
        insertEnd(&head, temp);
    }
    printf("Your station coordinates are: ");
    printList(head);

    int d;
    printf("Enter d value: ");
    scanf("%d", &d);

    node * stations = NULL;
    node * stations_head = grredy_solver(head, no_of_towns, d);

    printf("----\n");
    printf("Your stations coordinates will be: ");
    printList(stations_head);

    return 0;
}