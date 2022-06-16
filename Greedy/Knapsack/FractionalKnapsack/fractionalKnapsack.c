#include <stdio.h>
#include <stdlib.h>

void swap(float* a, float* b) {
    float c = *a;
    *a = *b;
    *b = c;
}

void heapify(float* objCount, float* f, float* v, float* w, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && f[left] < f[smallest]) {
        smallest = left;
    }
    if (right < n && f[right] < f[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&f[i], &f[smallest]);
        swap(&v[i], &v[smallest]);
        swap(&w[i], &w[smallest]);
        swap(&objCount[i], &objCount[smallest]);
        heapify(objCount, f, v, w, n, smallest);
    }
}

void heapsort(float* objCount, float* f, float* v, float* w, int n) {
    int i = 0;
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(objCount, f, v, w, n, i);
    }
    for (i = n - 1; i >= 0; i--) {
        swap(&f[0], &f[i]);
        swap(&v[0], &v[i]);
        swap(&w[0], &w[i]);
        swap(&objCount[0], &objCount[i]);
        heapify(objCount, f, v, w, i, 0);
    }
}

void fileImport(int* n, int* W, float* v, float* w) {
    int i = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in reading file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", n);
    if (*n < 1) {
        printf("Number of items less than 1!\n");
        exit(0);
    }
    fscanf(fptr, "%d", W);
    for (i = 0; i < *n; i++) {
        fscanf(fptr, "%f", &v[i]);
    }
    for (i = 0; i < *n; i++) {
        fscanf(fptr, "%f", &w[i]);
    }
    fclose(fptr);
}

void knapsack(float* objCount, float* v, float* w, int n, int W) {
    float* x = (float*)malloc(n * sizeof(float));
    int i = 0, j = 0, tmp = 0;
    float profit = 0.0f;
    for (i = 0; i < n; i++) {
        x[i] = 0.0;
    }
    for (i = 0; i < n; i++) {
        if (w[i] < W) {
            x[i] = 1.0;
            profit += v[i];
            W = W - w[i];
        }
        else {
            break;
        }
    }
    if (i < n) {
        x[i] = W / w[i];
    }
    profit += (x[i] * v[i]);
    printf("\nOptimal arrangement:\n( ");
    for (i = 0; i < n; i++) {
        tmp = 0;
        while (objCount[tmp] != i+1) {
            tmp++;
        }
        printf("%.2f ",x[tmp]);
    }
    printf(")\n\n");
    printf("Object Number\tValue\tWeight\n");
    for (i = 0; i < n; i++) {
        printf("%.0f\t\t%.0f\t%.0f\n", objCount[i], v[i], w[i]);
    }
    printf("\nMax Profit: %.2f\n", profit);
}

int main() {
    int i = 0, n = 0, W = 0;
    float* v = (float*)malloc(10 * sizeof(float));
    float* w = (float*)malloc(10 * sizeof(float));
    fileImport(&n, &W, v, w);
    float* f = (float*)malloc(n * sizeof(float));
    float* objCount = (float*)malloc(n * sizeof(float));
    printf("Number of objects: %d\n", n);
    printf("Weight of knapsack: %d\n", W);
    printf("Object Number\tValue\tWeight\n");
    for (int i = 0; i < n; i++) {
        objCount[i] = (i+1);
        printf("%d\t\t%.0f\t%.0f\n", (i + 1), v[i], w[i]);
    }
    for (i = 0; i < n; i++)
    {
        f[i] = v[i] / w[i];
    }
    heapsort(objCount, f, v, w, n);
    knapsack(objCount, v, w, n, W);
    free(v);
    free(w);
    return 0;
}