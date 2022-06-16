                         ___SOURCE_CODE___ 
#include <stdio.h>
#include <stdlib.h>

int** init2DMatrix(int** graph, int N) {
    int i = 0, j = 0;
    graph = (int**)malloc(N * sizeof(int));
    for (i = 0; i < N; i++) {
        graph[i] = (int*)malloc(N * sizeof(int));
        for (j = 0; j < N; j++) {
            graph[i][j] = 0;
        }
    }
    return graph;
}

int printColor(int* color, int N, int col) {
    int i,tmp;
    static int k = 1;
    if (k == 1) {
        tmp = 0;
        for (i = 0; i < N; i++) {
            if (color[i] > tmp) {
                tmp = color[i];
            }
        }
        printf("The Chromatic Number of the graph : %d\n\n", tmp);
        col = tmp;
    }
    printf("Solution %d\n", k++);
    for (i = 0; i < N; i++) {
        printf("C%d ", color[i]);
    }
    printf("\n\n");
    return col;
}

int isValid(int* color, int** graph, int currentCol, int vertex,int N) {
    int i;
    for (i = 0; i < N; i++) {
        if (graph[vertex][i] && currentCol == color[i]) {
            return 0;
        }
    }
    return 1;
}

int solveGraph(int* color, int** graph, int vertex, int N, int  col) {
    if (vertex == N) {
        col = printColor(color, N, col);
        return 1;
    }
    int res = 0;
    for (int i = 1; i < col; i++)
    {
        if (isValid(color, graph, i, vertex, N)) {
            color[vertex] = i;
            res = solveGraph(color, graph, vertex + 1, N, col) || res;
            color[vertex] = 0;
        }
    }
    return res;
}

void solveChromatic(int** graph, int N) {
    int i = 0;
    int* color = (int*)calloc(N,sizeof(int));
    int col = N;
    if (solveGraph(color, graph, 0, N, col) == 0) {
        printf("No Solution.\n");
    }
}


int** importGraph(int** graph, int* N) {
    int i = 0, j = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    graph = init2DMatrix(graph, *N);
    for (i = 0; i < *N; i++) {
        for (j = 0; j < *N; j++) {
            fscanf(fptr, "%d", &graph[i][j]);
        }
    }
    fclose(fptr);
    return graph;
}

void main() {
    int N = 0;
    int** graph = NULL;
    graph = importGraph(graph, &N);
    solveChromatic(graph, N);
}