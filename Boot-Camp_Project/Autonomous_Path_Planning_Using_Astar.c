#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 10
#define COL 10

typedef struct {
    int row, col;
} Point;

typedef struct {
    Point parent;
    int f, g, h;
} Node;

typedef struct {
    int size;
    Node data[ROW * COL];
} PriorityQueue;

void initPriorityQueue(PriorityQueue* pq) {
    pq->size = 0;
}

int isQueueEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

void insert(PriorityQueue* pq, Node node) {
    pq->data[pq->size] = node;
    pq->size++;
}

Node removeMin(PriorityQueue* pq) {
    int minIndex = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->data[i].f < pq->data[minIndex].f) {
            minIndex = i;
        }
    }
    Node minNode = pq->data[minIndex];
    pq->data[minIndex] = pq->data[--pq->size]; // Replace with last element
    return minNode;
}

int isValid(int grid[ROW][COL], int row, int col) {
    return (row >= 0 && row < ROW && col >= 0 && col < COL && grid[row][col] == 0);
}

int isDestination(Point p, Point dest) {
    return (p.row == dest.row && p.col == dest.col);
}

int calculateH(Point a, Point b) {
    return abs(a.row - b.row) + abs(a.col - b.col);
}

void tracePath(Point parent[ROW][COL], Point dest, int grid[ROW][COL]) {
    int path[ROW][COL] = {0};
    Point current = dest;
    
    while (!(current.row == -1 && current.col == -1)) {
        path[current.row][current.col] = 1;
        current = parent[current.row][current.col];
    }
    
    printf("Path found!\n\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (path[i][j])
                printf("* ");  // Path
            else if (grid[i][j] == 1)
                printf("# ");  // Obstacle
            else
                printf("_ ");  // Free space
        }
        printf("\n");
    }
}

void aStarSearch(int grid[ROW][COL], Point start, Point dest) {
    if (!isValid(grid, start.row, start.col) || !isValid(grid, dest.row, dest.col)) {
        printf("Invalid start or destination.\n");
        return;
    }

    if (isDestination(start, dest)) {
        printf("We are already at the destination!\n");
        return;
    }

    int closedList[ROW][COL] = {0};
    Point parent[ROW][COL];

    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            parent[i][j] = (Point){-1, -1};

    PriorityQueue openList;
    initPriorityQueue(&openList);

    Node startNode = {start, 0, 0, calculateH(start, dest)};
    insert(&openList, startNode);

    while (!isQueueEmpty(&openList)) {
        Node current = removeMin(&openList);
        Point p = current.parent;

        if (isDestination(p, dest)) {
            tracePath(parent, dest, grid);
            return;
        }

        closedList[p.row][p.col] = 1;

        Point neighbors[4] = {{p.row - 1, p.col}, {p.row + 1, p.col}, {p.row, p.col - 1}, {p.row, p.col + 1}};

        for (int i = 0; i < 4; i++) {
            Point n = neighbors[i];

            if (isValid(grid, n.row, n.col) && !closedList[n.row][n.col]) {
                int gNew = current.g + 1;
                int hNew = calculateH(n, dest);
                int fNew = gNew + hNew;

                insert(&openList, (Node){n, fNew, gNew, hNew});
                parent[n.row][n.col] = p;
            }
        }
    }

    printf("No path found.\n");
}

int main() {
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

    Point start = {0, 0};
    Point dest = {9, 9};

    aStarSearch(grid, start, dest);

    return 0;
}
