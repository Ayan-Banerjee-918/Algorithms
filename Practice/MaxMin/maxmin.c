#include <stdio.h>
#include <stdlib.h>

typedef struct result{
    int maximum;
    int minimum;
} res;

res findMaxMin(int *arr,int low,int high,res temp){
    res tmpleft, tmpright;
    int mid = 0;
    if(low==high){
        temp.maximum = temp.minimum = arr[low];
        return temp;
    }
    // else if(high==low+1){
    //     if(arr[low]>arr[high]){
    //         temp.maximum = arr[low];
    //         temp.minimum = arr[high];
    //     }
    //     else{
    //         temp.maximum = arr[high];
    //         temp.minimum = arr[low];
    //     }
    //     return temp;
    // }
    mid = (low + high) / 2;
    tmpleft = findMaxMin(arr, low, mid, temp);
    tmpright = findMaxMin(arr, mid + 1, high, temp);
    if(tmpleft.minimum<tmpright.minimum){
        temp.minimum = tmpleft.minimum;
    }
    else{
        temp.minimum = tmpright.minimum;
    }
    if(tmpleft.maximum>tmpright.maximum){
        temp.maximum = tmpleft.maximum;
    }
    else{
        temp.maximum = tmpright.maximum;
    }
    return temp;
}

void printArray(int *arr,int n){
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int fileImport(int *arr){
    int i = 0;
    FILE *fptr = fopen("input.txt", "r");
    if(fptr==NULL){
        printf("Error in reading file\n");
        return 0;
    }
    while(fscanf(fptr,"%d",&arr[i])!=EOF){
        i++;
    }
    fclose(fptr);
    return i;
}

void main(){
    int arr[9999],n=0,choice=0;
    res result;
    n=fileImport(arr);
    result = findMaxMin(arr, 0, n-1, result);
    printf("Given Array:\n");
    printArray(arr,n);
    printf("Minimum: %d\n", result.minimum);
    printf("Maximum: %d\n", result.maximum);
}