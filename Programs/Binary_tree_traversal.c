/*
 * Binary Tree and its Traversals
 * ------------------------------
 * A binary tree is a tree in which every node has at most 2 children.
 * Each node has: left pointer, data, right pointer.
 *
 * Traversals (recursive):
 *   Preorder : Root  Left  Right   (used to copy a tree)
 *   Inorder  : Left  Root  Right   (gives sorted order in a BST)
 *   Postorder: Left  Right Root    (used to delete a tree)
 *
 * Tree built in main() (from the notes):
 *                1
 *              /   \
 *             2     3
 *            / \     \
 *           4   5     6
 *              / \   /
 *             7   8 9
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

void preorder(struct node *root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(struct node *root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int countNodes(struct node *root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

/* Height = number of levels (a single node has height 1). */
int height(struct node *root) {
    int lh, rh;
    if (root == NULL)
        return 0;
    lh = height(root->left);
    rh = height(root->right);
    return 1 + (lh > rh ? lh : rh);
}

/* Postorder is used to delete a tree: children are freed before the parent. */
void deleteTree(struct node *root) {
    if (root == NULL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int main() {
    struct node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);
    root->left->right->left = createNode(7);
    root->left->right->right = createNode(8);
    root->right->right->left = createNode(9);

    printf("Preorder : ");
    preorder(root);
    printf("\nInorder  : ");
    inorder(root);
    printf("\nPostorder: ");
    postorder(root);
    printf("\nNumber of nodes: %d\n", countNodes(root));
    printf("Height of tree : %d\n", height(root));

    deleteTree(root);
    return 0;
}
