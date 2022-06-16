#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
  int u;
  int v;
  int wt;
} edge;

typedef struct edgeGraph {
  edge *data;
  int n;
} edgeGraph;

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

edgeGraph* initEdgeGraph(edgeGraph* graph,int n){
  graph = (edgeGraph *)malloc(sizeof(graph));
  graph->n = n;
  graph->data = (edge *)malloc(100 * sizeof(edge));
  return graph;
}

// Applying Krushkal Algo
void kruskalAlgo(int **graph,edgeGraph edgeList) {
  int belongs[100], i, j, cno1, cno2;
  edgeList.n = 0;

  for (i = 1; i < n; i++){
    for (j = 0; j < i; j++) {
      if (graph[i][j] != 0) {
        edgeList.data[edgeList.n].u = i;
        edgeList.data[edgeList.n].v = j;
        edgeList.data[edgeList.n].w = graph[i][j];
        edgeList.n++;
      }
    }
  }
  sort();

  for (i = 0; i < n; i++)
    belongs[i] = i;

  spanlist.n = 0;

  for (i = 0; i < elist.n; i++) {
    cno1 = find(belongs, elist.data[i].u);
    cno2 = find(belongs, elist.data[i].v);

    if (cno1 != cno2) {
      spanlist.data[spanlist.n] = elist.data[i];
      spanlist.n = spanlist.n + 1;
      applyUnion(belongs, cno1, cno2);
    }
  }
}

int find(int belongs[], int vertexno) {
  return (belongs[vertexno]);
}

void applyUnion(int belongs[], int c1, int c2) {
  int i;

  for (i = 0; i < n; i++)
    if (belongs[i] == c2)
      belongs[i] = c1;
}

// Sorting algo
void sort() {
  int i, j;
  edge temp;

  for (i = 1; i < elist.n; i++)
    for (j = 0; j < elist.n - 1; j++)
      if (elist.data[j].w > elist.data[j + 1].w) {
        temp = elist.data[j];
        elist.data[j] = elist.data[j + 1];
        elist.data[j + 1] = temp;
      }
}

// Printing the result
void print() {
  int i, cost = 0;

  for (i = 0; i < spanlist.n; i++) {
    printf("\n%d - %d : %d", spanlist.data[i].u, spanlist.data[i].v, spanlist.data[i].w);
    cost = cost + spanlist.data[i].w;
  }

  printf("\nSpanning tree cost: %d\n", cost);
}

int main() {
  int i, j, total_cost;
  edgeGraph edgeList;
  edgeGraph spanlist;
  int n = 0, cost = 0;
  int** graph = NULL;
  graph = importGraph(graph, &n);
  edgeList = initEdgeGraph(edgeList, n);
  spanList = initEdgeGraph(spanList, n);
  kruskalAlgo(graph,edgeList,spanList);
  print();
}