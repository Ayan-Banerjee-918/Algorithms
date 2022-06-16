/*
Name: Ayan Banerjee
Roll: 13000120019

Question: I) Write a program to find the binomial coefficient using Dynamic programming method.
*/
#include <stdio.h>
#include <stdlib.h>

int calcBinomial(int n,int k,int** table){
    if(table[n][k]!=-1){
        return table[n][k];
    }
    else{
        if(k==0 || k==n){
            table[n][k]=1;
            return table[n][k];
        }
        else{
            table[n][k]=calcBinomial(n-1,k-1,table)+calcBinomial(n-1,k,table);
        }
    }
    return table[n][k];
}

int createLookupTable(int n,int k){
    int **lookupTable = (int**)malloc((n+1)*sizeof(int*));
    int i=0,j=0;
    for(i=0;i<n+1;i++){
        lookupTable[i]=(int*)malloc((k+1)*sizeof(int));
        for(j=0;j<k+1;j++){
            lookupTable[i][j]=-1;
        }
    }
    return calcBinomial(n,k,lookupTable);
}

void fileImport(int *arr){
    int i=0;
    FILE* fptr;
    if((fptr=fopen("BinomialCoefficientInput.txt","r"))==NULL){
        printf("Error opening file!\n");
        exit(0);
    }
    while((fscanf(fptr,"%d",&arr[i]))!=EOF){
        i++;
    }
    fclose(fptr);
}

int main(){
    int n=0,k=0;
    int arr[2];
    fileImport(arr);
    n=arr[0];
    k=arr[1];
    printf("n=%d\nk=%d\nBinomial Coefficient=%d\n",n,k,createLookupTable(n,k));
    return 0;
}
