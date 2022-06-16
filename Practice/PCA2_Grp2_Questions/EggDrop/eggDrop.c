#include <stdio.h>
#include <stdlib.h>

int max(int a,int b){
    return (a > b) ? a : b;
}

int eggDrop(int N,int K){
    int i = 0, j = 0,x = 0,res = 0;
    int **dp = (int **)malloc((N+1) * sizeof(int *));
    for (i = 0; i <= N;i++){
        dp[i] = (int *)malloc((K + 1) * sizeof(int));
        for (j = 0; j <= K;j++){
            dp[i][j] = 999999;
        }
    }
    for (i = 1; i <= N;i++){
        dp[i][0] = 0;
        dp[i][1] = 1;
    }
    for (j = 1; j <= K;j++){
        dp[1][j] = j;
    }
    for (i = 2; i <= N;i++){
        for (j = 2; j <= K;j++){
            for (x = 1; x < j;x++){
                res = 1 + max(dp[i - 1][x - 1], dp[i][j - x]);
                if(res<dp[i][j]){
                    dp[i][j] = res;
                }
            }
        }
    }
    return dp[N][K];
}

void fileImport(int* N,int* K){
    FILE *fptr = fopen("input.txt", "r");
    if(fptr==NULL){
        printf("Error in reading file!");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    fscanf(fptr, "%d", K);
    fclose(fptr);
}

void main(){
    int N = 0, K = 0;
    fileImport(&N, &K);
    printf("N = %d\nK = %d\nMinimum Number of Trials required so that the eggs do not break is %d \n", N, K, eggDrop(N, K));
}