/*
 * Binary Search
 * -------------
 * Condition: the array must be sorted.
 * Check the middle element:
 *   - equal to key   -> found
 *   - key is bigger  -> search only the right half
 *   - key is smaller -> search only the left half
 *
 * Time: O(log n). Both iterative and recursive versions are shown.
 */
#include <stdio.h>

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (key > arr[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int binarySearchRecursive(int arr[], int low, int high, int key) {
    int mid;
    if (low > high)
        return -1;
    mid = low + (high - low) / 2;
    if (arr[mid] == key)
        return mid;
    if (key > arr[mid])
        return binarySearchRecursive(arr, mid + 1, high, key);
    return binarySearchRecursive(arr, low, mid - 1, key);
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};   /* sorted */
    int n = sizeof(arr) / sizeof(arr[0]);
    int keys[] = {23, 91, 4};
    int i, pos;

    for (i = 0; i < 3; i++) {
        pos = binarySearch(arr, n, keys[i]);
        printf("Iterative: key %d -> %s", keys[i], pos != -1 ? "found at index " : "not found");
        if (pos != -1)
            printf("%d", pos);
        printf("\n");
        printf("Recursive: key %d -> index %d\n", keys[i],
               binarySearchRecursive(arr, 0, n - 1, keys[i]));
    }
    return 0;
}
