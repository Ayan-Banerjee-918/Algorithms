#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void merge(int *arr,int low,int mid,int high){
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int i = 0, j = 0, k = low;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *M = (int *)malloc(n2 * sizeof(int));
    for (i = 0; i < n1;i++){
        L[i] = arr[low+i];
    }
    for (j = 0; j < n2;j++){
        M[j] = arr[mid+1+j];
    }
    i = 0, j = 0;
    while(i<n1 && j<n2){
        if(L[i]<=M[j]){
            arr[k++] = L[i++];
        }
        else{
            arr[k++] = M[j++];
        }
    }
    while(i<n1){
        arr[k++] = L[i++];
    }
    while(j<n2){
        arr[k++] = M[j++];
    }
}

void mergeSort(int* arr,int low,int high){
    if(low<high){
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int partition(int *arr,int low,int high){
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high;j++){
        if(arr[j]<=pivot){
            swap(&arr[++i],&arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int *arr,int low,int high){
    if(low<high){
        int part = partition(arr, low, high);
        quickSort(arr, low, part - 1);
        quickSort(arr, part, high);
    }
}

void heapify(int *arr,int n,int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left<n && arr[largest]<arr[left]){
        largest = left;
    }
    if(right<n && arr[largest]<arr[right]){
        largest = right;
    }
    if(largest!=i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int *arr,int n){
    for (int i = n / 2 - 1; i--;i>=0){
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0;i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}