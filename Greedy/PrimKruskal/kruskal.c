#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    int u;
    int v;
    int wt;
} Edge;

typedef struct edgelist {
    Edge* data;
    int n;
} edgeList;

void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
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

void heapify(Edge* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left<n && arr[left].wt>arr[largest].wt) {
        largest = left;
    }
    if (right<n && arr[right].wt>arr[largest].wt) {
        largest = right;
    }
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(Edge* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

edgeList createList(int** graph, edgeList list, int n) {
    list.n = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != 99999 && graph[i][j] != 0) {
                list.data[list.n].u = i;
                list.data[list.n].v = j;
                list.data[list.n].wt = graph[i][j];
                list.n++;
            }
        }
    }
    return list;
}

int find(int* parent, int i) {
    return parent[i];
}

void unionMST(int* parent, int x, int y, int n) {
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (parent[i] == y) {
            parent[i] = x;
        }
    }
}

void kruskal(edgeList list, int n) {
    int i = 0, j = 0, u = 0, v = 0, cost = 0;
    int* parent = (int*)malloc(n * sizeof(int));
    edgeList MST;
    MST.n = 0;
    MST.data = (Edge*)malloc(100 * sizeof(Edge));
    heapSort(list.data, list.n);
    for (i = 0; i < n; i++) {
        parent[i] = i;
    }
    for (i = 0; i < list.n; i++) {
        u = find(parent, list.data[i].u);
        v = find(parent, list.data[i].v);
        if (u != v) {
            MST.data[MST.n] = list.data[i];
            MST.n++;
            unionMST(parent, u, v, n);
        }
    }
    printf("Minimum Spanning Tree:\n\n");
    for (i = 0; i < MST.n; i++) {
        printf("%d - %d : %d\n", MST.data[i].u + 1, MST.data[i].v + 1, MST.data[i].wt);
        cost += MST.data[i].wt;
    }
    printf("\nMST cost: %d\n", cost);
}

int main() {
    int n = 0, cost = 0;
    int** graph = NULL;
    graph = importGraph(graph, &n);
    edgeList list;
    list.data = (Edge*)malloc(100*sizeof(Edge));
    list = createList(graph, list, n);
    kruskal(list, n);
    return 0;
}