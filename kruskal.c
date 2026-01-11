#include <stdio.h>
#include <stdlib.h>

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
        for (int j = 0; j < vertices; j++)
            graph->adjMatrix[i][j] = 0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;
}

struct Edge {
    int src, dest, weight;
};

int compare(const void* a, const void* b) {
    struct Edge* e1 = (struct Edge*)a;
    struct Edge* e2 = (struct Edge*)b;
    return e1->weight - e2->weight;
}

int find(int parent[], int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSet(int parent[], int x, int y) {
    int px = find(parent, x);
    int py = find(parent, y);
    parent[px] = py;
}

void kruskalMST(struct Graph* graph) {
    int V = graph->numVertices;
    int totalEdges = 0;

    for (int i = 0; i < V; i++)
        for (int j = i + 1; j < V; j++)
            if (graph->adjMatrix[i][j] != 0)
                totalEdges++;

    struct Edge *edges = (struct Edge*)malloc(totalEdges * sizeof(struct Edge));

    int k = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph->adjMatrix[i][j] != 0) {
                edges[k].src = i;
                edges[k].dest = j;
                edges[k].weight = graph->adjMatrix[i][j];
                k++;
            }
        }
    }

    qsort(edges, totalEdges, sizeof(struct Edge), compare);

    int *parent = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
        parent[i] = i;

    int count = 0;
    printf("Kruskal's Minimum Spanning Tree:\n");

    for (int i = 0; i < totalEdges && count < V - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        int pu = find(parent, u);
        int pv = find(parent, v);

        if (pu != pv) {
            printf("%d - %d (weight %d)\n", u, v, edges[i].weight);
            unionSet(parent, pu, pv);
            count++;
        }
    }

    free(edges);
    free(parent);
}

int main() {
    int vertices = 4;
    struct Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 6);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 1, 3, 15);
    addEdge(graph, 2, 3, 4);

    kruskalMST(graph);
    return 0;
}
