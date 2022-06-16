#include <stdio.h>
#include <stdlib.h>

typedef struct res{
    int minimum;
    int maximum;
} result;

result findMaxMin(int *arr,int low,int high,result res1){
    if(low==high){
        res1.maximum = res1.minimum = arr[low];
        return res;
    }
    int mid = (low + high) / 2;
    result resleft = findMaxMin(arr,low,mid,res1);
    result resright = findMaxMin(arr, mid + 1, high, res1);
    if(resleft.maximum>resright.maximum){
        res1.maximum = resleft.maximum;
    }
    else{
        res1.maximum = resright.maximum;
    }
    if(resleft.minimum<resright.minimum){
        res1.minimum = resleft.minimum;
    }
    else{
        res1.maximum = resright.minimum;
    }
    return res;
}