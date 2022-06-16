#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** init2DMatrix(int **graph,int n){
    int i = 0,j = 0;
    graph = (int **)malloc(n * sizeof(int));
    for (i = 0; i < n;i++){
        graph[i] = (int *)malloc(n * sizeof(int));
        for (j = 0; j < n;j++){
            graph[i][j] = 0;
        }
    }
    return graph;
}

int** importGraph(int **graph,int *n){
    int i = 0, j = 0;
    FILE *fptr = fopen("input.txt", "r");
    if(fptr==NULL){
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", n);
    graph = init2DMatrix(graph,*n);
    for (i = 0; i < *n;i++){
        for (j = 0; j < *n;j++){
            fscanf(fptr, "%d", &graph[i][j]);
        }
    }
    fclose(fptr);
    return graph;
}

int findCost(int** graph, int**dp,int**path,int source,int toVisitMask, int n, int subsetCnt){
    int i = 0, j = 0;
    int tmp = 0, min = 9999999;
    int mask = 0, chkMask = 0;
    if(dp[source][toVisitMask]!=-1){
        return dp[source][toVisitMask];
    }
    for (i = 0; i < n; i++){
        mask = subsetCnt - (1 << i);
        chkMask = mask & toVisitMask;
        if(chkMask!=toVisitMask){
            tmp = graph[source][i] + findCost(graph, dp, path, i, chkMask, n, subsetCnt);
            if(tmp<min){
                min = tmp;
                path[source][toVisitMask] = i;
            }
        }
    }
    return dp[source][toVisitMask] = min;
}

void printPath(int** path,int source,int toVisitMask, int subsetCnt){
    if(path[source][toVisitMask]==-1){
        return;
    }
    int tmp = path[source][toVisitMask];
    int mask = subsetCnt - (1 << tmp);
    printf("%d->", tmp+1);
    printPath(path, tmp, mask & toVisitMask, subsetCnt);
}

int tsp(int** graph,int n){
    int i = 0, j = 0, cost = 0;
    int subsetCnt = (int)pow(2, n);
    int **dp = (int **)malloc(n * sizeof(int*));
    int **path = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n;i++){
        dp[i] = (int *)malloc(subsetCnt * sizeof(int));
        path[i] = (int *)malloc(subsetCnt * sizeof(int));
        for (int j = 0; j < subsetCnt;j++){
            if(j==0){
                dp[i][j] = graph[i][j];
            }
            else{
                dp[i][j] = -1;
            }
            path[i][j] = -1;
        }
    }
    cost = findCost(graph, dp, path, 0, subsetCnt - 2, n, subsetCnt-1);
    printf("The min Path is:\n1->");
    printPath(path, 0, subsetCnt - 2, subsetCnt - 1);
    printf("->1\n");
    return cost;
}

int main(){
    int n = 0,cost = 0;
    int **graph = NULL;
    graph = importGraph(graph, &n);
    cost = tsp(graph, n);
    printf("Minimum cost is %d\n", cost);
    return 0;
}