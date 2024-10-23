#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 10  // Define the number of rows in the grid
#define COL 10  // Define the number of columns in the grid

// Structure to represent a point in the grid
typedef struct {
    int row, col;  // Row and column indices of the point
} Point;

// Structure to represent a node in the priority queue for A* algorithm
typedef struct {
    Point parent;  // Parent point of the current node
    int f, g, h;   // f = g + h, where g is the cost from start to current node, and h is the heuristic cost to the destination
} Node;

// Structure to represent a priority queue for nodes
typedef struct {
    int size;                  // Current number of nodes in the queue
    Node data[ROW * COL];     // Array to store nodes in the queue
} PriorityQueue;

// Initialize the priority queue
void initPriorityQueue(PriorityQueue* pq) {
    pq->size = 0;  // Set the size of the queue to 0
}

// Check if the priority queue is empty
int isQueueEmpty(PriorityQueue* pq) {
    return pq->size == 0;  // Return true if size is 0
}

// Insert a new node into the priority queue
void insert(PriorityQueue* pq, Node node) {
    pq->data[pq->size] = node;  // Add the node to the queue
    pq->size++;  // Increase the size of the queue
}

// Remove and return the node with the smallest f value from the queue
Node removeMin(PriorityQueue* pq) {
    int minIndex = 0;  // Index of the node with minimum f value
    for (int i = 1; i < pq->size; i++) {
        // Update minIndex if a smaller f value is found
        if (pq->data[i].f < pq->data[minIndex].f) {
            minIndex = i;  // Update the index of the node with minimum f value
        }
    }
    Node minNode = pq->data[minIndex];  // Store the minimum node
    pq->data[minIndex] = pq->data[--pq->size]; // Replace it with the last element and decrease the size
    return minNode;  // Return the minimum node
}

// Check if a given cell is valid (inside grid and not an obstacle)
int isValid(int grid[ROW][COL], int row, int col) {
    return (row >= 0 && row < ROW && col >= 0 && col < COL && grid[row][col] == 0);  // Return true if valid
}

// Check if the current point is the destination
int isDestination(Point p, Point dest) {
    return (p.row == dest.row && p.col == dest.col);  // Return true if the point matches destination
}

// Calculate the heuristic (Manhattan distance) between two points
int calculateH(Point a, Point b) {
    return abs(a.row - b.row) + abs(a.col - b.col);  // Return the sum of absolute differences
}

// Trace the path from destination to start and print the grid
void tracePath(Point parent[ROW][COL], Point dest, int grid[ROW][COL]) {
    int path[ROW][COL] = {0};  // Array to mark the path
    Point current = dest;  // Start tracing from the destination
    
    while (!(current.row == -1 && current.col == -1)) {
        path[current.row][current.col] = 1;  // Mark the current point as part of the path
        current = parent[current.row][current.col];  // Move to the parent point
    }
    
    printf("Path found!\n\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (path[i][j])
                printf("* ");  // Print '*' for path points
            else if (grid[i][j] == 1)
                printf("# ");  // Print '#' for obstacles
            else
                printf("_ ");  // Print '_' for free space
        }
        printf("\n");  // Newline for the next row
    }
}

// Implement the A* search algorithm
void aStarSearch(int grid[ROW][COL], Point start, Point dest) {
    // Validate the start and destination points
    if (!isValid(grid, start.row, start.col) || !isValid(grid, dest.row, dest.col)) {
        printf("Invalid start or destination.\n");
        return;  // Exit if invalid
    }

    // Check if we are already at the destination
    if (isDestination(start, dest)) {
        printf("We are already at the destination!\n");
        return;  // Exit if already at destination
    }

    int closedList[ROW][COL] = {0};  // Array to keep track of closed nodes
    Point parent[ROW][COL];  // Array to store parents of each node

    // Initialize the parent array to indicate no parents (-1, -1)
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            parent[i][j] = (Point){-1, -1};  // No parent for any node initially

    PriorityQueue openList;  // Create the open list
    initPriorityQueue(&openList);  // Initialize the open list

    Node startNode = {start, 0, 0, calculateH(start, dest)};  // Create the start node
    insert(&openList, startNode);  // Insert the start node into the open list

    // Main loop for A* search
    while (!isQueueEmpty(&openList)) {
        Node current = removeMin(&openList);  // Remove the node with the smallest f value
        Point p = current.parent;  // Current point

        // Check if we have reached the destination
        if (isDestination(p, dest)) {
            tracePath(parent, dest, grid);  // Trace the path to the destination
            return;  // Exit if destination reached
        }

        closedList[p.row][p.col] = 1;  // Mark the current node as closed

        // Define the neighboring points (up, down, left, right)
        Point neighbors[4] = {{p.row - 1, p.col}, {p.row + 1, p.col}, {p.row, p.col - 1}, {p.row, p.col + 1}};

        // Loop through each neighbor
        for (int i = 0; i < 4; i++) {
            Point n = neighbors[i];  // Current neighbor

            // If the neighbor is valid and not in the closed list
            if (isValid(grid, n.row, n.col) && !closedList[n.row][n.col]) {
                int gNew = current.g + 1;  // Calculate g value for the neighbor
                int hNew = calculateH(n, dest);  // Calculate h value for the neighbor
                int fNew = gNew + hNew;  // Calculate f value for the neighbor

                // Insert the new node into the open list
                insert(&openList, (Node){n, fNew, gNew, hNew});
                parent[n.row][n.col] = p;  // Set the parent of the neighbor to the current point
            }
        }
    }

    printf("No path found.\n");  // If the open list is empty, no path exists
}

int main() {
    // Define the grid (0 = free, 1 = obstacle)
    int grid[ROW][COL] = {
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 1, 1, 1, 1, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0}
    };

    Point start = {0, 0};  // Define the starting point
    Point dest = {9, 9};   // Define the destination point

    aStarSearch(grid, start, dest);  // Call the A*
