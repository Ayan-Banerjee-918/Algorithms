/*
Name: Ayan Banerjee
Roll: 13000120019

Question: II) Implement Merge Sort, Quick Sort, and Heap Sort using Divide and Conquer
approach.
*/
#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
int temp=*a;
*a=*b;
*b=temp;
}

//MERGESORT
void merge(int arr[],int p,int q,int r){
int n1=q-p+1;
int n2=r-q;
int i=0,j=0,k=p;
int L[n1],M[n2];
for(i=0;i<n1;i++){
    L[i]=arr[p+i];
}
for(j=0;j<n2;j++){
    M[j]=arr[q+j+1];
}
i=0,j=0;
while(i<n1&&j<n2){
    if(L[i]<=M[j]){
        arr[k]=L[i];
        i++;
    }
    else{
        arr[k]=M[j];
        j++;
    }
    k++;
}
while(i<n1){
    arr[k]=L[i];
    i++;
    k++;
}
while(j<n2){
    arr[k]=M[j];
    j++;
    k++;
}
}

void mergeSort(int arr[],int l,int r){
    if(l<r){
        int m=l+(r-l)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

//QUICKSORT
int partition(int arr[],int low,int high){
    int pivot=arr[high];
    int i=(low-1);
    for(int j=low;j<high;j++){
        if(arr[j]<=pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return i+1;
}

void quickSort(int arr[],int low,int high){
    if(low<high){
        int part=partition(arr,low,high);
        quickSort(arr,low,part-1);
        quickSort(arr,part+1,high);
    }
}

//HEAPSORT
void heapify(int arr[],int n,int i){
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n&&arr[left]>arr[largest]){
        largest=left;
    }
    if(right<n&&arr[right]>arr[largest]){
        largest=right;
    }
    if(largest!=i){
        swap(&arr[i],&arr[largest]);
        heapify(arr,n,largest);
    }
}

void heapSort(int arr[],int n){
    for(int i=n/2-1;i>=0;i--){
        heapify(arr,n,i);
    }
    for(int i=n-1;i>=0;i--){
        swap(&arr[0],&arr[i]);
        heapify(arr,i,0);
    }
}

//DISPLAYING ARRAY
void printArray(int arr[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[9999], i=0;
    FILE *fptr=fopen("SortingInput.txt","r");
    while((fscanf(fptr,"%d",&arr[i]))!=EOF){
        i++;
    }
    fclose(fptr);
    int n=i;
    printf("Given Array:\n");
    printArray(arr,n);
    int result=0,choice=0;

flag:
    printf("1.MergeSort\n2.QuickSort\n3.HeapSort\n4.Exit\n");
    printf("Enter choice:");
    scanf("%d",&choice);
    if(choice==4){
        exit(0);
    }
    result=0;
    for(i=0;i<n-1;i++){
        if(arr[i]>arr[i+1]){
            result=999;
            break;
        }
    }
    if(result==0){
        printf("\nArray already sorted\n");
        goto flag;
    }
    else{
    switch(choice){
    case 1:
        mergeSort(arr,0,n-1);
        printArray(arr,n);
        goto flag;
    case 2:
        quickSort(arr,0,n-1);
        printArray(arr,n);
        goto flag;
    case 3:
        heapSort(arr,n);
        printArray(arr,n);
        goto flag;
    case 4:
        exit(0);
    default:
        printf("Incorrect Option Entered!Enter between 1 and 4");
        goto flag;
    }
    }
}