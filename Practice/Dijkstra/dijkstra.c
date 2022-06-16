#include <stdio.h>
#include <stdlib.h>

int** initMatrix(int** arr, int n) {
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
    int* distance = (int*)malloc(n * sizeof(int));
    int *predecessor = (int *)malloc(n * sizeof(int));
    int* A = (int*)malloc(n * sizeof(int));
    int Acnt = 0;
    int i = 0, min = 0, k = 0, tmp1=0, minVal=0;
    int* tmp = (int*)malloc(n * sizeof(int));
    int cpy = start;
    for (i = 0; i < n; i++) {
        if (i == start) {
            distance[i] = 0;
        }
        else {
            distance[i] = 99999;
        }
        A[i] = -1;
        tmp[i] = -1;
        predecessor[i] = start;
    }
    A[k++] = start;
    tmp[start] = 1;
    Acnt++;
    while (Acnt != n) {
        min = 999999;
        minVal = 999999;
        for (i = 0; i < n; i++) {
            if (i == cpy || start==i) {
                continue;
            }
            if (costGraph[start][i] != 99999) {
                tmp1 = distance[start] + costGraph[start][i];
                if ((tmp1 < distance[i])) {
                    distance[i] = tmp1;
                    predecessor[i] = start;
                }
                if (tmp1 < minVal && tmp[i]==-1) {
                    minVal = tmp1;
                    min = i;
                }
            }
        }
        A[k++] = min;
        tmp[min] = 1;
        Acnt++;
        start = min;
    }
    printf("Shortest Path including all vertices:\n");
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            printf("%d\n", (A[i] + 1));
        }
        else {
            printf("%d->", (A[i] + 1));
        }
    }
    for (int i = 0; i < n; i++) {
        if(i==cpy){
            continue;
        }
        else{
            printf("\nShortest Distance from %d to %d: %d\n", (cpy+1), (i+1), distance[i] );
            printf("Path: %d->",(i+1));
            k = 99999;
            while(k!=cpy){
                if(k==99999){
                    k = predecessor[i];
                }
                else{
                    k = predecessor[k];
                }
                if(k==cpy){
                    printf("%d", k+1);
                }       
                else{
                    printf("%d->", k+1);
                }         
            }
            printf("\n");
        }
    }
}

int** fileImport(int** costGraph, int* n) {
    int i = 0, j = 0;
    int source, destination, cost;
    FILE* fptr;
    if ((fptr = fopen("input.txt", "r")) == NULL) {
        printf("Error opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", n);
    costGraph = initMatrix(costGraph, *n);
    for (i = 0; i < (*n); i++) {
        costGraph[i][i] = 0;
    }
    for (i = 0; i < ((*n) * ((*n) - 1)); i++) {
        fscanf(fptr, "%d", &source);
        fscanf(fptr, "%d", &destination);
        fscanf(fptr, "%d", &cost);
        costGraph[source - 1][destination - 1] = cost;
    }
    fclose(fptr);
    return costGraph;
}

int main() {
    int** cost = NULL;
    int startNode = 0;
    int n = 0;
    cost = fileImport(cost, &n);
    printf("Enter starting Node:");
    scanf("%d", &startNode);
    printf("Source Vertex:%d\n", startNode);
    dijkstra(cost, n, startNode - 1);
    return 0;
}