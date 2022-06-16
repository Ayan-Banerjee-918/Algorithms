#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** initMatrix(int n) {
	int** mat = (int**)malloc(n * sizeof(int*));
	int i = 0, j = 0;
	for (i = 0; i < n; i++) {
		mat[i] = (int*)malloc(n * sizeof(int));
		for (j = 0; j < n; j++) {
			mat[i][j] = 0;
		}
	}
	return mat;
}

int** addMatrix(int** matA, int** matB, int n) {
	int** res = initMatrix(n);
	int i = 0, j = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			res[i][j] = matA[i][j] + matB[i][j];
		}
	}
	return res;
}

int** subMatrix(int** matA, int** matB, int n) {
	int** res = initMatrix(n);
	int i = 0, j = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			res[i][j] = matA[i][j] - matB[i][j];
		}
	}
	return res;
}

int** splitMatrix(int** mat, int n, int row, int col) {
	int n_new = n / 2;
	int** newMat = initMatrix(n_new);
	int i, j, r = row, c = col;
	for (i = 0; i < n_new; i++) {
		c = col;
		for (j = 0; j < n_new; j++) {
			newMat[i][j] = mat[r][c];
			c++;
		}
		r++;
	}
	return newMat;
}

void joinMatrix(int** mat, int** res, int row, int col, int n) {
	int i, j, r = row, c = col;
	for (i = 0; i < n; i++) {
		c = col;
		for (j = 0; j < n; j++) {
			res[r][c] = mat[i][j];
			c++;
		}
		r++;
	}
}

int** strassensMult(int** matA, int** matB, int n) {
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

		int** P = strassensMult(addMatrix(A11, A22, n / 2), addMatrix(B11, B22, n / 2), n / 2);
		int** Q = strassensMult(addMatrix(A21, A22, n / 2), B11, n / 2);
		int** R = strassensMult(A11, subMatrix(B12, B22, n / 2), n / 2);
		int** S = strassensMult(A22, subMatrix(B21, B11, n / 2), n / 2);
		int** T = strassensMult(addMatrix(A12, A11, n / 2), B22, n / 2);
		int** U = strassensMult(subMatrix(A21, A11, n / 2), addMatrix(B11, B12, n / 2), n / 2);
		int** V = strassensMult(subMatrix(A12, A22, n / 2), addMatrix(B22, B21, n / 2), n / 2);

		int** C11 = addMatrix(subMatrix(addMatrix(P, S, n / 2), T, n / 2), V, n / 2);
		int** C12 = addMatrix(R, T, n / 2);
		int** C21 = addMatrix(Q, S, n / 2);
		int** C22 = addMatrix(subMatrix(addMatrix(P, R, n / 2), Q, n / 2), U, n / 2);

		joinMatrix(C11, res, 0, 0, n / 2);
		joinMatrix(C12, res, 0, n / 2, n / 2);
		joinMatrix(C21, res, n / 2, 0, n / 2);
		joinMatrix(C22, res, n / 2, n / 2, n / 2);
	}
	else {
		res[0][0] = matA[0][0] * matB[0][0];
	}
	return res;
}

void printMatrix(int** mat, int n) {
	int i = 0, j = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}
}

void importMatrix(int** matA, int** matB, int n) {
	int i = 0, j = 0, flag = 0;
	FILE* fptr;
	char input[9999];
	char* tmpline;
	if ((fptr = fopen("StrassenInput.txt", "r")) == NULL) {
		printf("Error! opening file");
		exit(0);
	}
	while (fgets(input, sizeof(input), fptr)) {
		tmpline = input;
		j = 0;
		char* token = strtok(tmpline, " ");
		while (token != NULL) {
			if (flag == 0) {
				matA[i][j] = atoi(token);
			}
			else {
				matB[i][j] = atoi(token);
			}
			token = strtok(NULL, " ");
			j++;
			if (j >= n) {
				break;
			}
		}
		i++;
		if (i >= n) {
			i = 0;
			flag++;
		}
	}
}

int main() {
	int n = 0, pow = 1;
	printf("Enter order of matrix:");
	scanf("%d", &n);
	while (pow < n) {
		pow = pow * 2;
	}
	int** matA = initMatrix(pow);
	int** matB = initMatrix(pow);
	importMatrix(matA, matB, n);
	printf("Matrix A\n");
	printMatrix(matA, pow);
	printf("Matrix B\n");
	printMatrix(matB, pow);
	printf("Matrix Multiplication Result\n");
	printMatrix(strassensMult(matA, matB, pow), pow);
	return 0;
}