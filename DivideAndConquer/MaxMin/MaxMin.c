
#include <stdio.h>
#include <stdlib.h>

typedef struct res{
    int minimum;
    int maximum;
} result;

result findMinMax(int* arr,int beginning,int end){
    result temp,templeft,tempright;
    int mid = 0;
    if(beginning==end){
        temp.maximum = arr[beginning];
        temp.minimum = arr[beginning];
        return temp;
    }
    // else if(end==beginning+1){
    //     if(arr[beginning]<arr[end]){
    //         temp.minimum = arr[beginning];
    //         temp.maximum = arr[end];
    //     }
    //     else if (arr[beginning]>arr[end]){
    //         temp.maximum = arr[beginning];
    //         temp.minimum = arr[end];
    //     }
    //     return temp;
    // }
    mid = (beginning + end) / 2;
    templeft = findMinMax(arr, beginning, mid);
    tempright = findMinMax(arr, mid+1, end);
    if(templeft.minimum<tempright.minimum){
        temp.minimum = templeft.minimum;
    }
    else{
        temp.minimum = tempright.minimum;
    }
    if(templeft.maximum>tempright.maximum){
        temp.maximum = templeft.maximum;
    }
    else{
        temp.maximum = tempright.maximum;
    }
    return temp;
}   

void printArray(int *arr,int n){
    int i = 0;
    printf("\nArray:\n");
    for (i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
}

int fileImport(int *arr){
    int i = 0;
    FILE *fptr;
    if ((fptr = fopen("MaxMinInput.txt", "r")) == NULL){
       printf("Error! opening file");
       exit(0);
    }
    while((fscanf(fptr,"%d",&arr[i]))!=EOF){
        i++;
    }
    fclose(fptr);
    return i;
}

int main(){
    int arr[9999],n=0,choice=0;
    result res;
    n=fileImport(&arr[0]);
flag:
    printArray(arr,n);
    printf("\n\n1. Find Maximum Element\n");
    printf("2. Find Minimum Element\n");
    printf("3. Update Array\n");
    printf("4. Exit\n");
    printf("Enter your choice:");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            res = findMinMax(arr, 0, n - 1);
            printf("\nMAXIMUM ELEMENT : %d\n", res.maximum);
            goto flag;
        case 2:
            res = findMinMax(arr, 0, n - 1);
            printf("\nMINIMUM ELEMENT : %d\n", res.minimum);
            goto flag;
        case 3:
            n=fileImport(&arr[0]);
            goto flag;
        case 4:
            exit(0);
        default:
            printf("\nInvalid Option! Enter between 1 and 4\n");
            goto flag;
    }
    return 0;
}