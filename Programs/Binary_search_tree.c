/*
 * Binary Search Tree (BST)
 * ------------------------
 * For every node: values in the left subtree are smaller, values in the
 * right subtree are greater. Searching discards half the tree at each step:
 * O(log n) for a balanced tree (O(n) in the worst case, a skewed tree).
 *
 * Inorder traversal of a BST prints the values in sorted order.
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *left;
    int data;
    struct node *right;
};

struct node *createNode(int data) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->left = NULL;
    newNode->data = data;
    newNode->right = NULL;
    return newNode;
}

struct node *insert(struct node *root, int data) {
    if (root == NULL)
        return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;                        /* duplicates are ignored */
}

struct node *search(struct node *root, int key) {
    while (root != NULL && root->data != key) {
        if (key < root->data)
            root = root->left;          /* search left subtree  */
        else
            root = root->right;         /* search right subtree */
    }
    return root;
}

struct node *findMin(struct node *root) {
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

struct node *deleteNode(struct node *root, int key) {
    struct node *temp;
    if (root == NULL)
        return NULL;
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {       /* 0 or 1 child */
            temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }
        /* 2 children: replace with inorder successor */
        temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(struct node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void deleteTree(struct node *root) {
    if (root == NULL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int main() {
    int values[] = {50, 30, 80, 20, 40, 70, 91};
    int i, n = sizeof(values) / sizeof(values[0]);
    struct node *root = NULL;

    for (i = 0; i < n; i++)
        root = insert(root, values[i]);

    printf("Inorder (sorted): ");
    inorder(root);
    printf("\n");

    printf("Search 91: %s\n", search(root, 91) ? "Found" : "Not found");
    printf("Search 65: %s\n", search(root, 65) ? "Found" : "Not found");

    root = deleteNode(root, 30);        /* node with two children */
    printf("After deleting 30: ");
    inorder(root);
    printf("\n");

    deleteTree(root);
    return 0;
}
