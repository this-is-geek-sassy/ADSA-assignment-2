#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10000

// Node structure for a doubly linked list
struct Node {
    char data;
    struct Node *prev, *next;
};
typedef struct Node node;

char stack[MAX_SIZE];
char palindrome[MAX_SIZE];

int top = -1, pointer = -1;

// Function to return the n-th element in the linked list
int get_Nth_element(struct Node* head, int n) {
    struct Node* current = head;
    int count = 0;

    // Traverse the list
    while (current != NULL) {
        if (count == n) {
            return current->data; // Return the data of the n-th node
        }
        count++;
        current = current->next;
    }

    // If we reach here, the n-th element does not exist
    printf("Error: Index out of range.\n");
    return -1; // Error code for invalid index
}

void push_in_stack(char data) {
    if (top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    top++;
    stack[top] = data;
    printf("%c pushed to stack\n", data);
}

int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    int data = stack[top];
    top--;
    return data;
}

void display_stack(char * container, int top) {
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= top; i++) {
        printf("%c ", container[i]);
    }
    printf("\n");
}

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

int find_palindromic_subsequence(char * sample_string, int i, int j, int ** table, node * list) {

    if (i > j) {
        printf("Invalid case!\n");
        // exit(1);
        return 0;
    }
    if (i==j) {
        return table[i][i];
    }

    if (table[i][j] != 0)
            return table[i][j];
    
    if (get_Nth_element(list, i) == get_Nth_element(list, j)) {

        push_in_stack(get_Nth_element(list, i));
        // palindrome[++pointer] = sample_string[i];
        printf("%d %d \n", i, j);

        table[i][j] = find_palindromic_subsequence(sample_string, i+1, j-1, table, list) + 2;
        return table[i][j];
    }
    else {
        
        table[i+1][j] = find_palindromic_subsequence(sample_string, i+1, j, table, list);
        
        table[i][j-1] = find_palindromic_subsequence(sample_string, i, j-1, table, list);
        
        table[i][j] = max(table[i+1][j], table[i][j-1]);
        return table[i][j];
    }
}

void writeMatrixToCSV(int rows, int cols, int **matrix, const char* filename) {
    // Open the file in write mode
    FILE *file = fopen(filename, "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    // Write the matrix to the file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);
            // Add a comma if it's not the last column
            if (j < cols - 1) {
                fprintf(file, ",");
            }
        }
        // End the row with a newline
        fprintf(file, "\n");
    }

    // Close the file
    fclose(file);

    printf("Matrix successfully written to %s\n", filename);
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

    int length_of_palindrome = find_palindromic_subsequence(sample_string, 0, n-1, table, head);
    printf("LENGTH OF PALINDROME: %d \n", length_of_palindrome);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            printf("%d ", table[i][j]);
        }
        printf("\n");
        // table[i][i] = 1;
    }

    writeMatrixToCSV(n, n, table, "table.csv");
    // display_stack(stack, top);
    // display_stack(palindrome, pointer);

    char palindromic_seq[length_of_palindrome];

    int i = 0, j = n-1, right = length_of_palindrome-1, left = 0;

    while (i <= j)
    {
        printf("i = %d, j = %d\n", i, j);
        if (get_Nth_element(head, i) == get_Nth_element(head, j)) {
            palindromic_seq[left++] = get_Nth_element(head, i);
            palindromic_seq[right--] = get_Nth_element(head, j);
            i++;
            j--;
            printf("%c \n", palindromic_seq[left-1]);
        }
        else if (table[i][j] == 1){
            palindromic_seq[right] = get_Nth_element(head, i);
            break; 
        }
        else if (right == left)
        {
            palindromic_seq[right] = get_Nth_element(head, i);
        }

        else if (table[i][j] == table[i][j-1]) {
            j--;
        }
        else if (table[i][j] == table[i+1][j]) {
            i++;
        }
        
        
        // i++;
        // j--;
    }
    printf("Final palindrome string: \n");
    for (size_t i = 0; i < length_of_palindrome; i++)
    {
        printf("%c ", palindromic_seq[i]);
    }
    printf("\n");
    

    return 0;
}