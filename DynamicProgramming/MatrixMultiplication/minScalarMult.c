/*
Name: Ayan Banerjee
Roll: 13000120019

Question: I) Write a program to Find the minimum number of scalar multiplication needed for chain of matrix whose sequences are < 5, 10, 3, 12, 5, 50, 6 >using the dynamic programming technique.
*/

#include <stdio.h>
#include <stdlib.h>

void printBrackets(int i, int j, int** bracketTable) {
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

int calcMultCount(int* arr, int n, int** table,int** bracketTable) {
    int min;
    for (int i = n; i > 0; i--) {
        for (int j = i; j <= n; j++) {
            if (i == j) {
                table[i][j] = 0;
            }
            else {
                for (int k = i; k < j; k++) {
                    min = table[i][k] + table[k + 1][j] + (arr[i - 1] * arr[k] * arr[j]);
                    if (table[i][j] == -1) {
                        table[i][j] = min;
                        bracketTable[i][j] = k;
                    }
                    if (min < table[i][j]) {
                        table[i][j] = min;
                        bracketTable[i][j] = k;
                    }
                }
            }
        }
    }
    printBrackets(1, n, bracketTable);
    printf("\n");
    return table[1][n];
}

int calcMultCountRecur(int* arr, int i, int j, int** table,int** bracketTable) {
    int min=999999,sum,tmp;
    if(i==j){
        return table[i][j] = 0;
    }
    if(table[i][j]!=-1){
        return table[i][j];
    }
    for (int k = i; k < j;k++){
        sum = calcMultCountRecur(arr, i, k, table, bracketTable) + calcMultCountRecur(arr, k + 1, j, table, bracketTable) + arr[i - 1] * arr[k] * arr[j];
        if(sum<min){
            min = sum;
            tmp = k;
        }
    }
    table[i][j] = min;
    bracketTable[i][j] = tmp;
    return table[i][j];
}

int** createLookupTable(int** lookupTable, int n) {
    lookupTable = (int**)malloc(n * sizeof(int*));
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        lookupTable[i] = (int*)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            lookupTable[i][j] = -1;
        }
    }
    return lookupTable;
}


int fileImport(int *arr){
    int i=0;
    FILE* fptr;
    if((fptr=fopen("ChainMatrixMult.txt","r"))==NULL){
        printf("Error opening file!\n");
        exit(0);
    }
    while((fscanf(fptr,"%d",&arr[i]))!=EOF){
        i++;
    }
    fclose(fptr);
    return i;
}

void main() {
    int arr[999];
    int n = fileImport(arr);
    int** lookupTable=NULL;
    int** temp = NULL;
    lookupTable=createLookupTable(lookupTable, n);
    temp = createLookupTable(temp, n);
    printf("Minimum number of scalar matrix multiplications are: %d\n", calcMultCountRecur(arr, 1, n-1, lookupTable,temp));
    printBrackets(1, n-1, temp);
    printf("\n");
}