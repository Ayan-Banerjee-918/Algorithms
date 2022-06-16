#include <stdio.h>
#include <stdlib.h>

int maximum(int a, int b, int c) {
    return ((a > b && a > c) ? a : b > a && b > c ? b : c);
}

int calcMidSum(int* arr, int low, int m, int high) {
    int leftSum = 0, rightSum = 0, sum = 0;
    int i = 0;
    for (i = m; i >= low; i--)
    {
        sum = sum + arr[i];
        if (sum > leftSum) {
            leftSum = sum;
        }
    }
    sum = 0;
    for (i = m + 1; i <= high; i++) {
        sum = sum + arr[i];
        if (sum > rightSum) {
            rightSum = sum;
        }
    }
    return maximum(leftSum + rightSum, leftSum, rightSum);
}

int calcMaxSum(int* arr, int low, int high) {
    if (low < high) {
        int m = (low + high) / 2;
        return maximum(calcMaxSum(arr, low, m), calcMaxSum(arr, m + 1, high), calcMidSum(arr, low, m, high));
    }
}

int* fileImport(int* arr, int* N) {
    int i = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    arr = (int*)malloc(*N * sizeof(int));
    for (i = 0; i < *N; i++) {
        fscanf(fptr, "%d", &arr[i]);
    }
    fclose(fptr);
    return arr;
}

void main() {
    int* arr=NULL;
    int N = 0;
    arr = fileImport(arr, &N);
    printf("The maximum Sum is: %d\n", calcMaxSum(arr, 0, N - 1));
}