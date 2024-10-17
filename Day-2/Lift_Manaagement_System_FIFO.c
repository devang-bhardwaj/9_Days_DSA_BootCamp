#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 10

typedef struct {
    int floor;
    char direction;
} Request;

void processLiftRequests(Request requests[], int requestCount) {
    int currentFloor = 0;
    printf("Lift starting operation from floor %d.\n", currentFloor);

    for (int i = 0; i < requestCount; i++) {
        int targetFloor = requests[i].floor;
        char direction = requests[i].direction;

        printf("Processing request for floor %d in direction %c...\n", targetFloor, direction);
        
        while (currentFloor < targetFloor) {
            currentFloor++;
            printf("Lift moving up to floor %d...\n", currentFloor);
        }
        while (currentFloor > targetFloor) {
            currentFloor--;
            printf("Lift moving down to floor %d...\n", currentFloor);
        }

        printf("Arrived at floor %d in direction %c.\n", currentFloor, direction);
    }
    printf("All requests completed. Lift is now at floor %d.\n", currentFloor);
}

int main() {
    printf("Lift is starting to operate from floor 0/G.\n");
    
    Request requests[MAX_REQUESTS];
    int requestCount = 0;
    
    printf("Enter the number of lift requests (up to %d): ", MAX_REQUESTS);
    scanf("%d", &requestCount);

    for (int i = 0; i < requestCount; i++) {
        printf("Enter the floor number (0 to 10): ");
        scanf("%d", &requests[i].floor);
        printf("Enter direction (U for Up, D for Down): ");
        scanf(" %c", &requests[i].direction);
    }

    processLiftRequests(requests, requestCount);
    
    return 0;
}