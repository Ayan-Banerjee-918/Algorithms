#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void merge(int* arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int i = 0, j = 0, k = low;
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
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = M[j++];
    }
}

void mergeSort(int* arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(&arr[++i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int partitionlow(int* arr, int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;
    while (i < j) {
        while (arr[i] <= pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int part = partition(arr, low, high);
        quickSort(arr, low, part - 1);
        quickSort(arr, part, high);
    }
}

void quickSortLow(int* arr, int low, int high) {
    if (low < high) {
        int part = partitionlow(arr, low, high);
        quickSortLow(arr, low, part - 1);
        quickSortLow(arr, part + 1, high);
    }
}

void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left<n && arr[left]>arr[largest]) {
        largest = left;
    }
    if (right<n && arr[right]>arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int fileImport(int* arr) {
    int i = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error inputting file!");
        return 0;
    }
    while (fscanf(fptr, "%d", &arr[i++]) != EOF) {
    }
    fclose(fptr);
    return i - 1;
}

void main() {
    int arr[9999];
    int n = fileImport(arr);
    printf("Given Array:\n");
    printArray(arr, n);
    printf("Sorted Array:\n");
    //quickSort(arr, 0, n-1);
    quickSortLow(arr, 0, n - 1);
    //mergeSort(arr, 0, n-1);
    //heapSort(arr, n);
    printArray(arr, n);
}