#include <stdio.h>
#include <stdlib.h>

void floydwarshall(int** graph,int n){
    int **predecessor = (int **)malloc(n * sizeof(int *));
    int min = 0;
    int i = 0, j = 0, k = 0;
    for (i = 0; i < n;i++){
        predecessor[i] = (int *)malloc(n * sizeof(int));
        for (j = 0; j < n;j++){
            predecessor[i][j] = j + 1;
        }
    }
    for (k = 0; k < n;k++){
        for (i = 0; i < n;i++){
            for (j = 0; j < n;j++){
                if(graph[i][k]+graph[k][j]<graph[i][j]){
                    graph[i][j] = graph[i][k] + graph[k][j];
                    predecessor[i][j] = k + 1;
                }
            }
        }
    }
    for (i = 0; i < n;i++){
        for (j = 0; j < n;j++){
            if(i==j){
                continue;
            }
            printf("Shortest distance from %d to %d is: %d", (i + 1), (j + 1), graph[i][j]);
            printf("Path from %d to %d: %d->", i + 1, j + 1, i+1);
            min = predecessor[i][j];
            while(min!=(j+1)){
                printf("%d->", min);
                min = predecessor[min-1][j];
            }
            printf("%d", j + 1);
        }
    }
}