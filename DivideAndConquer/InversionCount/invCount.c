#include <stdio.h>
#include <stdlib.h>

int merge(int* arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int i = 0, j = 0, k = low;
    int inversionCount = 0;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* M = (int*)malloc(n2 * sizeof(int));
    for (i = 0; i < n1; i++) {
        L[i] = arr[low + i];
    }
    for (j = 0; j < n2; j++) {
        M[j] = arr[mid + 1 + j];   
    }
    i = 0, j = 0;
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = M[j++];
            inversionCount += (mid - i + 1);
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = M[j++];
    }
    return inversionCount;
}

int mergeSort(int* arr, int low, int high) {
    int inversionCount = 0;
    if (low < high) {
        int mid = (low + high) / 2;
        inversionCount += mergeSort(arr, low, mid);
        inversionCount += mergeSort(arr, mid + 1, high);
        inversionCount += merge(arr, low, mid, high);
    }
    return inversionCount;
}


int fileImport(int* arr) {
    int i = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error inputting file!");
        return 0;
    }
    while (fscanf(fptr, "%d", &arr[i]) != EOF) {
        i++;
    }
    fclose(fptr);
    return i - 1;
}

void main(){
    int arr[9999];
    int n = fileImport(arr);
    printf("Total no of inversion Cnts: %d\n",mergeSort(arr,0,n));
}