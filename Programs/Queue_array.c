/*
 * Queue - Array Implementation (FIFO)
 * -----------------------------------
 * Insertion (enqueue) happens at the rear, deletion (dequeue) at the front.
 * front = rear = -1 means the queue is empty.
 *
 * Limitation: once rear reaches MAX-1, we cannot insert even if space was
 * freed at the front. The circular queue (Circular_queue.c) solves this.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

int isFull() {
    return rear == MAX - 1;
}

int isEmpty() {
    return front == -1 || front == rear + 1;
}

void enqueue(int data) {
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1)                    /* first insertion */
        front = 0;
    rear = rear + 1;
    queue[rear] = data;
}

int dequeue() {
    int data;
    if (isEmpty()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    data = queue[front];
    front++;
    return data;
}

int peek() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    return queue[front];
}

void print() {
    int i;
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue (front -> rear): ");
    for (i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    int choice, data;
    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Print\n5. Quit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
            break;
        switch (choice) {
        case 1:
            printf("Enter the element: ");
            scanf("%d", &data);
            enqueue(data);
            break;
        case 2:
            if (!isEmpty()) {
                data = dequeue();
                printf("Deleted element: %d\n", data);
            } else {
                printf("Queue Underflow\n");
            }
            break;
        case 3:
            if (!isEmpty())
                printf("Front element: %d\n", peek());
            else
                printf("Queue is empty\n");
            break;
        case 4:
            print();
            break;
        case 5:
            exit(0);
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}
