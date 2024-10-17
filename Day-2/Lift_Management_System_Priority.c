#include <stdio.h>
#define MAX 10

// Structure to handle lift requests
typedef struct {
    int floor;
    char direction; // 'U' for up, 'D' for down
} Request;

Request queue[MAX];
int front = -1, rear = -1;
int current_floor = 0;
char current_direction = 'U'; // Lift starts by going up

// Enqueue a floor request
void enqueue(int floor, char direction) {
    if (rear == MAX - 1) {
        printf("Queue is full. No more requests can be taken.\n");
        return;
    }
    if (front == -1) front = 0;
    rear++;
    queue[rear].floor = floor;
    queue[rear].direction = direction;
    printf("Request for floor %d in direction %c added.\n", floor, direction);
}

// Dequeue the next request
Request dequeue() {
    Request invalid = {-1, ' '}; // Return invalid request if no requests are left
    if (front == -1 || front > rear) {
        printf("No more requests left.\n");
        return invalid;
    }
    Request req = queue[front];
    front++;
    if (front > rear) front = rear = -1;
    return req;
}

// Function to simulate lift movement
void liftMovement() {
    while (front != -1) {
        Request req = dequeue();
        if (req.floor != -1) {
            printf("Lift moving %s to floor %d.\n", (req.floor > current_floor ? "up" : "down"), req.floor);
            current_floor = req.floor; // Update current floor
        }
    }
}

// Function to prioritize requests in the same direction
void processRequests() {
    while (front != -1) {
        for (int i = front; i <= rear; i++) {
            if (queue[i].direction == current_direction) {
                printf("Processing request for floor %d in direction %c.\n", queue[i].floor, queue[i].direction);
                current_floor = queue[i].floor; // Update lift floor
                // Dequeue this request
                for (int j = i; j < rear; j++) {
                    queue[j] = queue[j + 1];
                }
                rear--;
                if (rear < front) front = rear = -1;
            }
        }
        // Change direction when no requests are available in the current direction
        current_direction = (current_direction == 'U') ? 'D' : 'U';
    }
}

// User inputs
void getUserInputs() {
    int num_requests;
    printf("Enter the number of lift requests: ");
    scanf("%d", &num_requests);
    
    for (int i = 0; i < num_requests; i++) {
        int floor;
        char direction;
        
        printf("Enter the floor number (0 to 10): ");
        scanf("%d", &floor);
        
        printf("Enter direction (U for Up, D for Down): ");
        scanf(" %c", &direction); // Adding space before %c to consume any newline character
        
        enqueue(floor, direction);
    }
}

int main() {
    printf("Lift starting operation from floor %d.\n", current_floor);
    
    // Get user inputs
    getUserInputs();
    
    // Process the lift requests
    processRequests();
    
    printf("All requests completed. Lift is now at floor %d.\n", current_floor);
    
    return 0;
}
