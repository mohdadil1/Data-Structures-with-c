/*
 * Circular Queue - Array Implementation
 * -------------------------------------
 * The last position is connected back to the first, so space freed by
 * dequeue() at the front can be reused. Indexes move with
 *     rear  = (rear + 1) % MAX
 *     front = (front + 1) % MAX
 *
 * Empty: front == -1
 * Full : (rear + 1) % MAX == front
 * One element left: front == rear -> after deleting it, reset both to -1.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int cqueue[MAX];
int front = -1;
int rear = -1;

int isEmpty() {
    return front == -1;
}

int isFull() {
    return (rear + 1) % MAX == front;
}

void enqueue(int data) {
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1)
        front = 0;
    rear = (rear + 1) % MAX;
    cqueue[rear] = data;
}

int dequeue() {
    int data;
    if (isEmpty()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    data = cqueue[front];
    if (front == rear)                  /* only one element was present */
        front = rear = -1;
    else
        front = (front + 1) % MAX;
    return data;
}

int peek() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    return cqueue[front];
}

void print() {
    int i;
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue (front -> rear): ");
    i = front;
    while (1) {
        printf("%d ", cqueue[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("   [front = %d, rear = %d]\n", front, rear);
}

int main() {
    enqueue(2);
    enqueue(8);
    enqueue(69);
    enqueue(6);
    enqueue(9);
    print();                            /* full queue */
    enqueue(100);                       /* overflow */

    printf("Dequeued: %d\n", dequeue());
    printf("Dequeued: %d\n", dequeue());
    print();

    enqueue(10);                        /* reuses index 0 */
    enqueue(20);                        /* reuses index 1 */
    print();
    printf("Front element: %d\n", peek());

    while (!isEmpty())
        printf("Dequeued: %d\n", dequeue());
    print();
    return 0;
}
