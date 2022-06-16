#include <stdio.h>
#include <stdlib.h>

int** initMatrix(int n){
    int **arr = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n;i++){
        arr[i] = (int *)malloc(n * sizeof(int));
    }
    return arr;
}

int minimum(int a,int b){
    if (a<b){
        return a;
    }
    else{
        return b;
    }
}

int tsp(int **graph,long mask,int pos, long VISITED_ALL, int n, int* predecessor){
    if(mask==VISITED_ALL){
        return graph[pos][0];
    }
    int ans = 99999;
    for (int city = 0; city < n;city++){
        if(pos==city){
            continue;
        }
        if((mask & (1<<city))==0){
            int newAns = graph[pos][city] + tsp(graph, (mask | 1 << city), city, VISITED_ALL, n, predecessor);
            int oldAns = ans;
            ans = minimum(ans, newAns);
            if(ans!=oldAns){
                predecessor[city] = pos;
            }
        }
    }
    return ans;
}

void fileImport(FILE** fptr,int **graph,int n){
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            fscanf(*fptr, "%d", &graph[i][j]);
        }
    }
    fclose(*fptr);
}

void printGraph(int **graph,int n){
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int n = 0;
    FILE *fptr = fopen("input.txt", "r");
    if(fptr==NULL){
        printf("Error!\n");
        exit(0);
    }
    fscanf(fptr, "%d", &n);
    int **graph = initMatrix(n);
    int *predecessor = (int *)malloc(n * sizeof(int));
    fileImport(&fptr, graph, n);
    printf("Graph:\n");
    printGraph(graph, n);
    long VISITED_ALL = (1 << n) - 1;
    printf("Shortest Path Distance : %d\n",tsp(graph, 1, 0, VISITED_ALL, n, predecessor));
    for (int i = 0; i < n;i++){
        printf("%d\t", predecessor[i]);
    }
    printf("\n");
    return 0;
}