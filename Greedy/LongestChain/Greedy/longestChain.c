#include <stdio.h>
#include <stdlib.h>

void swap(int **A,int **B){
    int *C = *A;
    *A = *B;
    *B = C;
}

void heapify(int **arr,int n,int i){
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n && arr[left][0]>arr[largest][0]){
        largest=left;
    }
    if(right<n&&arr[right][0]>arr[largest][0]){
        largest=right;
    }
    if(largest!=i){
        swap(&arr[i],&arr[largest]);
        heapify(arr,n,largest);
    }
}


void heapSort(int **arr,int N){
    for (int i = N / 2 - 1; i >= 0;i--){
        heapify(arr, N, i);
    }
    for(int i=N-1;i>=0;i--){
        swap(&arr[0],&arr[i]);
        heapify(arr,i,0);
    }
}

int** fileImport(int** arr,int* N){
    int i = 0, j = 0;
    FILE *fptr = fopen("input.txt", "r");
    if(fptr==NULL){
        printf("Error in opening File!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    arr = (int **)malloc((*N) * sizeof(int *));
    for (i = 0; i < *N;i++){
        arr[i] = (int *)calloc(2, sizeof(int));
    }
    for (i = 0; i < *N;i++){
        for (j = 0; j < 2;j++){
            fscanf(fptr, "%d", &arr[i][j]);
        }
    }
    fclose(fptr);
    return arr;
}

void printChain(int **arr,int N){
    int i = 0, j = 0;
    for (i = 0; i < N; i++) {
        printf("(");
        for (j = 0; j < 2; j++) {
            if(j==0)
                printf("%d,", arr[i][j]);
            else
                printf("%d", arr[i][j]);
        }
        if(i==N-1){
            printf(") }\n");
        }
        else{
            printf(") , ");
        }
    }
}

int calcLongestChain(int **arr,int N){
    int i = 0,j = 0, cnt = 1;
    int **A = NULL;
    A = (int **)malloc((N) * sizeof(int *));
    for (i = 0; i < N;i++){
        A[i] = (int *)calloc(2, sizeof(int));
    }
    A[cnt - 1] = arr[0];
    for (i = 1; i < N;i++){
        if(arr[i][0]>arr[j][1]){
            j = i;
            A[cnt] = arr[i];
            cnt++;
        }
    }
    printf("The Longest Chain is : \n{ ");
    printChain(A, cnt);
    return cnt;
}

void main(){
    int **arr = NULL;
    int N = 0, i = 0, j = 0;
    arr = fileImport(arr, &N);
    printf("The input chain:\n");
    printChain(arr, N);
    heapSort(arr,N);
    printf("The sorted chain:\n");
    printChain(arr, N);
    printf("Longest Chain Length: %d\n", calcLongestChain(arr, N));
}