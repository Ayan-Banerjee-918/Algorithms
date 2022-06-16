#include <stdio.h>
#include <stdlib.h>

int** init2DMatrix(int** graph, int n) {
    int i = 0, j = 0;
    graph = (int**)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
    return graph;
}

int** importGraph(int** graph, int* n) {
    int i = 0, j = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", n);
    graph = init2DMatrix(graph, *n);
    for (i = 0; i < *n; i++) {
        for (j = 0; j < *n; j++) {
            fscanf(fptr, "%d", &graph[i][j]);
        }
    }
    fclose(fptr);
    return graph;
}

void primCost(int** graph, int n) {
    int* visited = (int*)malloc(n * sizeof(int));
    int* path = (int*)malloc(n * sizeof(int));
    int* minKey = (int*)malloc(n * sizeof(int));
    int i = 0, j = 0, cost = 0, k = 0, x = 0, y = 0;;
    int min = 0;
    for (i = 0; i < n; i++) {
        minKey[i] = 99999;
        visited[i] = 0;
        path[i] = 0;
    }
    minKey[0] = 0;
    path[0] = -1;
    printf("Minimum Spanning Tree:\n");
    for (i = 0; i < n; i++) {
        min = 99999;
        for (j = 0; j < n; j++) {
            if (minKey[j] < min && !visited[j]) {
                min = minKey[j];
                k = j;
            }
        }
        visited[k] = 1;
        for (j = 0; j < n; j++) {
            if (graph[k][j] != 99999 && !visited[j] && graph[k][j] < minKey[j]) {
                minKey[j] = graph[k][j];
                path[j] = k;
            }
        }
        if (i != 0) {
            printf("%d->%d\n", path[k] + 1, k + 1);
        }
    }
    for (i = 1; i < n; i++) {
        cost += graph[i][path[i]];
    }
    printf("Cost:%d\n", cost);
}

int main() {
    int n = 0, cost = 0;
    int** graph = NULL;
    graph = importGraph(graph, &n);
    primCost(graph, n);
    return 0;
}