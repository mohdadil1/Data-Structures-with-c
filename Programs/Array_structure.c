/*
 * Array Data Structure (Static, Linear)
 * -------------------------------------
 * An array stores elements in contiguous memory. Size is fixed at
 * compile time, so access is fast (O(1)) but insertion/deletion in the
 * middle is slow (O(n)) because elements must be shifted.
 *
 * Operations: traverse, insert at position, delete at position, search, update
 */
#include <stdio.h>

#define MAX 50

int arr[MAX];
int n = 0;              /* current number of elements */

void traverse() {
    int i;
    if (n == 0) {
        printf("Array is empty\n");
        return;
    }
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* Insert data at index pos (0-based). Elements from pos onward shift right. */
void insert(int pos, int data) {
    int i;
    if (n == MAX) {
        printf("Array is full\n");
        return;
    }
    if (pos < 0 || pos > n) {
        printf("Invalid position\n");
        return;
    }
    for (i = n - 1; i >= pos; i--)
        arr[i + 1] = arr[i];
    arr[pos] = data;
    n++;
}

/* Delete element at index pos. Elements after pos shift left. */
void delete_at(int pos) {
    int i;
    if (pos < 0 || pos >= n) {
        printf("Invalid position\n");
        return;
    }
    printf("Deleted %d\n", arr[pos]);
    for (i = pos; i < n - 1; i++)
        arr[i] = arr[i + 1];
    n--;
}

int search(int key) {
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] == key)
            return i;
    return -1;
}

void update(int pos, int data) {
    if (pos < 0 || pos >= n) {
        printf("Invalid position\n");
        return;
    }
    arr[pos] = data;
}

int main() {
    insert(0, 23);
    insert(1, 54);
    insert(2, 78);
    insert(3, 90);
    printf("Array: ");
    traverse();

    insert(2, 60);                       /* 23 54 60 78 90 */
    printf("After inserting 60 at index 2: ");
    traverse();

    delete_at(0);                        /* removes 23 */
    printf("After deleting index 0: ");
    traverse();

    update(1, 65);
    printf("After updating index 1 to 65: ");
    traverse();

    printf("Search 78 -> index %d\n", search(78));
    printf("Search 100 -> index %d\n", search(100));
    return 0;
}
