#include <stdio.h>
#include <stdlib.h>

int count(int* S, int N, int Scnt) {
    int i = 0, j = 0, cnt = 0;
    int** dp = (int**)malloc((Scnt + 1) * sizeof(int*));
    // dp[0] = 1;
    // for (int i = 1; i <= N; i++) {
    //     dp[i] = 0;
    // }
    // j = 0;
    // while (cnt != Scnt) {
    //     int coin = S[j++];
    //     for (i = 0; i <= N; i++) {
    //         if (i >= coin) {
    //             dp[i] += dp[i - coin];
    //         }
    //     }
    //     cnt++;
    // }
    for (i = 0; i <= Scnt;i++){
        dp[i] = (int *)calloc((N + 1), sizeof(int));
    }
    for(i = 0; i <= Scnt; i++)
        dp[i][0] = 1;
    
    for(j = 0; j <= N; j++)
        dp[0][j] = 0;

    for (i = 1; i <= Scnt;i++){
        for (j = 1; j <= N;j++){
            if(j<S[i-1]){
                dp[i][j] = dp[i - 1][j];
            }
            else{
                dp[i][j] = dp[i - 1][j] + dp[i][j - S[i-1]];
            }
        }
    }
    for (i = 0; i <= Scnt;i++){
        for (j = 0; j <= N;j++){
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
    return dp[Scnt][N];
}

int fileImport(int* S, int* N) {
    int i = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in reading file!");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    while (fscanf(fptr, "%d", &S[i]) != EOF) {
        i++;
    }
    fclose(fptr);
    return i;
}

int main() {
    int S[999];
    int N = 0;
    int Scnt = fileImport(S, &N);
    printf("Count : %d\n", count(S, N, Scnt));
    return 0;
}