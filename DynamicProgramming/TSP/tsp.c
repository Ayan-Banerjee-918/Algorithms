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

int least(int source,int **graph,int *visited,int *minCost,int n){
    int i = 0, tmp = 9999;
    int min = 9999, tmp1;
    for (i = 0; i < n;i++){
        if((graph[source][i]!=0)&&(visited[i]==0)){
            if(graph[source][i]+graph[i][source]<min){
                min = graph[i][source] + graph[source][i];
                tmp1 = graph[source][i];
                tmp = i;
            }
        }
    }
    if(min!=9999){
        *minCost += tmp1;
    }
    return tmp;
}

void tsp(int source,int **graph,int *visited, int* minCost, int n){
    int i = 0, tmp = 0;
    visited[source] = 1;
    printf("%d->",source+1);
    tmp = least(source,graph,visited,minCost,n);
    if(tmp==9999){
        tmp = 0;
        printf("%d", tmp + 1);
        *minCost += graph[source][tmp];
        return;
    }
    tsp(tmp, graph, visited, minCost,n);
}

int main(){
    int **graph = NULL;
    int *visited = NULL;
    int n = 0, minCost = 0, i = 0;
    graph = fileImport(graph, &n);
    visited = (int*)malloc(n*sizeof(int));
    for (i = 0; i < n;i++){
        visited[i] = 0;
    }
    tsp(0, graph, visited,&minCost,n);
    printf("\nThe least cost for entire path: %d\n", minCost);
    return 0;
}