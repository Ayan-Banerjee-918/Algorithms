#include <stdio.h>
#include <stdlib.h>

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

void BellmanFord(int n, int** weight, int* distance, int* predecessor) {
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                if (distance[i] + weight[i][j] < distance[j]) {
                    distance[j] = distance[i] + weight[i][j];
                    predecessor[j] = i;
                }
            }
        }
    }
}

int** fileImport(int** graph, int* n) {
    int i = 0, j = 0;
    int source = 0, destination = 0, weight = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in reading file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", n);
    graph=initMatrix(graph, *n);
    for (i = 0; i <= (*n); i++) {
        graph[i][i] = 0;
    }
    for (i = 0; i < ((*n) * ((*n) - 1)); i++) {
        fscanf(fptr, "%d", &source);
        fscanf(fptr, "%d", &destination);
        fscanf(fptr, "%d", &weight);
        graph[source-1][destination-1] = weight;
    }
    fclose(fptr);
    return graph;
}

int main() {
    int** weight = NULL;
    int n = 0, k = 0, j = 0;
    weight=fileImport(weight, &n);
    int* distance = (int*)malloc(n * sizeof(int));
    int* predecessor = (int*)malloc(n * sizeof(int));
    int *path=(int*)malloc(n*sizeof(int));
    char ch[] = { 'S','t','x','y','z' };
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            distance[i] = 0;
        }
        else {
            distance[i] = 99999;
        }
    }
    BellmanFord(n, weight, distance, predecessor);
    printf("Source Vertex: S\n");
    for (int i = 0; i < n; i++) {
        if (i != start) {
            printf("\nShortest distance from S to %c: %d\n", ch[i], distance[i]);
            j=i;
            while(j!=start){
                j=predecessor[j];
                path[k++]=j+1;
            }
            printf("Path=");
            for(j=k-1;j>=0;j--){
                printf("%c->",ch[path[j]-1]);
            }
            printf("%c\n",ch[i]);
            k=0;
        }
    }
}