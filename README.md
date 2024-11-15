# ADSA-assignment-2
ADSA assignmnet 2 consisting of problems for DP and greedy methods


------
problem-02 file: "problem-2-attempt-2.c"
Code Flow Documentation:
1. Includes and Definitions - 
Includes stdio.h for input/output and stdlib.h for dynamic memory allocation.
Defines a Node structure for a doubly linked list with:
data: Holds the coordinate value of a town.
next: Points to the next node.
prev: Points to the previous node.

2. Helper Functions - 
Node Management
newNode(int data):

Creates a new doubly linked list node with the given data.
Sets next and prev pointers to NULL.
insertFront(struct Node** head_ref, int new_data):

Inserts a new node at the beginning of the doubly linked list.
Updates the prev pointer of the current head to link with the new node.
insertEnd(struct Node** head_ref, int new_data):

Inserts a new node at the end of the doubly linked list.
Traverses the list to find the last node, then updates its next pointer to the new node.
printList(struct Node* node):

Traverses the list and prints the data value of each node.


3. Core Logic - 
Greedy Algorithm for Station Placement
grredy_solver(node *head, int no_of_towns, int d):
Solves the problem of placing stations such that each town is within a distance d of a station.
Steps:
Initializes the station list (stations_head).
Adds the first station at the position head->data + d.
Traverses the town list (head) with pointers:
i: Tracks the current town.
j: Tracks the last station placed.
For each town:
If the town is within the range of the last station (j->data + d), no action is taken.
Otherwise, a new station is added at i->data + d, and j is updated.
Returns the list of station coordinates.


4. Main Function - 
Input Handling

Prompts the user to enter the number of towns (no_of_towns) and their coordinates.
Constructs a doubly linked list (head) using insertEnd to represent the town coordinates.
Reads the maximum allowed distance (d) for station placement.
Station Placement

Calls grredy_solver to determine the coordinates of the stations.
Prints the original town coordinates and the station coordinates.
Example Walkthrough
Input:
yaml
Copy code
Number of towns: 5
Town coordinates: 1 3 7 12 20
Distance (d): 5
Execution:
Constructs the town list:

rust
Copy code
Head -> 1 <-> 3 <-> 7 <-> 12 <-> 20
Station Placement:

First station at 1 + 5 = 6.
Towns 3 and 7 are within the range [1, 6].
Second station at 12 + 5 = 17.
Town 20 is beyond 17 + 5, so no further station is needed.
Station List:

rust
Copy code
Head -> 6 <-> 17
Output:
yaml
Copy code
Your station coordinates are: 1 3 7 12 20 
Your stations coordinates will be: 6 17
Key Observations
Time Complexity:

O(n) for traversing the town list.
Efficient for large input sizes.
Space Complexity:

Uses a doubly linked list for input towns and stations, making memory usage linear in terms of n.
Potential Improvements:

Add error handling for invalid input or memory allocation failures.
Optimize greedy solver to handle edge cases, such as overlapping station ranges or identical town coordinates.