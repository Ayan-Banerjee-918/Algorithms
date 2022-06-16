#include <stdio.h>
#include <stdlib.h>

int** init2DArray(int** arr, int n) {
    arr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            arr[i][j] = -1;
        }
    }
    return arr;
}

void dijkstra(int** costGraph, int n, int start) {
    int** cost = NULL;
    cost = init2DArray(cost, n);
    int* distance = (int*)malloc(n * sizeof(int));
    int* predecessor = (int*)malloc(n * sizeof(int));
    int* path = (int*)malloc(n * sizeof(int));
    int* visited = (int*)malloc(n * sizeof(int));
    int i, j, k = 0, count, minDistance, nextNode;
    for (i = 0; i < n; i++) {
        distance[i] = costGraph[start][i];
        predecessor[i] = start;
        visited[i] = 0;
    }
    distance[start] = 0;
    visited[start] = 1;
    count = 1;
    while (count < n - 1) {
        minDistance = 99999;
        for (i = 0; i < n; i++) {
            if (distance[i] < minDistance && !visited[i]) {
                minDistance = distance[i];
                nextNode = i;
            }
        }
        visited[nextNode] = 1;
        for (i = 0; i < n; i++) {
            if (!visited[i]) {
                if (minDistance + costGraph[nextNode][i] < distance[i]) {
                    distance[i] = minDistance + costGraph[nextNode][i];
                    predecessor[i] = nextNode;
                }
            }
        }
        count++;
    }
    for (i = 0; i < n; i++) {
        if (i != start) {
            printf("\nShortest distance from %d to %d: %d\n",start+1, i + 1, distance[i]);
            j = i;
            while (j != start) {
                j = predecessor[j];
                path[k++] = j + 1;
            }
            printf("Path=");
            for (j = k-1; j >= 0; j--) {
                printf("%d->", path[j]);
            }
            printf("%d\n", i + 1);
            k = 0;
        }
    }
}

int** fileImport(int** costGraph,int* n) {
    int i = 0, j = 0;
    int source, destination, cost;
    FILE* fptr;
    if ((fptr = fopen("dijkstraInput.txt", "r")) == NULL) {
        printf("Error opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", n);
    costGraph = init2DArray(costGraph, *n);
    for (i = 0; i < (*n); i++) {
        costGraph[i][i] = 0;
    }
    for (i = 0; i < ((*n) * ((*n)-1)); i++) {
        fscanf(fptr, "%d", &source);
        fscanf(fptr, "%d", &destination);
        fscanf(fptr, "%d", &cost);
        costGraph[source - 1][destination - 1] = cost;
    }
    fclose(fptr);
    return costGraph;
}

int main() {
    int** cost=NULL, startNode;
    int n = 0;
    cost=fileImport(cost,&n);
    printf("Enter starting Node:");
    scanf("%d", &startNode);
    printf("Source Vertex: %d\n", startNode);
    dijkstra(cost, n, startNode - 1);
    return 0;
}