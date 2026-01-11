
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
void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
}
void topologicalSort(struct Graph* graph) {
    int inDegree[100] = {0};
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjMatrix[i][j] == 1)
                inDegree[j]++;
        }
    }
    int queue[100];
    int front = 0, rear = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (inDegree[i] == 0)
            queue[rear++] = i;
    }
    int count = 0;
    int topoOrder[100];
    while (front < rear) {
        int u = queue[front++];
        topoOrder[count++] = u;
        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->adjMatrix[u][v] == 1) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }
    if (count != graph->numVertices) {
        printf("Graph has a cycle! Topological sort not possible.\n");
        return;
    }
    printf("Topological Sort: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", topoOrder[i]);
    }
    printf("\n");
}
int main() {
    int vertices = 6;
    struct Graph* graph = createGraph(vertices);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);
    topologicalSort(graph);
    return 0;
}
