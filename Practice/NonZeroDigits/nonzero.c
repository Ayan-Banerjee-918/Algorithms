#include <stdio.h>
#include <stdlib.h>

int calcCount(int n,int k)
{
    int i = 0,count = 0,num=0,total = 0;

    for( i = 1 ; i < n+1 ; i++ )
    {
        num = i;
        count = 0;
        while(num != 0)
        {
            if ( num % 10 != 0)
                count++;
            num = num / 10;
        }
        if(count == k)
        {
            printf("%d ",i);
            total++;
        }
    }
    return total;
}

void fileImport(int* N, int* K) {
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", N);
    fscanf(fptr, "%d", K);
    fclose(fptr);
}

void main() {
    int N = 0, K = 0;
    fileImport(&N, &K);
    printf("N = %d\nK = %d\n", N, K);
    printf("Numbers:\n");
    printf("\nNumber of integers between 1 and N that contain exactly K non zero integers : %d\n", calcCount(N, K));
}