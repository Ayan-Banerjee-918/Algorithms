                         ___SOURCE_CODE___
/*
Name: Ayan Banerjee
Roll: 13000120019

Question: I) Write a program using the single-source-shortest-path problem to find out the shortest path from the source vertex ‘s’ using the Bellman-Ford’s algorithm, using the dynamic programming technique.
*/
#include <stdio.h>
#include <stdlib.h>

int** init2DArray(int **arr,int n){
    arr=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        arr[i]=(int*)malloc(n*sizeof(int));
    }
    return arr;
}

void bellmanFord(int n,int **arr, int *distance, int *predecessor){
    int i,j=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j && arr[i][j]!=0){
                if(distance[i]+arr[i][j]<distance[j]){
                    distance[j]=distance[i]+arr[i][j];
                    predecessor[j]=i;
                }
            }
        }
    }
}

int fileImport(int n,int **arr){
    FILE* fptr=fopen("BellmanFordInput.txt","r");
    if(fptr==NULL){
        printf("Error inputting file!");
        return 0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fscanf(fptr, "%d ",&arr[i][j]);
        }
    }
    fclose(fptr);
    return 0;
}

int main(){
    int **cost=NULL;
    int *distance=NULL;
    int *predecessor=NULL;
    int *path=NULL;
    char ch[]={'S','t','x','y','z'};
    int n=5;
    int j=0,k=0;;
    int start=0;
    cost=init2DArray(cost,n);
    distance=(int*)malloc(n*sizeof(int));
    predecessor=(int*)malloc(n*sizeof(int));
    path=(int*)malloc(n*sizeof(int));
    fileImport(n,cost);
    for(int i=0;i<n;i++){
        if(i==0){
            distance[i]=0;
        }
        else{
            distance[i]=99999;
        }
    }
    bellmanFord(n,cost,distance,predecessor);
    printf("Source Vertex: S\n");
    for(int i=0;i<n;i++){
        if(i!=start){
            printf("\nShortest distance from S to %c: %d\n",ch[i],distance[i]);
            j=i;
            while(j!=start){
                j=predecessor[j];
                path[k++]=j+1;
            }
            printf("Path=");
            for(j=k-1;j>=0;j--){
                printf("%c->",ch[path[j]-1]);
            }
            printf("%c\n",ch[i]);
            k=0;
        }
    }
    return 0;
}
