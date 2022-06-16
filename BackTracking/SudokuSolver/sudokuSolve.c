#include <stdio.h>
#include <stdlib.h>

void printGrid(int** grid,int N){
    int i = 0, j = 0;
    for (i = 0; i < N;i++){
        for (j = 0; j < N;j++){
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

int** fileImport(int** grid, int *N){
    int i = 0, j = 0;
    FILE *fptr = fopen("input.txt", "r");
    if(fptr==NULL){
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    grid = (int **)calloc(*N, sizeof(int *));
    for(i=0;i<*N;i++){
        grid[i] = (int *)calloc(*N, sizeof(int));
        for (j = 0; j < *N;j++){
            fscanf(fptr, "%d", &grid[i][j]);
        }
    }
    fclose(fptr);
    return grid;
}

int isSafe(int** grid,int num,int row,int col,int N){
    for (int i = 0; i < N;i++){
        if(grid[row][i]==num){
            return 0;
        }
    }
    for (int i = 0; i < N;i++){
        if(grid[i][col]==num){
            return 0;
        }
    }
    row = row - (row % 3);
    col = col - (col % 3);
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 3;j++){
            if(grid[row+i][col+j]==num){
                return 0;
            }
        }
    }
    return 1;
}

int solveGrid(int** grid,int N){
    int row = 0, col = 0;
    static int k = 0;
    int flag = 0;
    for (row = 0; row < N;row++){
        for (col = 0; col < N;col++){
            if(grid[row][col]==0){
                flag = 1;
                break;
            }
        }
        if (flag==1)
        {
            break;
        }
        
    }

    if(flag==0){
        return 1;
    }
    int num = 0;
    for (num = 1; num <= 9;num++){
        if(isSafe(grid,num,row,col,N)){
            grid[row][col] = num;
            if(solveGrid(grid,N)){
                if(k==0){
                    printf("Sudoku Grid:\n");
                    printGrid(grid, N);
                    k++;
                }
                return 1;
            }
            grid[row][col] = 0;
        }
    }
    return 0;
}

void solveSudoku(int** grid,int N){
    if(!solveGrid(grid, N)){
        printf("No Solution!");
    }
}

void main(){
    int **grid = NULL;
    int N = 0;
    grid = fileImport(grid, &N);
    printf("Initial Sudoku Grid:\n");
    printGrid(grid, N);
    solveSudoku(grid, N);
}