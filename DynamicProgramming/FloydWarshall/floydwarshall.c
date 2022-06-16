/*
Name: Ayan Banerjee
Roll: 13000120019
*/
#include <stdio.h>
#include <stdlib.h>

int minimum(int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

void floydWarshall(int** graph, int n) {
    int** predecessor = (int**)malloc(n * sizeof(int*));
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        predecessor[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            predecessor[i][j] = j + 1;
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j) {
                    tmp = minimum(graph[i][j], graph[i][k] + graph[k][j]);
                    if (tmp != graph[i][j]) {
                        graph[i][j] = tmp;
                        predecessor[i][j] = k+1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            printf("Shortest Distance between %d to %d: %d\n", (i + 1), (j + 1), graph[i][j]);
            printf("Path from %d to %d: %d->", i + 1, j + 1, i+1);
            tmp = predecessor[i][j];
            while (tmp != j + 1) {
                printf("%d->", tmp);
                tmp = predecessor[tmp - 1][j];
            }
            printf("%d\n\n", j + 1);
        }
    }
}

int** initMatrix(int** arr, int n) {
    arr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        arr[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j <= n; j++) {
            arr[i][j] = -1;
        }
    }
    return arr;
}

int** fileImport(int** graph, int* n) {
    int i = 0, j = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in reading file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", n);
    graph = initMatrix(graph, *n);
    for (int i = 0; i < (*n);i++){
        for (int j = 0; j < (*n);j++){
            fscanf(fptr, "%d", &graph[i][j]);
        }
    }
    fclose(fptr);
    return graph;
}

int main() {
    int** graph = NULL;
    int n = 0;
    graph = fileImport(graph, &n);
    floydWarshall(graph, n);
    return 0;
}