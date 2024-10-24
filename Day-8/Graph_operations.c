#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure for a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure for the graph
struct Graph {
    int numVertices;
    struct Node** adjLists; // Array of adjacency lists
    int* visited;           // Array to track visited vertices
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (struct Node**) malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*) malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;  // Mark all vertices as unvisited
    }

    return graph;
}

// Function to add an edge to the graph (undirected)
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to display the graph
void displayGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("Vertex %d: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Function for DFS traversal
void DFS(struct Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// Function for BFS traversal
void BFS(struct Graph* graph, int startVertex) {
    int queue[MAX_VERTICES], front = 0, rear = -1;
    graph->visited[startVertex] = 1;
    queue[++rear] = startVertex;

    while (front <= rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                queue[++rear] = adjVertex;
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices = 6;
    struct Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    printf("Graph adjacency list representation:\n");
    displayGraph(graph);

    printf("\nDFS Traversal starting from vertex 0:\n");
    DFS(graph, 0);

    // Reset visited array for BFS
    for (int i = 0; i < vertices; i++)
        graph->visited[i] = 0;

    printf("\n\nBFS Traversal starting from vertex 0:\n");
    BFS(graph, 0);

    return 0;
}
