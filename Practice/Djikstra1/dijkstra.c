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

int** fileImport(int *N, int **graph){
    int i = 0, j = 0;
    FILE *fptr = fopen("input.txt", "r");
    if(fptr==NULL){
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    graph = init2DArray(graph, *N);
    for (i = 0; i < *N;i++){
        for (j = 0; j < *N;j++){
            fscanf(fptr, "%d", &graph[i][j]);
        }
    }
    fclose(fptr);
    return graph;
}

void dijkstra(int**graph,int N,int start){
    int *path = (int *)calloc(N, sizeof(int));
    int *distance = (int *)calloc(N, sizeof(int));
    int i = 0, j = 0, cnt = 0;
    for (i = 0; i < N;i++){
        distance[i] = 999999;
    }
    path[0] = start;
    cnt++;
    distance[start] = 0;
    while(cnt!=N){
        
    }
}

void main(){
    int **graph=NULL;
    int N = 0;
    graph = fileImport(graph, &N);
    dijkstra(graph,N,0);
}