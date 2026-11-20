/*
 * Selection Sort
 * --------------
 * 1. Find the smallest element in the unsorted part.
 * 2. Swap it with the first element of the unsorted part.
 * 3. Now that position is sorted; repeat for the rest.
 *
 * Time: O(n^2) in all cases. Space: O(1). At most n-1 swaps.
 */
#include <stdio.h>

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void selectionSort(int arr[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min])
                min = j;
        if (min != i) {
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
        printf("After pass %d: ", i + 1);
        printArray(arr, n);
    }
}

int main() {
    int arr[] = {5, 3, 8, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted array: ");
    printArray(arr, n);
    selectionSort(arr, n);
    printf("Sorted array:   ");
    printArray(arr, n);
    return 0;
}
