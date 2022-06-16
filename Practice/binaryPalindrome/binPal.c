#include <stdio.h>
#include <stdlib.h>

int* decimalToBinary(int num,int *cnt)
{
    int binaryNum[32];
    int* bin = NULL;
    int i = 0;
    while (num > 0) {
        binaryNum[i] = num % 2;
        num = num / 2;
        i++;
    }
    bin = (int*)malloc(i * sizeof(int));
    for (int j = i - 1; j >= 0; j--) {
        bin[(*cnt)] = binaryNum[j];
        (*cnt)++;
    }
    return bin;
}

int isPalindrome(int N) {
    int* binary = NULL;
    int cnt = 0;
    int i = 0;
    binary = decimalToBinary(N,&cnt);
    if (cnt % 2 == 1) {
        for (i = cnt / 2 - 1; i >= 0; i--) {
            if (binary[i] != binary[cnt - 1 - i]) {
                return 0;
            }
        }
    }
    else {
        for (i = cnt / 2 - 1; i >= 0; i--) {
            if (binary[i] != binary[cnt - 1 - i]) {
                return 0;
            }
        }
    }
    return 1;
}

int* minCount(int N, int* dp) {
    int i = 0, j = 0, k = 1;
    if (isPalindrome(N)) {
        printf("Palindrome number in binary representation: %d\n", N);
        return dp;
    }
    for (i = N; i>=0; i--) {
        if (!isPalindrome(i)) {
            dp[i] = k++;
        }
        else {
            dp[i] = dp[i + 1];
            break;
        }
    }
    k = 2;
    for (j = N + 1;; j++) {
        if (!isPalindrome(j)) {
            dp[j] = k++;
        }
        else {
            dp[j] = dp[j - 1];
            break;
        }
    }
    if (dp[i] < dp[j]) {
        printf("Palindrome number in binary representation: %d\n", i);
        dp[N] = dp[i];
    }
    else if(dp[j]<dp[i]) {
        printf("Palindrome number in binary representation: %d\n", j);
        dp[N] = dp[j];
    }
    else {
        printf("Palindrome numbers in binary representation: %d and %d\n", i, j);
        dp[N] = dp[i];
    }
    return dp;
}

void fileImport(int* N) {
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening File!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    fclose(fptr);
}

void main() {
    int N = 0, count = 0, i = 0;
    int* dp = (int*)calloc(100, sizeof(int));
    fileImport(&N);
    printf("Original Number: %d\n", N);
    dp=minCount(N,dp);
    printf("Minimum number of operations required : %d\n", dp[N]);
}