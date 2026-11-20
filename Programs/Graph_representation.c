/*
 * Graph Representation
 * --------------------
 * 1. Adjacency Matrix: a V x V table, adj[i][j] = 1 if there is an edge
 *    from i to j. Undirected graph -> symmetric matrix. Space O(V^2).
 * 2. Adjacency List: for every vertex, a linked list of its neighbours.
 *    Space O(V + E), better for sparse graphs.
 *
 * Undirected graph used (vertices A..E):
 *      A - B, A - C, B - D, C - D, D - E
 */
#include <stdio.h>
#include <stdlib.h>

#define V 5

/* ---------- Adjacency Matrix ---------- */
int adj[V][V];

void addEdgeMatrix(int u, int v, int directed) {
    adj[u][v] = 1;
    if (!directed)
        adj[v][u] = 1;
}

void printMatrix() {
    int i, j;
    printf("   ");
    for (j = 0; j < V; j++)
        printf("%c ", 'A' + j);
    printf("\n");
    for (i = 0; i < V; i++) {
        printf("%c: ", 'A' + i);
        for (j = 0; j < V; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }
}

/* ---------- Adjacency List ---------- */
struct node {
    int vertex;
    struct node *next;
};

struct node *list[V];

/* Append at the end so neighbours stay in the order they were added. */
void addToList(int u, int v) {
    struct node *newNode = malloc(sizeof(struct node));
    struct node *temp;
    newNode->vertex = v;
    newNode->next = NULL;
    if (list[u] == NULL) {
        list[u] = newNode;
        return;
    }
    temp = list[u];
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

void addEdgeList(int u, int v, int directed) {
    addToList(u, v);
    if (!directed)
        addToList(v, u);
}

void printList() {
    int i;
    struct node *temp;
    for (i = 0; i < V; i++) {
        printf("%c: ", 'A' + i);
        for (temp = list[i]; temp != NULL; temp = temp->next)
            printf("%c ", 'A' + temp->vertex);
        printf("\n");
    }
}

void freeList() {
    int i;
    struct node *temp;
    for (i = 0; i < V; i++) {
        while (list[i] != NULL) {
            temp = list[i];
            list[i] = list[i]->next;
            free(temp);
        }
    }
}

int main() {
    int edges[][2] = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}};
    int i, e = sizeof(edges) / sizeof(edges[0]);

    for (i = 0; i < e; i++) {
        addEdgeMatrix(edges[i][0], edges[i][1], 0);
        addEdgeList(edges[i][0], edges[i][1], 0);
    }

    printf("Adjacency Matrix (undirected, symmetric):\n");
    printMatrix();

    printf("\nAdjacency List:\n");
    printList();

    freeList();
    return 0;
}
