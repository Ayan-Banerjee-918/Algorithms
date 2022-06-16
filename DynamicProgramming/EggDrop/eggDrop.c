#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { 
    return (a > b) ? a : b; 
}

int eggDrop(int N, int K)
{
    int res;
    int i, j, x;
    int **eggFloor = (int **)malloc((N + 1) * sizeof(int *));
    for (i = 0; i <= N + 1;i++){
        eggFloor[i] = (int *)malloc((K + 1) * sizeof(int));
    }
    for (i = 1; i <= N; i++) {
        eggFloor[i][1] = 1;
        eggFloor[i][0] = 0;
    }
    for (j = 1; j <= K; j++){
        eggFloor[1][j] = j;
    } 
    for (i = 2; i <= N; i++) {
        for (j = 2; j <= K; j++) {
            eggFloor[i][j] = 9999999;
            for (x = 1; x <= j; x++) {
                res = 1 + max(eggFloor[i - 1][x - 1], eggFloor[i][j - x]);
                if (res < eggFloor[i][j]){
                    eggFloor[i][j] = res;
                }
            }
        }
    }
    return eggFloor[N][K];
}

void fileImport(int* N, int* K) {
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    fscanf(fptr, "%d", K);
    fclose(fptr);
}
 
int main()
{
    int N = 0, K = 0;
    fileImport(&N, &K);
    printf("N = %d\nK = %d\nMinimum Number of Trials required so that the eggs do not break is %d \n", N, K, eggDrop(N, K));
    return 0;
}