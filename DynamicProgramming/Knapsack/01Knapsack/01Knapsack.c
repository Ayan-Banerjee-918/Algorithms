#include <stdio.h>
#include <stdlib.h>

int maximum(int a,int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

int knapsack(int W,int *w,int *v,int n){
    int i=0,j=0;
    int tmp=0;
    int **cost=(int**)malloc((n+1)*sizeof(int*));
    for(i=0;i<=n;i++){
        cost[i]=(int*)malloc((W+1)*sizeof(int));
    }
    for(i=0;i<=n;i++){
        for(j=0;j<=W;j++){
            if(i==0 || W==0){
                cost[i][j]=0;
            }
            else if(w[i-1]<=W && j>=w[i-1]){
                cost[i][j]=maximum(v[i-1]+cost[i-1][W-w[i-1]],cost[i-1][j]);
            }
            else{
                cost[i][j]=cost[i-1][j];
            }
        }
    }
    return cost[n][W];
}

void fileImport(int* n, int* W, int* v, int* w) {
    int i = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in reading file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", n);
    if (*n < 1) {
        printf("Number of items less than 1!\n");
        exit(0);
    }
    fscanf(fptr, "%d", W);
    for (i = 0; i < *n; i++) {
        fscanf(fptr, "%d", &v[i]);
    }
    for (i = 0; i < *n; i++) {
        fscanf(fptr, "%d", &w[i]);
    }
    fclose(fptr);
}

int main() {
    int i = 0, n = 0, W = 0;
    int* v = (int*)malloc(10 * sizeof(int));
    int* w = (int*)malloc(10 * sizeof(int));
    fileImport(&n, &W, v, w);
    printf("Number of objects: %d\n", n);
    printf("Weight of knapsack: %d\n", W);
    printf("Value\tWeight\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", v[i], w[i]);
    }
    printf("Minimal Cost: %d",knapsack(W,w,v,n));
    free(v);
    free(w);
    return 0;
}
