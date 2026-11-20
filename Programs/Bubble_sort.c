/*
 * Bubble Sort
 * -----------
 * Repeatedly swap neighbours that are in the wrong order. After each pass
 * the largest remaining element "bubbles" to the end.
 * If a pass makes no swaps, the array is already sorted (early stop).
 *
 * Time: O(n^2) worst/average, O(n) best (already sorted). Space: O(1).
 */
#include <stdio.h>

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void bubbleSort(int arr[], int n) {
    int i, j, temp, swapped;
    for (i = 0; i < n - 1; i++) {           /* pass number */
        swapped = 0;
        for (j = 0; j < n - 1 - i; j++) {   /* last i elements are sorted */
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        printf("After pass %d: ", i + 1);
        printArray(arr, n);
        if (!swapped)
            break;
    }
}

int main() {
    int arr[] = {5, 3, 8, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted array: ");
    printArray(arr, n);
    bubbleSort(arr, n);
    printf("Sorted array:   ");
    printArray(arr, n);
    return 0;
}
