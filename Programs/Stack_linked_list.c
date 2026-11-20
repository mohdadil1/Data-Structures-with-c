/*
 * Stack - Linked List Implementation
 * ----------------------------------
 * Same stack ADT (push/pop/peek) but built on a linked list, so there is
 * no fixed maximum size. The head of the list acts as the top.
 * The client code in main() is the same as for the array version -
 * this is the advantage of an ADT.
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node *top = NULL;

int isEmpty() {
    return top == NULL;
}

void push(int data) {
    struct node *newNode = malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Stack Overflow\n");
        exit(1);
    }
    newNode->data = data;
    newNode->link = top;        /* new node points to old top */
    top = newNode;              /* new node becomes top       */
}

int pop() {
    struct node *temp;
    int value;
    if (isEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    temp = top;
    value = temp->data;
    top = top->link;
    free(temp);
    return value;
}

int peek() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return top->data;
}

void print() {
    struct node *temp = top;
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (top -> bottom): ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int main() {
    push(1);
    push(2);
    push(3);
    print();                                /* 3 2 1 */
    printf("Popped: %d\n", pop());          /* 3 */
    printf("Top element: %d\n", peek());    /* 2 */
    push(10);
    print();                                /* 10 2 1 */
    return 0;
}
