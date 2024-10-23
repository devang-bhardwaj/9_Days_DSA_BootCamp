#include <stdio.h>
#include <limits.h>

#define V 6  // Number of vertices in the graph

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Function to print the shortest path distances from the source
void printSolution(int dist[], int n) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Dijkstra's algorithm implementation for a graph represented by an adjacency matrix
void dijkstra(int graph[V][V], int src) {
    int dist[V];    // dist[i] will hold the shortest distance from src to i
    int visited[V]; // visited[i] will track whether vertex i has been visited

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance of the source vertex to itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited);

        // Mark the picked vertex as processed
        visited[u] = 1;

        // Update dist[] value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    // Print the constructed distance array
    printSolution(dist, V);
}

int main() {
    // Representation of the graph as an adjacency matrix
    int graph[V][V] = {
        {0, 10, 0, 0, 15, 0},
        {10, 0, 5, 0, 10, 0},
        {0, 5, 0, 5, 0, 5},
        {0, 0, 5, 0, 0, 10},
        {15, 10, 0, 0, 0, 10},
        {0, 0, 5, 10, 10, 0}
    };

    // Run Dijkstra's algorithm from vertex 0
    dijkstra(graph, 0);

    return 0;
}
