#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10

// 그래프의 인접 리스트를 구현하기 위한 구조체
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 그래프를 구현하기 위한 구조체
typedef struct Graph {
    Node* adjLists[MAX_VERTICES];
    bool visited[MAX_VERTICES];
} Graph;

Graph* createGraph();
void addVertex(Graph* graph, int vertex);
void addEdge(Graph* graph, int src, int dest);
void DFS(Graph* graph, int startVertex);
void BFS(Graph* graph, int startVertex);
void printGraph(Graph* graph);
void initializeVisited(Graph* graph);
void menu();
void handleCommand(char command, Graph* graph);

int main() {
    Graph* graph = createGraph();
    char command;

    printf("[----- [송 동 선] [2023078041] -----]\n");

    while (1) {
        menu();
        printf("Command: ");
        scanf(" %c", &command);
        if (command == 'q') {
            break;
        }
        handleCommand(command, graph);
    }

    return 0;
}

void menu() {
    printf("----------------------------------------------------------------\n");
    printf("                          Graph Searches                        \n");
    printf("----------------------------------------------------------------\n");
    printf("Initialize Graph \t= z\n");
    printf("Insert Vertex \t\t= v\t\t");
    printf("Insert Edge \t\t\t= e\n");
    printf("Depth First Search \t= d\t\t");
    printf("Breadth First Search \t= b\n");
    printf("Print Graph \t\t= p\t\t");
    printf("Quit \t\t\t\t\t= q\n");
    printf("----------------------------------------------------------------\n");
}

// 그래프를 생성하는 함수
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

// 정점을 추가하는 함수
void addVertex(Graph* graph, int vertex) {
    if (vertex < 0 || vertex >= MAX_VERTICES) {
        printf("Invalid vertex number.\n");
    } else {
        printf("Vertex %d added.\n", vertex);
    }
}

// 간선을 추가하는 함수
void addEdge(Graph* graph, int src, int dest) {
    if (src < 0 || src >= MAX_VERTICES || dest < 0 || dest >= MAX_VERTICES) {
        printf("Invalid edge.\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // 무방향 그래프일 경우
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;

    printf("Edge from %d to %d added.\n", src, dest);
}

// 깊이 우선 탐색
void DFS(Graph* graph, int startVertex) {
    initializeVisited(graph);

    int stack[MAX_VERTICES];
    int top = -1;
    stack[++top] = startVertex;
    graph->visited[startVertex] = true;

    printf("DFS Traversal starting from vertex %d: ", startVertex);

    while (top != -1) {
        int currentVertex = stack[top--];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];

        int vertices[MAX_VERTICES];
        int count = 0;
        while (temp) {
            if (!graph->visited[temp->vertex]) {
                vertices[count++] = temp->vertex;
            }
            temp = temp->next;
        }
        for (int i = count - 1; i >= 0; i--) {
            stack[++top] = vertices[i];
            graph->visited[vertices[i]] = true;
        }
    }
    printf("\n");
}

// 너비 우선 탐색
void BFS(Graph* graph, int startVertex) {
    initializeVisited(graph);

    int queue[MAX_VERTICES];
    int front = 0;
    int rear = -1;
    queue[++rear] = startVertex;
    graph->visited[startVertex] = true;

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    while (front <= rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];

        int vertices[MAX_VERTICES];
        int count = 0;
        while (temp) {
            if (!graph->visited[temp->vertex]) {
                vertices[count++] = temp->vertex;
            }
            temp = temp->next;
        }
        for (int i = 0; i < count; i++) {
            queue[++rear] = vertices[i];
            graph->visited[vertices[i]] = true;
        }
    }
    printf("\n");
}

// 그래프 출력
void printGraph(Graph* graph) {
    for (int v = 0; v < MAX_VERTICES; v++) {
        Node* temp = graph->adjLists[v];
        printf("Vertex %d:", v);
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// 방문 여부 초기화
void initializeVisited(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = false;
    }
}

// 명령어 처리
void handleCommand(char command, Graph* graph) {
    int vertex, src, dest;
    switch (command) {
        case 'z':
            for (int i = 0; i < MAX_VERTICES; i++) {
                graph->adjLists[i] = NULL;
                graph->visited[i] = false;
            }
            printf("Graph initialized.\n");
            break;
        case 'v':
            printf("Enter vertex number to add: ");
            scanf("%d", &vertex);
            addVertex(graph, vertex);
            break;
        case 'e':
            printf("Enter edge (src dest): ");
            scanf("%d %d", &src, &dest);
            addEdge(graph, src, dest);
            break;
        case 'd':
            printf("Enter starting vertex for DFS: ");
            scanf("%d", &vertex);
            DFS(graph, vertex);
            break;
        case 'b':
            printf("Enter starting vertex for BFS: ");
            scanf("%d", &vertex);
            BFS(graph, vertex);
            break;
        case 'p':
            printGraph(graph);
            break;
        default:
            printf("Invalid command.\n");
    }
}