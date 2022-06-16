#include <stdio.h>
#include <stdlib.h>

int calcBinCoeff(int **table, int n, int k){
    if (table[n][k]!=-1){
        return table[n][k];
    }
    else{
        if(k==0 || k==n){
            return 1;
        }
        else{
            table[n][k] = calcBinCoeff(table, n - 1, k - 1) + calcBinCoeff(table, n - 1, k);
        }
    }
    return table[n][k];
}

int createLookUpTable(int n,int k){
    int **lookupTable = (int **)malloc(n * sizeof(int *));
    int i = 0, j = 0;
    for (i = 0; i <= n;i++){
        lookupTable[i] = (int *)malloc(n * sizeof(int));
        for (j = 0; j <= n;j++){
            lookupTable[i][j] = -1;
        }
    }
    return calcBinCoeff(lookupTable, n, k);
}

void fileImport(int *arr){
    int i = 0;
    FILE *fptr = fopen("input.txt", "r");
    if(fptr==NULL){
        printf("Error in inputting file!\n");
        exit(0);
    }
    while(fscanf(fptr,"%d",&arr[i++])!=EOF){
        if(i==2){
            break;
        }
    }
    fclose(fptr);
}

int main(){
    int n = 0, k = 0;
    int arr[2];
    fileImport(arr);
    n = arr[0];
    k = arr[1];
    printf("Binomial Coefficient Val: %d\n", createLookUpTable(n, k));
    return 0;
}