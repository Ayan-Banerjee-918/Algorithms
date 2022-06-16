#include <stdio.h>
#include <stdlib.h>

int findMinimum(int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

int minCost(int** cost, int N) {
    int i = 0, j = 0;
    for (i = 1; i < N; i++) {
        for (j = 0; j < 3; j++) {
            if (j == 0) {
                cost[i][j] += findMinimum(cost[i-1][1],cost[i-1][2]);
            }
            else if (j == 1) {
                cost[i][j] += findMinimum(cost[i - 1][0], cost[i - 1][2]);
            }
            else {
                cost[i][j] += findMinimum(cost[i - 1][0], cost[i - 1][1]);
            }
        }
    }
    return findMinimum(findMinimum(cost[N-1][0], cost[N-1][1]), cost[N-1][2]);
}

int** fileImport(int** cost, int* N) {
    int i = 0, j = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in reading file!");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    cost = (int**)malloc(*N * sizeof(int*));
    for (i = 0; i < *N; i++) {
        cost[i] = (int*)malloc(3 * sizeof(int));
        for (j = 0; j < 3; j++) {
            fscanf(fptr, "%d", &cost[i][j]);
        }
    }
    fclose(fptr);
    return cost;
}

int main() {
    int **cost=NULL;
    int i = 0, j = 0, N = 0;
    cost = fileImport(cost, &N);
    printf("Minimum Cost = %d\n", minCost(cost, N));
    return 0;
}