/*
 * Single Linked List
 * ------------------
 * Each node stores data and a link (address) to the next node.
 * head points to the first node; the last node's link is NULL.
 *
 * Operations: count_of_nodes, print_data, add_beg, add_at_end, add_at_pos,
 *             del_first, del_last, del_pos, reverse
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

void count_of_nodes(struct node *head) {
    int count = 0;
    struct node *ptr = NULL;
    if (head == NULL)
        printf("Linked List is empty");
    ptr = head;
    while (ptr != NULL) {
        count++;
        ptr = ptr->link;
    }
    printf("Number of nodes: %d\n", count);
}

void print_data(struct node *head) {
    struct node *ptr = head;
    if (head == NULL) {
        printf("Linked List is empty\n");
        return;
    }
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->link;
    }
    printf("\n");
}

/* Insert at the beginning: new node points to old head. */
struct node *add_beg(struct node *head, int data) {
    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = data;
    ptr->link = head;
    head = ptr;
    return head;
}

/* Insert at the end: traverse to the last node, link the new node. */
void add_at_end(struct node *head, int data) {
    struct node *ptr = head, *temp;
    temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->link = NULL;
    while (ptr->link != NULL)
        ptr = ptr->link;
    ptr->link = temp;
}

/* Insert after the given position (1-based). pos = 1 -> after first node. */
void add_at_pos(struct node *head, int data, int pos) {
    struct node *ptr = head;
    struct node *ptr2 = malloc(sizeof(struct node));
    ptr2->data = data;
    ptr2->link = NULL;

    pos--;
    while (pos != 0 && ptr != NULL) {
        ptr = ptr->link;
        pos--;
    }
    if (ptr == NULL) {
        printf("Invalid position\n");
        free(ptr2);
        return;
    }
    ptr2->link = ptr->link;
    ptr->link = ptr2;
}

struct node *del_first(struct node *head) {
    struct node *temp;
    if (head == NULL) {
        printf("List is already empty\n");
        return head;
    }
    temp = head;
    head = head->link;
    free(temp);
    return head;
}

/* Delete the last node using two pointers (temp walks, temp2 trails). */
struct node *del_last(struct node *head) {
    struct node *temp, *temp2;
    if (head == NULL) {
        printf("List is already empty\n");
        return head;
    }
    if (head->link == NULL) {           /* only one node */
        free(head);
        return NULL;
    }
    temp = head;
    temp2 = head;
    while (temp->link != NULL) {
        temp2 = temp;
        temp = temp->link;
    }
    temp2->link = NULL;
    free(temp);
    return head;
}

/* Delete the node at the given position (1-based). */
void del_pos(struct node **head, int position) {
    struct node *current = *head;
    struct node *previous = *head;

    if (*head == NULL) {
        printf("List is already empty\n");
        return;
    }
    if (position == 1) {
        *head = current->link;
        free(current);
        return;
    }
    while (position != 1 && current != NULL) {
        previous = current;
        current = current->link;
        position--;
    }
    if (current == NULL) {
        printf("Invalid position\n");
        return;
    }
    previous->link = current->link;
    free(current);
}

/* Reverse the list by reversing every link. */
struct node *reverse(struct node *head) {
    struct node *prev = NULL, *next = NULL;
    while (head != NULL) {
        next = head->link;
        head->link = prev;
        prev = head;
        head = next;
    }
    return prev;
}

int main() {
    /* Create the list 45 -> 98 -> 3 manually, as in the notes */
    struct node *head = malloc(sizeof(struct node));
    struct node *current;
    head->data = 45;
    head->link = NULL;

    current = malloc(sizeof(struct node));
    current->data = 98;
    current->link = NULL;
    head->link = current;

    current = malloc(sizeof(struct node));
    current->data = 3;
    current->link = NULL;
    head->link->link = current;

    printf("Created list: ");
    print_data(head);
    count_of_nodes(head);

    add_at_end(head, 67);
    printf("After add_at_end(67): ");
    print_data(head);

    head = add_beg(head, 10);
    printf("After add_beg(10): ");
    print_data(head);

    add_at_pos(head, 25, 2);
    printf("After add_at_pos(25, after position 2): ");
    print_data(head);

    head = del_first(head);
    printf("After del_first: ");
    print_data(head);

    head = del_last(head);
    printf("After del_last: ");
    print_data(head);

    del_pos(&head, 2);
    printf("After del_pos(2): ");
    print_data(head);

    head = reverse(head);
    printf("After reverse: ");
    print_data(head);
    count_of_nodes(head);

    while (head != NULL)                /* free remaining nodes */
        head = del_first(head);
    return 0;
}
