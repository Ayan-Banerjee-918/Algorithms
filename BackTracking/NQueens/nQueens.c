#include <stdio.h>
#include <stdlib.h>

void printBoard(int** board, int N)
{
    static int k = 1;
    printf("Solution %d\n", k++);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (board[i][j])
                printf("Q%d ",i+1);
            else
                printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int isValid(int** board, int row, int col, int N) {
    int i, j;
    for (i = 0; i < row; i++) {
        if (board[i][col])
            return 0;
    }
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return 0;
    }
    for (i = row, j = col; j < N && i >= 0; i--, j++) {
        if (board[i][j])
            return 0;
    }
    return 1;
}

int solveBoard(int** board, int row, int N) {
    if (row == N) {
        printBoard(board, N);
        return 1;
    }
    int res = 0;
    for (int i = 0; i < N; i++)
    {
        if (isValid(board, row, i, N))
        {
            board[row][i] = 1;
            res = solveBoard(board, row + 1, N) || res;
            board[row][i] = 0;
        }
    }
    return res;
}

void solveNQueens(int N) {
    int i = 0;
    int** board = (int**)calloc(N, sizeof(int*));
    for (i = 0; i < N; i++) {
        board[i] = (int*)calloc(N, sizeof(int));
    }
    if (solveBoard(board, 0, N) == 0) {
        printf("No Solution.\n");
    }
}

void importN(int* N) {
    int i = 0, j = 0, n = 4;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    fclose(fptr);
}

void main() {
    int N = 0;
    importN(&N);
    solveNQueens(N);
}