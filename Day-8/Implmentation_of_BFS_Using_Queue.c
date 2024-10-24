#include <stdio.h>
#include <stdlib.h>

#define SIZE 100  // Maximum number of vertices

int queue[SIZE], front = -1, rear = -1;  // Queue for BFS traversal

// Function to enqueue an element into the queue
void enqueue(int vertex) {
    if (rear == SIZE - 1) {
        printf("Queue is full\n");
    } else {
        if (front == -1) front = 0;
        queue[++rear] = vertex;
    }
}

// Function to dequeue an element from the queue
int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    } else {
        return queue[front++];
    }
}

// Function to perform BFS on a graph
void bfs(int graph[SIZE][SIZE], int numVertices, int startVertex) {
    int visited[SIZE] = {0};  // Array to mark visited vertices

    // Enqueue the start vertex and mark it as visited
    enqueue(startVertex);
    visited[startVertex] = 1;

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    while (front <= rear) {
        // Dequeue a vertex from the queue
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        // Traverse all adjacent vertices of the dequeued vertex
        for (int i = 0; i < numVertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                enqueue(i);  // Enqueue the adjacent vertex
                visited[i] = 1;  // Mark the vertex as visited
            }
        }
    }
    printf("\n");
}

int main() {
    int numVertices = 6;  // Number of vertices in the graph

    // Graph represented as an adjacency matrix
    int graph[SIZE][SIZE] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 1, 1, 0, 0},
        {1, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 1},
        {0, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    // Start BFS traversal from vertex 0
    bfs(graph, numVertices, 0);

    return 0;
}
