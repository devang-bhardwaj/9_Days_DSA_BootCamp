#include <stdio.h>

// Function to implement Linear Search
int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}

// Function to implement Binary Search
int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int mid = l + (r - l) / 2;

        // Check if x is present at mid
        if (arr[mid] == x)
            return mid;

        // If x greater, ignore left half
        if (arr[mid] < x)
            l = mid + 1;

        // If x is smaller, ignore right half
        else
            r = mid - 1;
    }

    // x is not present in the array
    return -1;
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int choice, x, result;
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    printArray(arr, n);

    printf("\nChoose the search algorithm:\n");
    printf("1. Linear Search\n");
    printf("2. Binary Search\n");
    scanf("%d", &choice);

    printf("Enter the element to search: ");
    scanf("%d", &x);

    switch (choice) {
        case 1:
            result = linearSearch(arr, n, x);
            if (result == -1)
                printf("Element not found in the array using Linear Search.\n");
            else
                printf("Element found at index %d using Linear Search.\n", result);
            break;
        case 2:
            result = binarySearch(arr, 0, n - 1, x);
            if (result == -1)
                printf("Element not found in the array using Binary Search.\n");
            else
                printf("Element found at index %d using Binary Search.\n", result);
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    return 0;
}
