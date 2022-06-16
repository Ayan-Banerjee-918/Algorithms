#include <stdio.h>
#include <stdlib.h>

void printBrackets(int i,int j,int **bracketTable){
    if (i == j) {
        printf(" A%d ", i);
    }
    else {
        printf("( ");
        printBrackets(i, bracketTable[i][j], bracketTable);
        printBrackets(bracketTable[i][j] + 1, j, bracketTable);
        printf(" )");
    }
}

int calcMatMult(int* arr,int **table,int n,int **bracketTable){
    int i = 0, j = 0, k = 0, min = 0;
    for (i = n; i > 0;i--){
        for (j = i; j <= n; j++){
            if(i==j){
                table[i][j]=0;
            }
            else{
                for (int k = i; k <= j - 1;k++){
                    min = table[i][k] + table[k + 1][j] + (arr[i - 1] * arr[j] * arr[k]);
                    if(table[i][j]==-1){
                        table[i][j] = min;
                        bracketTable[i][j] = k;
                    }
                    else if(min<table[i][j]){
                        table[i][j] = min;
                        bracketTable[i][j] = k;
                    }
                }
            }
        }
    }
    printBrackets(1, n, bracketTable);
    printf("\n");
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= n;j++){
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    return table[1][n];
}

int createLookupTable(int *arr,int n){
    int **lookupTable = (int **)malloc(n * sizeof(int *));
    int **bracketTable = (int **)malloc(n * sizeof(int *));
    int i = 0, j = 0;
    for (i = 0; i <= n;i++){
        lookupTable[i] = (int *)malloc(n * sizeof(int));
        bracketTable[i] = (int *)malloc(n * sizeof(int));
        for (j = 0; j <= n;j++){
            lookupTable[i][j] = -1;
            bracketTable[i][j] = -1;
        }
    }
    return calcMatMult(arr, lookupTable, n, bracketTable);
}

int fileImport(int *arr){
    int i = 0;
    FILE *fptr = fopen("input.txt", "r");
    if(fptr==NULL){
        printf("Error in opening file!\n");
        exit(0);
    }
    while(fscanf(fptr,"%d",&arr[i])!=EOF){
        i++;
    }
    fclose(fptr);
    return i - 1;
}

int main(){
    int arr[9999];
    int n = fileImport(arr);
    printf("Minimum number of scalar matrix multiplications are: %d\n", createLookupTable(arr,n));
    return 0;
}