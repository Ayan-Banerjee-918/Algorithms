#include <stdio.h>
#include <stdlib.h>

void printBrackets(int i,int j,int **bracket){
    if(i==j){
        printf("A%d ", i);
    }
    else{
        printf("( ");
        printBrackets(i, bracket[i][j], bracket);
        printBrackets(bracket[i][j] + 1, j, bracket);
        printf(" )");
    }
}

int calcMatrixMult(int **table,int **bracket,int *dist){
    for (int i = n; i > 0;i--){
        for (int j = i; j <= n;j++){
            if(i==j){
                table[i][j] = 0;
            }
            for (int k = i; k <= j - 1;k++){
                int min = table[i][k] + table[k + 1][j] + (dist[i-1]*dist[j]*dist[k]);
                if (table[i][j]==-1){
                    table[i][j] = min;
                    bracket[i][j] = k;
                }
                else{
                    if(min<table[i][j]){
                        table[i][j] = min;
                        bracket[i][j] = k;
                    }
                }
            }
        }
    }
    printBrackets(1, n, bracket);
    return table[1][n];
}