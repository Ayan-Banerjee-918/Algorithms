/*
Name: Ayan Banerjee
Roll: 13000120019

I) Implement Binary Search using the Divide and Conquer
approach.
*/

#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[],int no,int low,int high){
    if(low<=high){
        int m = (low + high) / 2;
        if(arr[m]==no)
            return m;
        if(arr[m]>no)
            return binarySearch(arr,no,low,m-1);
        else
            return binarySearch(arr,no,m+1,high);
    }
    return -1;
}

void printArray(int arr[],int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}


int main(){
    int n=0,i=0,num=0,res=0;
    int choice=0;
    int arr[9999];
    FILE *fptr=fopen("binarySearchInput.txt","r");
    while((fscanf(fptr,"%d",&arr[i]))!=EOF){
        i++;
    }
    fclose(fptr);
    n=i;
    int result=0;
    for(i=0;i<n-1;i++){
        if(arr[i]>arr[i+1]){
            result=999;
            break;
        }
    }
    if(result!=0){
        printf("Given Array:");
        printArray(arr,n);
        printf("\nArray not sorted!Exiting\n");
        exit(0);
    }
    else{
    while(1){
        printf("Given Array:");
        printArray(arr,n);
        printf("Enter element to be searched in array:");
        scanf("%d",&num);
        res=binarySearch(arr,num,0,n-1);
        if(res==-1){
            printf("Element %d not found.\n",num);
        }
        else{
            printf("Element %d found at position %d\n",num,res+1);
        }
    flag:
        printf("1.Continue\n2.Exit\n");
        scanf("%d",&choice);
        if(choice==1){
            continue;
        }
        else if(choice==2){
            break;
        }
        else{
            printf("Incorrect Option!Please Enter 1 or 2.\n");
            goto flag;
        }
    }
    }
}
