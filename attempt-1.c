#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for a doubly linked list
struct Node {
    char data;
    struct Node *prev, *next;
};
typedef struct Node node;

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a new node at the beginning of the list
void push(struct Node** head_ref, int new_data) {
    // 1. Allocate a new node
    struct Node* new_node = newNode(new_data);

    // 2. Make next of new node as head node
    new_node->next = (*head_ref);

    // 3. Change prev of head node as new node
    if ((*head_ref) != NULL)/* code */
        (*head_ref)->prev = new_node;

    // 4. Move the head to point to the new node
    (*head_ref) = new_node;
}

// Function to insert a new node at the end of the list
void append(struct Node** head_ref, struct Node** tail_ref, int new_data) {
    // 1. Allocate a new node
    struct Node* new_node = newNode(new_data);

    // 2. If the linked list is empty, make the new node as head
    if (*head_ref == NULL) {
        *head_ref = new_node;
        *tail_ref = new_node;
        return;
    }

    // 3. Set the next of last node as new node, and make next of new node as NULL
    (*tail_ref)->next = new_node;
    new_node->prev = *tail_ref;

    // 4. Move tail to point to the new node
    *tail_ref = new_node;
}

// Function to print the linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%c ", node->data);
        node = node->next;
    }
    printf("\n");
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int find_palindromic_subsequence(char * sample_string, int i, int j, int ** table) {

    if (i > j) {
        printf("SOMETHING TERRIBLY WRONG!!\n");
        exit(1);
    }
    if (i==j) {
        return table[i][i];
    }
    if (sample_string[i] == sample_string[j]) {
        if (table[i][j] != 0)
            return table[i][j];
        table[i][j] = find_palindromic_subsequence(sample_string, i+1, j-1, table) + 2;
        return table[i][j];
    }
    else {
        if (table[i+1][j] == 0)
            table[i+1][j] = find_palindromic_subsequence(sample_string, i+1, j, table);
        
        if (table[i][j-1] == 0)
            table[i][j-1] = find_palindromic_subsequence(sample_string, i, j-1, table);
        
        table[i][j] = max(table[i+1][j], table[i][j-1]);
        return table[i][j];
    }
}

int main() {
    struct Node* head = NULL, *tail = NULL;

    // Create the list 10->20->30->40->50
    // append(&head, &tail, 100);
    // push(&head, 80);
    // push(&head, 70);
    // append(&head, &tail, 84);
    // append(&head, &tail, 95);

    // printf("Created Doubly Linked List is: ");
    // printList(head);

    int n;
    printf("Enter the length of the string: ");
    scanf("%d", &n);

    char sample_string[n];

    getchar();
    printf("\nEnter a string length less than length n: ");
    fgets(sample_string, 100, stdin);

    printf("You entered: %s", sample_string);
    
    for (size_t i = 0; i < strlen(sample_string); i++)
    {
        append(&head, &tail, sample_string[i]);
    }

    printList(head);

    // defining a 2D matrix for memoization
    int ** table = (int ** )malloc(n * sizeof(int *));

    for (size_t i = 0; i < n; i++)
    {
        table[i] = calloc(n, sizeof(int));
    }

    for (size_t i = 0; i < n; i++)
    {
        // for (size_t j = 0; j < n; j++)
        // {
        //     printf("%d ", table[i][j]);
        // }
        // printf("\n");
        table[i][i] = 1;        
    }
    printf("%d \n", find_palindromic_subsequence(sample_string, 0, n-1, table));

    return 0;
}