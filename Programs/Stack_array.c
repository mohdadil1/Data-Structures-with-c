/*
 * Stack - Array Implementation (LIFO)
 * -----------------------------------
 * Insertion (push) and deletion (pop) happen only at one end: the top.
 * top = -1 means the stack is empty.
 *
 * Operations: push, pop, peek (top), size, isEmpty, isFull, print
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int stack_arr[MAX];     /* declared globally: every function needs it */
int top = -1;

int isFull() {
    return top == MAX - 1;
}

int isEmpty() {
    return top == -1;
}

void push(int data) {
    if (isFull()) {
        printf("Stack Overflow\n");
        return;
    }
    top = top + 1;              /* 1. increment top            */
    stack_arr[top] = data;      /* 2. place data at position top */
}

int pop() {
    int value;
    if (isEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    value = stack_arr[top];     /* 1. read element at top */
    top = top - 1;              /* 2. decrement top        */
    return value;
}

int peek() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack_arr[top];
}

int size() {
    return top + 1;
}

void print() {
    int i;
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (top -> bottom): ");
    for (i = top; i >= 0; i--)
        printf("%d ", stack_arr[i]);
    printf("\n");
}

int main() {
    int choice, data;
    while (1) {
        printf("\n1. Push\n2. Pop\n3. Peek\n4. Size\n5. Print\n6. Quit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
            break;
        switch (choice) {
        case 1:
            printf("Enter the element to be pushed: ");
            scanf("%d", &data);
            push(data);
            break;
        case 2:
            if (!isEmpty())
                printf("Popped element: %d\n", pop());
            else
                printf("Stack Underflow\n");
            break;
        case 3:
            if (!isEmpty())
                printf("Top element: %d\n", peek());
            else
                printf("Stack is empty\n");
            break;
        case 4:
            printf("Size: %d\n", size());
            break;
        case 5:
            print();
            break;
        case 6:
            exit(0);
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}
