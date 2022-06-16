                         ___SOURCE_CODE___
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList
{
    int data;
    struct LinkedList* link;
}list;

void createQueue(list** temp) {
    *temp = (list*)malloc(sizeof(list));
    (*temp)->link = NULL;
}
void enQueue(list** temp, int val, list** front, list** rear) {
    list* node = (list*)malloc(sizeof(list));
    node->data = val;
    node->link = NULL;
    if (*front == NULL) {
        *rear = *front = *temp = node;
    }
    else {
        (*rear)->link = node;
        *rear = node;
    }
}
void deQueue(list** temp, list** front) {
    if (front != NULL) {
        *front = (*front)->link;
        *temp = (*temp)->link;
    }
}
void BFSMatrix(int **arr, int val, int* visited, int VertexCnt) {
    int character[] = { 'a','b','c','d','e','f','g','h' };
    int i = 0;
    list* front, * rear;
    list* queue;
    createQueue(&queue);
    front = rear = NULL;
    enQueue(&queue, val, &front, &rear);
    for (i = 0; i < VertexCnt; i++) {
        visited[i] = 0;
    }
    printf("BFS Result:\n");
    while (queue != NULL) {
        printf("%c ", character[queue->data-1]);
        visited[queue->data - 1] = 1;
        for (i = 0; i < VertexCnt; i++) {
            if (arr[queue->data - 1][i] == 1 && !visited[i]) {
                enQueue(&queue, i + 1, &front, &rear);
                visited[i] = 1;
            }
        }
        deQueue(&queue, &front);
    }
}
int** init2DMatrix(int** graph, int n) {
    int i = 0, j = 0;
    graph = (int**)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
    return graph;
}
int** importGraph(int** graph, int* n) {
    int i = 0, j = 0;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening file!\n");
        exit(0);
    }
    fscanf(fptr, "%d", n);
    graph = init2DMatrix(graph, *n);
    for (i = 0; i < *n; i++) {
        for (j = 0; j < *n; j++) {
            fscanf(fptr, "%d", &graph[i][j]);
        }
    }
    fclose(fptr);
    return graph;
}

int main() {
    int n = 0, cost = 0;
    int** graph = NULL;
    graph = importGraph(graph, &n);
    int* visited = (int*)malloc(n * sizeof(int));
    BFSMatrix(graph, 1, visited, n);
    return 0;
}