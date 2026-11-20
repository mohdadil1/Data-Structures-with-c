/*
 * Doubly Linked List
 * ------------------
 * Each node has three parts: prev (address of previous node), data, and
 * next (address of next node). It can be traversed forward and backward.
 *
 * Operations: addToEmpty, addAtBeg, addAtEnd, addAfterPos, addBeforePos,
 *             createList, delFirst, delLast, delInter, print, printReverse
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *prev;
    int data;
    struct node *next;
};

struct node *addToEmpty(struct node *head, int data) {
    struct node *temp = malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;
    head = temp;
    return head;
}

struct node *addAtBeg(struct node *head, int data) {
    struct node *temp = malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = head;
    if (head != NULL)
        head->prev = temp;
    head = temp;
    return head;
}

struct node *addAtEnd(struct node *head, int data) {
    struct node *temp, *tp;
    temp = malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;
    if (head == NULL)
        return temp;
    tp = head;
    while (tp->next != NULL)            /* Step 1: traversal */
        tp = tp->next;
    tp->next = temp;                    /* Step 2: link both ways */
    temp->prev = tp;
    return head;
}

/* Insert a new node after the node at position (1-based). */
struct node *addAfterPos(struct node *head, int data, int position) {
    struct node *newP, *temp = head, *temp2;
    newP = addToEmpty(NULL, data);

    while (position != 1 && temp != NULL) {
        temp = temp->next;
        position--;
    }
    if (temp == NULL) {
        printf("Invalid position\n");
        free(newP);
        return head;
    }
    if (temp->next == NULL) {           /* insert at the end of the list */
        temp->next = newP;
        newP->prev = temp;
    } else {
        temp2 = temp->next;
        temp->next = newP;
        temp2->prev = newP;
        newP->next = temp2;
        newP->prev = temp;
    }
    return head;
}

/* Insert a new node before the node at position (1-based). */
struct node *addBeforePos(struct node *head, int data, int position) {
    struct node *newP, *temp = head, *temp2;

    if (position == 1)                  /* insert at the beginning of the list */
        return addAtBeg(head, data);

    newP = addToEmpty(NULL, data);
    while (position > 2 && temp != NULL) {
        temp = temp->next;
        position--;
    }
    if (temp == NULL) {
        printf("Invalid position\n");
        free(newP);
        return head;
    }
    temp2 = temp->next;
    temp->next = newP;
    newP->prev = temp;
    newP->next = temp2;
    if (temp2 != NULL)
        temp2->prev = newP;
    return head;
}

/* Create an entire list by reading n values from the user. */
struct node *createList(struct node *head) {
    int n, data, i;
    printf("Enter the number of nodes: ");
    if (scanf("%d", &n) != 1 || n <= 0)
        return head;
    printf("Enter the element for node 1: ");
    scanf("%d", &data);
    head = addToEmpty(head, data);
    for (i = 1; i < n; i++) {
        printf("Enter the element for node %d: ", i + 1);
        scanf("%d", &data);
        head = addAtEnd(head, data);
    }
    return head;
}

struct node *delFirst(struct node *head) {
    struct node *temp = head;
    if (head == NULL)
        return NULL;
    head = head->next;
    free(temp);
    if (head != NULL)                   /* note: one-node list */
        head->prev = NULL;
    return head;
}

struct node *delLast(struct node *head) {
    struct node *temp = head, *temp2;
    if (head == NULL)
        return NULL;
    while (temp->next != NULL)
        temp = temp->next;
    temp2 = temp->prev;
    if (temp2 == NULL) {                /* only one node */
        free(temp);
        return NULL;
    }
    temp2->next = NULL;
    free(temp);
    return head;
}

/* Delete the node at an intermediate position (1-based). */
struct node *delInter(struct node *head, int position) {
    struct node *temp = head, *temp2;
    if (position == 1)
        return delFirst(head);
    while (position > 1 && temp != NULL) {
        temp = temp->next;
        position--;
    }
    if (temp == NULL) {
        printf("Invalid position\n");
        return head;
    }
    if (temp->next == NULL)
        return delLast(head);
    temp2 = temp->prev;
    temp2->next = temp->next;
    temp->next->prev = temp2;
    free(temp);
    return head;
}

void print(struct node *head) {
    struct node *ptr = head;
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void printReverse(struct node *head) {
    struct node *ptr = head;
    if (ptr == NULL) {
        printf("\n");
        return;
    }
    while (ptr->next != NULL)
        ptr = ptr->next;
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->prev;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL;

    head = addToEmpty(head, 45);
    head = addAtBeg(head, 34);
    head = addAtEnd(head, 9);
    printf("List: ");
    print(head);                        /* 34 45 9 */

    head = addAfterPos(head, 25, 2);    /* after 45, between 45 and 9 */
    printf("After addAfterPos(25, 2): ");
    print(head);                        /* 34 45 25 9 */

    head = addBeforePos(head, 77, 3);
    printf("After addBeforePos(77, 3): ");
    print(head);                        /* 34 45 77 25 9 */

    printf("Reverse traversal: ");
    printReverse(head);

    head = delFirst(head);
    printf("After delFirst: ");
    print(head);

    head = delLast(head);
    printf("After delLast: ");
    print(head);

    head = delInter(head, 2);
    printf("After delInter(2): ");
    print(head);

    while (head != NULL)
        head = delFirst(head);

    printf("\n--- Create an entire list ---\n");
    head = createList(head);
    printf("Your list: ");
    print(head);
    while (head != NULL)
        head = delFirst(head);
    return 0;
}
