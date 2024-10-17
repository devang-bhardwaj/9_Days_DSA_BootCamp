#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* add;
};

struct Node* start = NULL;

void create() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // memory allot
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    printf("Enter data: ");
    scanf("%d", &newNode->data);
    newNode->add = NULL;

    if (start == NULL) { // agar start NULL ha to 
        start = newNode;
    } else {
        struct Node* temp = start; // copy of start
        while (temp->add != NULL) { // jab tk temp ka add NULL Nhi hai
            temp = temp->add;
        }
        temp->add = newNode;
    }
    printf("Node created successfully.\n");
}

void insertBeginning() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    printf("Enter data: ");
    scanf("%d", &newNode->data);
    newNode->add = start;
    start = newNode;
    printf("Node inserted at the beginning.\n");
}

void insertEnd() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    printf("Enter data: ");
    scanf("%d", &newNode->data);
    newNode->add = NULL;

    if (start == NULL) {
        start = newNode;
    } else {
        struct Node* temp = start;
        while (temp->add != NULL) {
            temp = temp->add;
        }
        temp->add = newNode;
    }
    printf("Node inserted at the end.\n");
}

void insertMiddle() {
    int position;
    printf("Enter position to insert: ");
    scanf("%d", &position);

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    printf("Enter data: ");
    scanf("%d", &newNode->data);

    if (position == 1 || start == NULL) {
        newNode->add = start;
        start = newNode;
    } else {
        struct Node* temp = start;
        for (int i = 1; i < position - 1 && temp != NULL; i++) {
            temp = temp->add;
        }
        if (temp == NULL) {
            printf("Position out of range.\n");
            free(newNode);
            return;
        }
        newNode->add = temp->add;
        temp->add = newNode;
    }
    printf("Node inserted at position %d.\n", position);
}

void deleteBeginning() {
    if (start == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = start;
    start = start->add;
    free(temp);
    printf("Node deleted from the beginning.\n");
}

void deleteEnd() {
    if (start == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (start->add == NULL) {
        free(start);
        start = NULL;
    } else {
        struct Node* temp = start;
        while (temp->add->add != NULL) {
            temp = temp->add;
        }
        free(temp->add);
        temp->add = NULL;
    }
    printf("Node deleted from the end.\n");
}

void deleteMiddle() {
    if (start == NULL) {
        printf("List is empty.\n");
        return;
    }
    int position;
    printf("Enter position to delete: ");
    scanf("%d", &position);

    if (position == 1) {
        struct Node* temp = start;
        start = start->add;
        free(temp);
    } else {
        struct Node* temp = start;
        struct Node* prev = NULL;
        for (int i = 1; i < position && temp != NULL; i++) {
            prev = temp;
            temp = temp->add;
        }
        if (temp == NULL) {
            printf("Position out of range.\n");
            return;
        }
        prev->add = temp->add;
        free(temp);
    }
    printf("Node deleted from position %d.\n", position);
}

void display() {
    if (start == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = start;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->add;
    }
    printf("NULL\n");
}
void main() {
    int choice;

    while (1) {
        printf("\nLinked List Menu\n");
        printf("1. Create\n");
        printf("2. Insert at beginning\n");
        printf("3. Insert at end\n");
        printf("4. Insert at middle\n");
        printf("5. Delete from beginning\n");
        printf("6. Delete from end\n");
        printf("7. Delete from middle\n");
        printf("8. Display\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                insertBeginning();
                break;
            case 3:
                insertEnd();
                break;
            case 4:
                insertMiddle();
                break;
            case 5:
                deleteBeginning();
                break;
            case 6:
                deleteEnd();
                break;
            case 7:
                deleteMiddle();
                break;
            case 8:
                display();
                break;
            case 9:
                printf("Exiting\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
