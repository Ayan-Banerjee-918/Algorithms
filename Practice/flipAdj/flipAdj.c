#include <stdio.h>
#include <stdlib.h>

int** init2DArray(int** graph, int N) {
    int i = 0;
    graph = (int**)malloc(N * sizeof(int*));
    for (i = 0; i < N; i++) {
        graph[i] = (int*)calloc(N, sizeof(int));
    }
    return graph;
}

void interactor(int** graph, int N) {
    int inputCnt = 0, vertex = 0;
    int i = 0, j = 0;
    char color[2][6] = { "Black\0","White\0" };
    printf("Enter no of inputs : ");
    scanf("%d", &inputCnt);
    printf("\n");
    for (i = 0; i < inputCnt; i++) {
        printf("Enter vertex : ");
        scanf("%d", &vertex);
        printf("Vertex Color : %s\n\n", color[graph[vertex - 1][vertex - 1]]);
        for (j = 0; j < N; j++) {
            if ((vertex - 1) == j) {
                continue;
            }
            else if (graph[vertex - 1][j]) {
                graph[j][j] ^= 1;
            }
        }
    }
    printf("Final Adjacency Matrix:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\nFinal Vertex Colors:\n");
    for (i = 0; i < N; i++) {
        printf("Vertex %d : %s\n", (i + 1), color[graph[i][i]]);
    }
}

int** fileImport(int* N, int** graph) {
    int i = 0, j = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening File!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    graph = init2DArray(graph, *N);
    for (i = 0; i < *N; i++) {
        for (j = 0; j < *N; j++) {
            fscanf(fptr, "%d", &graph[i][j]);
        }
    }
    fclose(fptr);
    return graph;
}

void main() {
    int N = 0, i = 0, j = 0;
    int** graph = NULL;
    graph = fileImport(&N, graph);
    interactor(graph, N);
}