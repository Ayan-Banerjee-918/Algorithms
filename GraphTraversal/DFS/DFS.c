#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList
{
    int data;
    struct LinkedList* link;
}list;

list* createStack(list* temp, list** topNode) {
    temp = (list*)malloc(sizeof(list));
    temp->link = NULL;
    *topNode = NULL;
    return temp;
}


int isEmptyStack(list* topNode) {
    if (topNode == NULL) {
        return 1;
    }
    return 0;
}

list* pushStack(list* temp, int val, list** topNode) {
    if (isEmptyStack(*topNode)) {
        temp = createStack(temp, topNode);
        temp->data = val;
    }
    else {
        list* newNode = (list*)malloc(sizeof(list));
        newNode->data = val;
        newNode->link = temp;
        temp = newNode;
    }
    *topNode = temp;
    return temp;
}

list* popStack(list* temp, list** topNode, list** vertex) {
    *vertex = (list*)malloc(sizeof(list));
    if (isEmptyStack(topNode)) {
    }
    else {
        *vertex = temp;
        temp = temp->link;
        *topNode = temp;
    }
    return temp;
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

void DFS(int** graph, int startVertex, int* visited, int n) {
    list* stk = NULL;
    list* topNode = NULL;
    list* vertex = NULL;
    int* elementPushed = (int*)calloc(n,sizeof(int));
    int i = 0;
    stk = createStack(stk, &topNode);
    stk = pushStack(stk, startVertex, &topNode);
    elementPushed[startVertex] = 1;
    printf("DFS Traversal:\n");
    while (!isEmptyStack(topNode)) {
        stk = popStack(stk, &topNode, &vertex);
        if (visited[vertex->data] == 0) {
            printf("%c ", (char)(vertex->data+65));
            visited[vertex->data] = 1;
        }
        for (i = n - 1; i >= 0; i--) {
            if (graph[vertex->data][i] == 1 && visited[i] == 0 && elementPushed[i] == 0) {
                stk = pushStack(stk, i, &topNode);
                elementPushed[i] = 1;
            }
        }
    }
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
    int* visited = (int*)calloc(n,sizeof(int));
    DFS(graph, 0, visited, n);
    return 0;
}