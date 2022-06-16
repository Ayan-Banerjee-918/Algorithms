#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    Up,
    Down,
    Right,
    Left
} Direction;

void swap(int* a, int* b) {
    int tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int* genPos(int** graph) {
    int i = 0, j = 0, k = 1;
    int cnt = 1;
    int* pos = (int*)malloc(17 * sizeof(int));
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (graph[i][j] == -1) {
                pos[16] = cnt++;
            }
            else {
                pos[graph[i][j]] = cnt++;
            }
        }
    }
    return pos;
}

int calcNotGoalState(int* pos) {
    int i = 0, j = 0, k = 1;
    int cnt = 0;
    for (i = 1; i < 16; i++) {
        if (pos[i] != i) {
            cnt++;
        }
    }
    return cnt;
}

int feasible(int** graph, int* pos) {
    int shaded[] = { 2, 4, 5, 7, 10, 12, 13, 15 };
    int x = 0, i = 0, j = 0, k = 1, cnt = 1, sum = 0;
    for (i = 1; i <= 16; i++) {
        for (j = 1; j < i; j++) {
            if (pos[j] > pos[i]) {
                cnt++;
            }
        }
        sum += cnt;
        cnt = 1;
    }
    for (i = 0; i < 8; i++) {
        if (pos[16] == shaded[i]) {
            x = 1;
            break;
        }
    }
    sum += x;
    if (sum % 2 == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int* resetPos(int* copy, int* pos) {
    int i = 0;
    for (i = 1; i <= 16; i++) {
        copy[i] = pos[i];
    }
    return copy;
}

int retVal(int* pos, int position) {
    int i = 0;
    int cnt = 0;
    for (i = 1; i <= 16; i++) {
        if (pos[i] == position) {
            return i;
        }
    }
}

void printPuzzle(int** graph, int* pos, int flag) {
    int i = 0, j = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (flag == 1) {
                graph[i][j] = retVal(pos, (i * 4) + (j + 1));
            }
            if (graph[i][j] == 16 || graph[i][j]==-1) {
                printf("ES\t");
            }
            else {
                printf("%d\t", graph[i][j]);
            }
        }
        printf("\n");
    }
}

void move(int** graph,int* pos, int ES_pos) {
    int gx = 0;
    int min = 9999;
    int* copy = (int*)malloc(16 * sizeof(int));
    int* copy1 = (int*)malloc(16 * sizeof(int));
    Direction direction = Right;
    Direction directionCopy = Right;
    int i = 0, j = 0, tmp = 0;
    copy = resetPos(copy, pos);
    copy1 = resetPos(copy1, pos);
    while (ES_pos != 16) {
        printf("\n");
        if (ES_pos % 4 == 0) {
            j = 4;
            i = ES_pos / 4;
        }
        else {
            i = (ES_pos / 4) + 1;
            j = ES_pos % 4;
        }
        min = 9999;
        if (i != 1 && directionCopy != Down) {
            swap(&copy[16], &copy[graph[i-2][j-1]]);
            gx = calcNotGoalState(copy);
            if (gx < min) {
                min = gx;
                copy1 = resetPos(copy1, copy);
                direction = Up;
                directionCopy = Down;
            }
        }
        copy = resetPos(copy, pos);
        if (i != 4 && directionCopy != Up) {
            swap(&copy[16], &copy[graph[i][j-1]]);
            gx = calcNotGoalState(copy);
            if (gx < min) {
                min = gx;
                copy1 = resetPos(copy1, copy);
                directionCopy = Down;
            }

        }
        copy = resetPos(copy, pos);
        if (j != 1 && directionCopy != Right) {
            swap(&copy[16], &copy[graph[i - 1][j - 2]]);
            gx = calcNotGoalState(copy);
            if (gx < min) {
                min = gx;
                copy1 = resetPos(copy1, copy);
                directionCopy = Left;
            }
        }
        copy = resetPos(copy, pos);
        if (j != 4 && directionCopy != Left) {
            swap(&copy[16], &copy[graph[i-1][j]]);
            gx = calcNotGoalState(copy);
            if (gx < min) {
                min = gx;
                copy1 = resetPos(copy1, copy);
                directionCopy = Right;
            }
        }
        copy = resetPos(copy, copy1);
        pos = resetPos(pos, copy);
        direction = directionCopy;
        switch (direction) {
        case Up:
            printf("Move: UP\n");
            break;
        case Down:
            printf("Move: DOWN\n");
            break;
        case Left:
            printf("Move: LEFT\n");
            break;
        case Right:
            printf("Move: RIGHT\n");
            break;
        }
        printf("Modified Puzzle :\n");
        printPuzzle(graph, copy, 1);
        ES_pos = copy[16];
        printf("\n");
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

int** importGraph(int** graph) {
    int i = 0, j = 0, n = 4;
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening file!\n");
        exit(0);
    }
    graph = init2DMatrix(graph, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(fptr, "%d", &graph[i][j]);
        }
    }
    fclose(fptr);
    return graph;
}

void main() {
    int* pos = (int*)malloc(17 * sizeof(int));
    int** graph = NULL;
    graph = importGraph(graph);
    pos = genPos(graph);
    printf("Entered Puzzle:\n");
    printPuzzle(graph, pos, 0);
    printf("\n");
    if (feasible(graph, pos)) {
        printf("Puzzle is FEASIBLE\n");
        move(graph, pos, pos[16]);
    }
    else {
        printf("Puzzle is NOT FEASIBLE\n");
    }
}