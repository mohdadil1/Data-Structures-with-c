/*
 * Queue - Linked List Implementation
 * ----------------------------------
 * Solves the fixed-size problem of the array queue. We keep two pointers:
 *   front -> first node (deletion happens here)
 *   rear  -> last node  (insertion happens here)
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *front = NULL;
struct node *rear = NULL;

int isEmpty() {
    return front == NULL;
}

void enqueue(int data) {
    struct node *newNode = malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Queue Overflow\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    if (rear == NULL) {                 /* queue was empty */
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

int dequeue() {
    struct node *temp;
    int data;
    if (isEmpty()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    temp = front;
    data = temp->data;
    front = front->next;
    if (front == NULL)                  /* queue became empty */
        rear = NULL;
    free(temp);
    return data;
}

int peek() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    return front->data;
}

void print() {
    struct node *temp = front;
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue (front -> rear): ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(15);
    enqueue(56);
    print();                            /* 10 15 56 */
    printf("Dequeued: %d\n", dequeue()); /* 10 - first in, first out */
    printf("Front element: %d\n", peek());
    enqueue(45);
    print();                            /* 15 56 45 */
    while (!isEmpty())
        dequeue();
    print();
    return 0;
}
