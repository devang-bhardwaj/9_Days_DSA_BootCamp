#include <stdio.h>
#include <conio.h>

#define MAXSIZE 10
int Queue[MAXSIZE];
int front = 0;
int rear= -1;

void main(){
    int choice();
    clrscr();

    do {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                insert(); 
                break;
            case 2:
                delete(); 
                break;
            case 3:
                display(); 
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while (choice!= 4);
    getch();
}
void insert(){
    int n;
    if(rear == MAXSIZE -1){
        printf("Queue Overflow");
    }
    else{
        printf("Enter the element to insert:");
        scanf("%d",&n);
        rear++;
        Queue[rear]=n;
    }
}
void delete(){
    int n;
    if(front>rear){
        printf("Queue Underflow\n");
    }
    else{
        n = Queue[front];
        front++;
        printf("popped element is %d",n);
    }
}
void display(){
    int i;
    if(front>rear){
        printf("Queue Is Empty \n");
    }
    else{
        print("Queue elements are: \n");
            for(int i = rear; i >=front; i--){
                printf("%d ",Queue[i]);
            }
    }
}
