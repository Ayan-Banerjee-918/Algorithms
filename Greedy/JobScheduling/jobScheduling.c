#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(int *arr, int n, int i,int *s,int *a)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        swap(&s[i],&s[largest]);
        swap(&a[i],&a[largest]);
        heapify(arr, n, largest,s,a);
    }
  }

  void heapSort(int *arr, int n,int *s,int *a)
  {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i,s,a);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0],&arr[i]);
        swap(&s[0],&s[i]);
        swap(&a[0],&a[i]);
        heapify(arr,i,0,s,a);
    }
}

void job_schedule(int n,int *f,int *s,int *A,int *a)
{
    A[0] = a[0];
    int i,j,k=0;
    j=0;
    for(i=1;i<n;i++)
        if (s[i] >= f[j])
        {
            A[++k] = a[i];
            j = i;

        }
}
int main()
{
    FILE *fptr = fopen("input.txt","r");
    int n,i;
    fscanf(fptr,"%d",&n);
    int *A = (int*)malloc(n*sizeof(int));
    int *a = (int*)malloc(n*sizeof(int));
    int *s = (int*)malloc(n*sizeof(int));
    int *f = (int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {   A[i] = -1;
        a[i] = i;
    }
    for(i=0;i<n;i++)
        fscanf(fptr,"%d",&s[i]);
    for(i=0;i<n;i++)
        fscanf(fptr,"%d",&f[i]);
    fclose(fptr);
    printf("The given activity schedule: \n");
    printf("Job No.\tStart time\tFinish time\n");
    for(i=0;i<10;i++)
        printf("A%d\t%d\t\t%d\n",i+1,s[i],f[i]);
    heapSort(f,n,s,a);
    job_schedule(n,f,s,A,a);
    printf("\nMutually exclusive optimized schedule: ");
    for(i=0;i<n;i++)
    {
        if(A[i] != -1)
            printf("A%d ",A[i]+1);
    }
    return 0;

}
