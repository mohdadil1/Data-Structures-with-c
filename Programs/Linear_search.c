/*
 * Linear Search
 * -------------
 * Check every element one by one until the key is found.
 * Works on any array, sorted or not.
 *
 * Time: O(n) worst, O(1) best (key at the first position).
 */
#include <stdio.h>

int linearSearch(int arr[], int n, int key) {
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] == key)
            return i;               /* index where key was found */
    return -1;                      /* key not present */
}

int main() {
    int arr[] = {10, 25, 7, 18, 42, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int keys[] = {18, 50};
    int i, pos;

    for (i = 0; i < 2; i++) {
        pos = linearSearch(arr, n, keys[i]);
        if (pos != -1)
            printf("Search for key = %d: found at index %d\n", keys[i], pos);
        else
            printf("Search for key = %d: not found\n", keys[i]);
    }
    return 0;
}
