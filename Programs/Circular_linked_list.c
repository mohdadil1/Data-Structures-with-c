/*
 * Circular Linked List
 * --------------------
 * Circular Singly Linked List: the last node points back to the first node.
 * Circular Doubly Linked List: additionally, the first node's prev points to
 * the last node.
 *
 * We keep a pointer to the LAST node (tail). Then tail->next is the first
 * node, so insertion at both the beginning and the end is O(1).
 */
#include <stdio.h>
#include <stdlib.h>

/* ---------- Circular Singly Linked List ---------- */
struct node {
    int data;
    struct node *next;
};

/* Create a single node that points to itself. */
struct node *circularSingly(int data) {
    struct node *temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->next = temp;
    return temp;
}

struct node *addAtBeg(struct node *tail, int data) {
    struct node *newP = circularSingly(data);
    if (tail == NULL)
        return newP;
    newP->next = tail->next;            /* new node -> old first node */
    tail->next = newP;                  /* last node -> new first node */
    return tail;
}

struct node *addAtEnd(struct node *tail, int data) {
    struct node *newP = circularSingly(data);
    if (tail == NULL)
        return newP;
    newP->next = tail->next;
    tail->next = newP;
    tail = newP;                        /* new node becomes the last node */
    return tail;
}

struct node *delFirst(struct node *tail) {
    struct node *temp;
    if (tail == NULL)
        return NULL;
    if (tail->next == tail) {           /* only one node */
        free(tail);
        return NULL;
    }
    temp = tail->next;
    tail->next = temp->next;
    free(temp);
    return tail;
}

struct node *delLast(struct node *tail) {
    struct node *temp;
    if (tail == NULL)
        return NULL;
    if (tail->next == tail) {
        free(tail);
        return NULL;
    }
    temp = tail->next;
    while (temp->next != tail)          /* find second-last node */
        temp = temp->next;
    temp->next = tail->next;
    free(tail);
    return temp;
}

void print(struct node *tail) {
    struct node *p;
    if (tail == NULL) {
        printf("List is empty\n");
        return;
    }
    p = tail->next;
    do {                                /* do-while: visit first node too */
        printf("%d ", p->data);
        p = p->next;
    } while (p != tail->next);
    printf("\n");
}

/* ---------- Circular Doubly Linked List ---------- */
struct dnode {
    struct dnode *prev;
    int data;
    struct dnode *next;
};

struct dnode *circularDoubly(int data) {
    struct dnode *temp = malloc(sizeof(struct dnode));
    temp->prev = temp;
    temp->data = data;
    temp->next = temp;
    return temp;
}

struct dnode *addAtEndDoubly(struct dnode *tail, int data) {
    struct dnode *newP = circularDoubly(data);
    if (tail == NULL)
        return newP;
    newP->next = tail->next;
    newP->prev = tail;
    tail->next->prev = newP;
    tail->next = newP;
    return newP;
}

void printDoubly(struct dnode *tail) {
    struct dnode *p;
    if (tail == NULL) {
        printf("List is empty\n");
        return;
    }
    p = tail->next;
    printf("Forward:  ");
    do {
        printf("%d ", p->data);
        p = p->next;
    } while (p != tail->next);
    printf("\nBackward: ");
    p = tail;
    do {
        printf("%d ", p->data);
        p = p->prev;
    } while (p != tail);
    printf("\n");
}

int main() {
    struct node *tail = NULL;
    struct dnode *dtail = NULL;

    printf("Circular Singly Linked List\n");
    tail = circularSingly(34);
    tail = addAtEnd(tail, 45);
    tail = addAtEnd(tail, 66);
    tail = addAtBeg(tail, 10);
    print(tail);                        /* 10 34 45 66 */
    printf("Last node -> next = %d (the first node)\n", tail->next->data);

    tail = delFirst(tail);
    printf("After delFirst: ");
    print(tail);
    tail = delLast(tail);
    printf("After delLast:  ");
    print(tail);
    while (tail != NULL)
        tail = delFirst(tail);

    printf("\nCircular Doubly Linked List\n");
    dtail = circularDoubly(34);
    dtail = addAtEndDoubly(dtail, 45);
    dtail = addAtEndDoubly(dtail, 66);
    printDoubly(dtail);

    /* free the doubly list */
    while (dtail != NULL) {
        struct dnode *first = dtail->next;
        if (first == dtail) {
            free(dtail);
            dtail = NULL;
        } else {
            dtail->next = first->next;
            first->next->prev = dtail;
            free(first);
        }
    }
    return 0;
}
