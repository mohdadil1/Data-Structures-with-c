/*
 * Graph Traversal: BFS and DFS
 * ----------------------------
 * BFS (Breadth First Search) - uses a QUEUE, visits level by level.
 *   1. Put the start vertex in the queue and mark it visited.
 *   2. Remove the front vertex from the queue and print it.
 *   3. Add all its unvisited neighbours to the queue and mark them visited.
 *   4. Repeat until the queue is empty.
 *
 * DFS (Depth First Search) - uses a STACK, goes as deep as possible first.
 *   1. Visit the vertex, print it and push it on the stack.
 *   2. Look at the top vertex: if it has an unvisited neighbour,
 *      visit it, print it and push it.
 *   3. If it has no unvisited neighbour, pop it.
 *   4. Repeat until the stack is empty.
 *
 * Graph (same as the notes):
 *   A: B C     B: A D     C: A D     D: B C E     E: D
 *
 * Expected: BFS from A = A B C D E,  DFS from A = A B D C E
 *           BFS from D = D B C E A,  DFS from D = D B A C E
 */
#include <stdio.h>

#define V 5

int adj[V][V];

void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

void BFS(int start) {
    int queue[V], front = 0, rear = -1;
    int visited[V] = {0};
    int u, v;

    queue[++rear] = start;              /* enqueue start, mark visited */
    visited[start] = 1;

    printf("BFS from %c: ", 'A' + start);
    while (front <= rear) {
        u = queue[front++];             /* dequeue and print */
        printf("%c ", 'A' + u);
        for (v = 0; v < V; v++) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                queue[++rear] = v;
            }
        }
    }
    printf("\n");
}

void DFS(int start) {
    int stack[V], top = -1;
    int visited[V] = {0};
    int u, v, found;

    printf("DFS from %c: ", 'A' + start);
    visited[start] = 1;
    printf("%c ", 'A' + start);
    stack[++top] = start;

    while (top != -1) {
        u = stack[top];                 /* look at the top vertex */
        found = 0;
        for (v = 0; v < V; v++) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                printf("%c ", 'A' + v);
                stack[++top] = v;
                found = 1;
                break;
            }
        }
        if (!found)
            top--;                      /* no unvisited neighbour: pop */
    }
    printf("\n");
}

/* Recursive DFS: the call stack plays the role of the explicit stack. */
int rvisited[V];

void DFSRecursive(int u) {
    int v;
    rvisited[u] = 1;
    printf("%c ", 'A' + u);
    for (v = 0; v < V; v++)
        if (adj[u][v] && !rvisited[v])
            DFSRecursive(v);
}

int main() {
    int i;
    /* A=0, B=1, C=2, D=3, E=4 */
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 3);
    addEdge(3, 4);

    BFS(0);
    DFS(0);
    BFS(3);
    DFS(3);

    for (i = 0; i < V; i++)
        rvisited[i] = 0;
    printf("Recursive DFS from A: ");
    DFSRecursive(0);
    printf("\n");
    return 0;
}
