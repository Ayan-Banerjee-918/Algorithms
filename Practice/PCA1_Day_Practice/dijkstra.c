void dijkstra(int** weight,int n,int start){
    int *distance = (int *)malloc(n * sizeof(int));
    int *pred = (int *)malloc(n * sizeof(int));
    int *A = (int *)malloc(n * sizeof(int));
    int *visited = (int *)malloc(n * sizeof(int));
    int i = 0, j = 0, k = 0, aCnt = 0, min = 0, minVal = 0, cpy=start, tmp = 0;
    for (i = 0; i < n;i++){
        if(i==start){
            distance[i] = 0;
        }
        else{
            distance[i] = 99999;
        }
        A[i] = -1;
        visited[i] = -1;
        pred[i] = start;
    }
    A[k++] = start;
    visited[start] = 1;
    aCnt++;
    while(aCnt!=n){
        minVal = min = 99999;
        for (i = 0; i < n;i++){
            if(i==cpy || i==start){
                continue;
            }
            if(weight[start][i]!=99999){
                tmp = distance[start] + weight[start][i];
                if(tmp<distance[i]){
                    distance[i] = tmp;
                    pred[i] = start;
                }
                if(tmp<minVal){
                    minVal = tmp;
                    min = i;
                }
            }
        }
        A[k++] = min;
        visited[min] = 1;
        aCnt++;
        start = min;
    }
}