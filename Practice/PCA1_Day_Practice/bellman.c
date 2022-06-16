#include <stdio.h>
#include <stdlib.h>

void bellmanFord(int n,int **weight,int* distance,int * pred){
    int i = 0, j = 0;
    for (i = 0; i < n;i++){
        for (j = 0; j < n; j++)
        {
            if(i!=j){
                if(distance[i]+weight[i][j]<distance[j]){
                    distance[j] = distance[i] + weight[i][j];
                    predecessor[j] = i;
                }
            }
        }
    }
}