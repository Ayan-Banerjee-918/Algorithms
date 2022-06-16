#include <stdio.h>
#include <stdlib.h>

void swap(float* a, float* b) {
    float c = *a;
    *a = *b;
    *b = c;
}

int maximum(int a,int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
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

void fractionalknapsack(float* objCount, float* v, float* w, int n, int W) {
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

int knapsackdp(int W,float *w,float *v,int n){
    int i=0,j=0;
    int tmp=0;
    int *k = (int *)malloc(n * sizeof(int));
    int **cost=(int**)malloc((n+1)*sizeof(int*));
    for(i=0;i<=n;i++){
        cost[i]=(int*)malloc((W+1)*sizeof(int));
        k[i] = 0;
    }
    for(i=0;i<=n;i++){
        for(j=0;j<=W;j++){
            if(i==0 || W==0){
                cost[i][j]=0;
            }
            else if(w[i-1]<=W && j>=w[i-1]){
                cost[i][j]=maximum(v[i-1]+cost[i-1][W-(int)w[i-1]],cost[i-1][j]);
                if(cost[i][j]>tmp){
                    tmp = cost[i][j];
                    k[i - 1] = 1;
                }
            }
            else{
                cost[i][j]=cost[i-1][j];
            }
        }
    }
    printf("\nOptimal arrangement:\n( ");
    for (i = 0; i < n;i++){
        printf("%d ", k[i]);
    }
    printf(")\n");
    free(k);
    return cost[n][W];
}


int main() {
    int i = 0, n = 0, W = 0;
    float* v = (float*)malloc(10 * sizeof(float));
    float* w = (float*)malloc(10 * sizeof(float));
    float* vc = (float*)malloc(10 * sizeof(float));
    float* wc = (float*)malloc(10 * sizeof(float));
    fileImport(&n, &W, v, w);
    float* f = (float*)malloc(n * sizeof(float));
    float* objCount = (float*)malloc(n * sizeof(float));
    int choice = 0;
    printf("Number of objects: %d\n", n);
    printf("Weight of knapsack: %d\n", W);
    printf("\nObject Number\tValue\tWeight\n");
    for (int i = 0; i < n; i++) {
        objCount[i] = (i+1);
        vc[i] = v[i];
        wc[i] = w[i];
        printf("%d\t\t%.0f\t%.0f\n", (i + 1), v[i], w[i]);
    }
    while(1){
        printf("\n1. Fractional Knapsack\n2. 0/1 Knapsack\n3. Exit\nEnter your choice:");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                for (i = 0; i < n; i++)
                {
                    f[i] = v[i] / w[i];
                }
                heapsort(objCount, f, v, w, n);
                fractionalknapsack(objCount, v, w, n, W);
                break;
            case 2:
                printf("\nMinimal Cost: %d\n",knapsackdp(W,wc,vc,n));
                break;
            case 3:
                free(v);
                free(w);
                free(vc);
                free(wc);
                exit(0);
            default:
                printf("\nIncorrect Choice! Enter 1,2 or 3\n\n");
        }
    }
    return 0;
}