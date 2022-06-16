#include <stdio.h>
#include <stdlib.h>

int** initMatrix(int n) {
    int** arr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }
    return arr;
}

int** splitMatrix(int** A, int n, int row, int col) {
    int n_new = n / 2;
    int** newMat = initMatrix(n_new);
    int r = row, c = col;
    for (int i = 0; i < n_new; i++) {
        c = col;
        for (int j = 0; j < n_new; j++) {
            newMat[i][j] = A[r][c++];
        }
        r++;
    }
    return newMat;
}

int** addMatrix(int** A, int** B, int n) {
    int** res = initMatrix(n);
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            res[i][j] = A[i][j] + B[i][j];
        }
    }
    return res;
}

int** subMatrix(int** A, int** B, int n) {
    int** res = initMatrix(n);
    int i = 0, j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            res[i][j] = A[i][j] - B[i][j];
        }
    }
    return res;
}

void joinMatrix(int** res, int** mat, int row, int col, int n) {
    int i = 0, j = 0;
    int r = row, c = col;
    for (i = 0; i < n; i++) {
        c = col;
        for (j = 0; j < n; j++) {
            res[r][c] = mat[i][j];
            c++;
        }
        r++;
    }
}

int** strassensMatrix(int** matA, int** matB, int n) {
    int** res = initMatrix(n);
    if (n > 1) {
        int** A11 = splitMatrix(matA, n, 0, 0);
        int** A12 = splitMatrix(matA, n, 0, n / 2);
        int** A21 = splitMatrix(matA, n, n / 2, 0);
        int** A22 = splitMatrix(matA, n, n / 2, n / 2);
        int** B11 = splitMatrix(matB, n, 0, 0);
        int** B12 = splitMatrix(matB, n, 0, n / 2);
        int** B21 = splitMatrix(matB, n, n / 2, 0);
        int** B22 = splitMatrix(matB, n, n / 2, n / 2);

        int** P = strassensMatrix(addMatrix(A11, A22, n / 2), addMatrix(B11, B22, n / 2), n / 2);
        int** Q = strassensMatrix(addMatrix(A21, A22, n / 2), B11, n / 2);
        int** R = strassensMatrix(A11, subMatrix(B12, B22, n / 2), n / 2);
        int** S = strassensMatrix(A22, subMatrix(B21, B11, n / 2), n / 2);
        int** T = strassensMatrix(addMatrix(A12, A11, n / 2), B22, n / 2);
        int** U = strassensMatrix(subMatrix(A21, A11, n / 2), addMatrix(B11, B12, n / 2), n / 2);
        int** V = strassensMatrix(subMatrix(A12, A22, n / 2), addMatrix(B22, B21, n / 2), n / 2);

        int** C11 = addMatrix(subMatrix(addMatrix(P, S, n / 2), T, n / 2), V, n / 2);
        int** C12 = addMatrix(R, T, n / 2);
        int** C21 = addMatrix(Q, S, n / 2);
        int** C22 = addMatrix(subMatrix(addMatrix(P, R, n / 2), Q, n / 2), U, n / 2);

        joinMatrix(res, C11, 0, 0, n / 2);
        joinMatrix(res, C12, 0, n / 2, n / 2);
        joinMatrix(res, C21, n / 2, 0, n / 2);
        joinMatrix(res, C22, n / 2, n / 2, n / 2);
    }
    else {
        res[0][0] = matA[0][0] * matB[0][0];
    }
    return res;
}

void fileImport(FILE** fptr, int** matA, int** matB, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(*fptr, "%d", &matA[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(*fptr, "%d", &matB[i][j]);
        }
    }
    fclose(*fptr);
}

void printArray(int **mat,int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void main() {
    int n = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in reading File!\n");
        exit(0);
    }
    fscanf(fptr, "%d", &n);
    int** matA = initMatrix(n);
    int** matB = initMatrix(n);
    int** res = initMatrix(n);
    fileImport(&fptr, matA, matB, n);
    printf("MAT A\n");
    printArray(matA, n);
    printf("MAT B\n");
    printArray(matB, n);
    printf("Strassens Matrix Result\n");
    res = strassensMatrix(matA, matB, n);
    printArray(res, n);
}