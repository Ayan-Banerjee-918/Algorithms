#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* link;
}AdjListnode;

typedef struct adjList {
    AdjListnode* head;
}AdjList;

typedef struct adjacencyList {
    int vertexCount;
    AdjList* VerticesList;
}graph;

typedef struct LinkedList
{
    int data;
    struct LinkedList* link;
}list;

//Functions for Adjacency Matrix

//Matrix Implementation
void fillEdgeMatrix(int***, int, int);
void displayAdjacencyMatrix(int**, int);

//Traversal
//  i>DFS
void DFSMatrix(int**, int, int*, int);
// ii>BFS
void BFSMatrix(int**, int, int*, int);

//Functions for Adjacency List

//List Implementation
AdjListnode* createNode(int);
graph* initGraph(int);
int checkVertex(AdjList, int);
void addListEdge(graph*, int, int);
void displayAdjacencyList(graph*);

//Traversal
//  i>DFS
void DFSList(graph*, AdjListnode*, int, int*, int);
// ii>BFS
void BFSList(graph*, AdjListnode*, int, int*, int);

//Queue Functions
void createQueue(list **);
void enQueue(list **, int, list **, list **);
void deQueue(list **, list **);

void createQueue(list** temp) {
    *temp = (list*)malloc(sizeof(list));
    (*temp)->link = NULL;
}

void enQueue(list** temp, int val,list** front,list** rear) {
    list* node = (list*)malloc(sizeof(list));
    node->data = val;
    node->link = NULL;
    if (*front==NULL) {
        *rear = *front = *temp = node;
    }
    (*rear)->link = node;
    *rear = node;
}

void deQueue(list** temp,list** front) {
    if (front!=NULL) {
        *front = (*front)->link;
        *temp = (*temp)->link;
    }
}

AdjListnode* createNode(int value) {
    AdjListnode* tmpNode = (AdjListnode*)malloc(sizeof(AdjListnode));
    if (!tmpNode) {
        printf("Memory Allocation Failed!");
        exit(0);
    }
    tmpNode->data = value;
    tmpNode->link = NULL;
    return tmpNode;
}

graph* initGraph(int vertexCount) {
    int i;
    graph* tmp = (graph*)malloc(sizeof(graph));
    if (!tmp) {
        printf("Memory Allocation Failed!");
        exit(0);
    }
    tmp->vertexCount = vertexCount;
    tmp->VerticesList = (AdjList*)malloc(vertexCount * sizeof(AdjList));
    for (i = 0; i < vertexCount; i++) {
        tmp->VerticesList[i].head = NULL;
    }
    return tmp;
}

int checkVertex(AdjList node,int val) {
    while (node.head != NULL) {
        if (node.head->data == val) {
            return 1;
        }
        node.head = node.head->link;
    }
    return 0;
}

void addListEdge(graph* tmp, int source, int destination) {
    if (!checkVertex(tmp->VerticesList[source - 1], destination)) {
        AdjListnode* tmpNode = createNode(destination);
        tmpNode->link = tmp->VerticesList[source - 1].head;
        tmp->VerticesList[source - 1].head = tmpNode;

        if (!checkVertex(tmp->VerticesList[destination - 1], source)) {
            tmpNode = createNode(source);
            tmpNode->link = tmp->VerticesList[destination - 1].head;
            tmp->VerticesList[destination - 1].head = tmpNode;
        }

        system("cls");
        printf("Edge Inserted.\n");
    }
    else {
        system("cls");
        printf("Edge Already Present.\n");
    }
}

void fillEdgeMatrix(int*** arr, int source, int destination) {
    (*arr)[source][destination] = (*arr)[destination][source] = 1;
}

void DFSMatrix(int**arr, int val, int* visited,int VertexCnt) {
    int i = 0;
    printf("%d ", val+1);
    visited[val] = 1;
    for (i = 0; i < VertexCnt; i++) {
        if (arr[val][i] == 1 && (!visited[i])) {
            DFSMatrix(arr, i, visited, VertexCnt);
        }
    }
}

void DFSList(graph* list,AdjListnode* tmp, int val,int* visited,int VertexCnt) {
    if (tmp == NULL) {
        return;
    }
    int i = 0, index=0;
    printf("%d ", (val+1));
    visited[val] = 1;
    for (i = 0; tmp != NULL && i < VertexCnt; i++) {
        if (!visited[tmp->data-1]) {
            index = tmp->data-1;
            DFSList(list, list->VerticesList[index].head, index, visited, VertexCnt);
        }
        tmp = tmp->link;
    }
}

void BFSMatrix(int**arr,int val,int* visited,int VertexCnt) {
    int i = 0;
    list* front, * rear;
    list* queue;
    createQueue(&queue);
    front = rear = NULL;
    enQueue(&queue, val, &front, &rear);
    while (queue != NULL) {
        printf("%d ", queue->data);
        visited[queue->data - 1] = 1;
        for (i = 0; i < VertexCnt; i++) {
            if (arr[queue->data - 1][i] == 1 && !visited[i]) {
                enQueue(&queue, i+1, &front, &rear);
                visited[i] = 1;
            }
        }
        deQueue(&queue, &front);
    }
}

void BFSList(graph* BFSgraph,AdjListnode* tmp, int val,int* visited,int VertexCnt){
    int i = 0,flag = 0;
    list* front, * rear;
    list* queue;
    createQueue(&queue);
    front = rear = NULL;
    enQueue(&queue, val, &front, &rear);
    while (queue != NULL) {
        printf("%d ", queue->data);
        visited[queue->data - 1] = 1;
        for (i = 0; tmp != NULL && i < VertexCnt; i++) {
            if (tmp != NULL && !visited[tmp->data-1]) {
                enQueue(&queue, tmp->data, &front, &rear);
                visited[tmp->data - 1] = 1;
            }
            tmp = tmp->link;
        }
        deQueue(&queue, &front);
        if (queue != NULL) {
            tmp = BFSgraph->VerticesList[queue->data - 1].head;
        }
    }
}

void displayAdjacencyMatrix(int** arr, int vertexCount) {
    int i = 0, j = 0;
    for (; i < vertexCount; i++) {
        for (j = 0; j < vertexCount; j++) {
            if (arr[i][j] == -1) {
                printf("%c\t", 'x');
            }
            else {
                printf("%d\t", arr[i][j]);
            }
        }
        printf("\n");
    }
}

void displayAdjacencyList(graph* tmp)
{
    int vertex;
    for (vertex = 0; vertex < tmp->vertexCount; ++vertex)
    {
        AdjListnode* copy = tmp->VerticesList[vertex].head;
        printf("\n Vertex %d ", (vertex+1));
        while (copy)
        {
            printf("-> %d",copy->data );
            copy = copy->link;
        }
        printf("\n");
    }
}

void main() {
    int** adjacencyMatrix;
    int* visited;
    int vertexCount = -1, i = 0, j = 0, source = -1, destination = -1, flag = 0, choice = 0, choiceM = 0, startingNode = 0;
    printf("Enter number of vertices of graph: ");
    scanf("%d", &vertexCount);
    adjacencyMatrix = (int**)malloc(vertexCount * sizeof(int*));
    graph* adjgraphlist = initGraph(vertexCount);
    if (!adjacencyMatrix) {
        printf("Memory Allocation Failed!");
        exit(0);
    }
    for (; i < vertexCount; i++) {
        adjacencyMatrix[i] = (int*)malloc(vertexCount * sizeof(int));
        if (!adjacencyMatrix[i]) {
            printf("Memory Allocation Failed!");
            exit(0);
        }
    }
    for (i = 0; i < vertexCount; i++) {
        for (j = 0; j < vertexCount; j++) {
            adjacencyMatrix[i][j] = -1;
        }
    }
    //printf("\nNumber of Vertices:%d\n", vertexCount);
startMain:
    system("cls");
    printf("Choose how to represent Graph:\n");
    printf("1. Adjacency Matrix\n");
    printf("2. Adjacency List\n");
    printf("3. Exit\n");
    printf("Enter your choice:");
    scanf("%d", &choiceM);
    system("cls");
    switch (choiceM) {
    case 1:
    start:
        printf("\n__GRAPH__\n");
        printf("1. Insert Edge\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Traversal\n");
        printf("4. Exit\n");
        printf("5. Back\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            if (flag == vertexCount * vertexCount) {
                system("cls");
                goto start;
            }
            printf("\nEnter source and destination:");
            scanf("%d", &source);
            scanf("%d", &destination);
            if ((source<1 || source>vertexCount) || (destination<1 || destination>vertexCount)) {
                system("cls");
                printf("Source or destination cannot be greater than Vertex Count or less than 1\n");
                goto start;
            }
            if (adjacencyMatrix[source - 1][destination - 1] == 1) {
                system("cls");
                printf("Edge Already Present.\n");
                goto start;
            }
            flag++;
            fillEdgeMatrix(&adjacencyMatrix, source - 1, destination - 1);
            system("cls");
            printf("Edge Inserted.\n");
            goto start;
        case 2:
            system("cls");
            printf("ADJACENCY MATRIX\n");
            displayAdjacencyMatrix(adjacencyMatrix, vertexCount);
            printf("\n");
            goto start;
        case 3:
            system("cls");
            printf("__Traversal__\n");
            printf("1. DFS\n");
            printf("2. BFS\n");
            printf("Enter your choice:");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                system("cls");
                printf("Enter starting node:");
                scanf("%d", &startingNode);
                if (startingNode<1 || startingNode>vertexCount) {
                    system("cls");
                    printf("Starting Node doesnt exist in graph\n");
                }
                else {
                    visited = (int*)malloc(vertexCount * sizeof(int));
                    for (i = 0; i < vertexCount; i++) {
                        visited[i] = 0;
                    }
                    system("cls");
                    printf("DFS Traversal:\n");
                    DFSMatrix(adjacencyMatrix, startingNode-1, visited, vertexCount);
                    printf("\n");
                }
                goto start;
            case 2:
                system("cls");
                printf("Enter starting node:");
                scanf("%d", &startingNode);
                if (startingNode<1 || startingNode>vertexCount) {
                    system("cls");
                    printf("Starting Node doesnt exist in graph\n");
                }
                else {
                    visited = (int*)malloc(vertexCount * sizeof(int));
                    for (i = 0; i < vertexCount; i++) {
                        visited[i] = 0;
                    }
                    system("cls");
                    printf("BFS Traversal:\n");
                    BFSMatrix(adjacencyMatrix, startingNode, visited, vertexCount);
                    printf("\n");
                }
                goto start;
            }
        case 4:
            exit(0);
        case 5:
            goto startMain;
        default:
            system("cls");
            printf("Incorrect choice entered.Enter between 1 and 5.\n");
            goto start;
        }
    case 2:
    startGraph:
        printf("\n__GRAPH__\n");
        printf("1. Insert Edge\n");
        printf("2. Display Adjacency List\n");
        printf("3. Traversal\n");
        printf("4. Exit\n");
        printf("5. Back\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            if (flag == vertexCount * vertexCount) {
                system("cls");
                goto startGraph;
            }
            printf("\nEnter source and destination:");
            scanf("%d", &source);
            scanf("%d", &destination);
            if ((source<1 || source>vertexCount) || (destination<1 || destination>vertexCount)) {
                system("cls");
                printf("Source or destination cannot be greater than Vertex Count or less than 1\n");
                goto startGraph;
            }
            flag++;
            addListEdge(adjgraphlist, source, destination);
            goto startGraph;
        case 2:
            system("cls");
            printf("ADJACENCY LIST\n");
            displayAdjacencyList(adjgraphlist);
            printf("\n");
            goto startGraph;
        case 3:
            system("cls");
            printf("__Traversal__\n");
            printf("1. DFS\n");
            printf("2. BFS\n");
            printf("Enter your choice:");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                system("cls");
                printf("Enter starting node:");
                scanf("%d", &startingNode);
                if (startingNode<1 || startingNode>vertexCount) {
                    system("cls");
                    printf("Starting Node doesnt exist in graph\n");
                }
                else {
                    visited = (int*)malloc(vertexCount * sizeof(int));
                    for (i = 0; i < vertexCount; i++) {
                        visited[i] = 0;
                    }
                    system("cls");
                    printf("DFS Traversal:\n");
                    DFSList(adjgraphlist,adjgraphlist->VerticesList[startingNode-1].head, startingNode - 1, visited, vertexCount);
                    printf("\n");
                }
                goto startGraph;
            case 2:
                system("cls");
                printf("Enter starting node:");
                scanf("%d", &startingNode);
                if (startingNode<1 || startingNode>vertexCount) {
                    system("cls");
                    printf("Starting Node doesnt exist in graph\n");
                }
                else {
                    visited = (int*)malloc(vertexCount * sizeof(int));
                    for (i = 0; i < vertexCount; i++) {
                        visited[i] = 0;
                    }
                    system("cls");
                    printf("BFS Traversal:\n");
                    BFSList(adjgraphlist,adjgraphlist->VerticesList[startingNode-1].head, startingNode, visited, vertexCount);
                    printf("\n");
                }
                goto startGraph;
            }
        case 4:
            exit(0);
        case 5:
            goto startMain;
        default:
            system("cls");
            printf("Incorrect choice entered.Enter between 1 and 5.\n");
            goto startGraph;
        }
    case 3:
        exit(0);
    default:
        printf("Incorrect choice entered.Enter between 1 and 3.\n");
    }
}