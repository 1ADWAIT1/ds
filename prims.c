#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Graph {
    int numVertices;
    int **adjMatrix;
};
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    return graph;
}
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;
}
int minKey(int key[], int mstSet[], int vertices) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}
void primMST(struct Graph* graph) {
    int vertices = graph->numVertices;
    int parent[100];
    int key[100];
    int mstSet[100];
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < vertices - 1; count++) {
        int u = minKey(key, mstSet, vertices);
        mstSet[u] = 1;
        for (int v = 0; v < vertices; v++) {
            if (graph->adjMatrix[u][v] != 0 && mstSet[v] == 0 &&
                graph->adjMatrix[u][v] < key[v]) {

                parent[v] = u;
                key[v] = graph->adjMatrix[u][v];
            }
        }
    }
    printf("Prim's Minimum Spanning Tree:\n");
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d  (weight %d)\n", parent[i], i,
               graph->adjMatrix[i][parent[i]]);
    }
}
int main() {
    int vertices = 5;
    struct Graph* graph = createGraph(vertices);
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 4, 7);
    addEdge(graph, 3, 4, 9);
    primMST(graph);
    return 0;
}