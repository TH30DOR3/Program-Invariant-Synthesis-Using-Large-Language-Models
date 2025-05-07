#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>  // Required for using assert()

struct Node {
	int data;
	struct Node* next;
};

struct List {
	struct Node* head;
};

struct Graph {
	int vertices;
	struct List* array;
};

struct Node* createNode(int data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	assert(newNode != NULL);  // Invariant: Memory allocation must succeed
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int vertices) {
	assert(vertices > 0);  // Invariant: Number of vertices must be positive
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	assert(graph != NULL);  // Invariant: Memory allocation must succeed

	graph->vertices = vertices;
	graph->array = (struct List*)malloc(vertices * sizeof(struct List));
	assert(graph->array != NULL);  // Invariant: Memory allocation must succeed

	for (int i = 0; i < vertices; i++) {
		graph->array[i].head = NULL;
	}

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
	assert(graph != NULL);
	assert(src >= 0 && src < graph->vertices);   // Invariant: Source index must be within bounds
	assert(dest >= 0 && dest < graph->vertices); // Invariant: Destination index must be within bounds

	struct Node* newNode = createNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void DFS(struct Graph* graph, int vertex, bool visited[]) {
	assert(graph != NULL);
	assert(vertex >= 0 && vertex < graph->vertices); // Invariant: Vertex index must be within bounds
	assert(visited != NULL);

	visited[vertex] = true;
	printf("%d ", vertex);

	struct Node* currentNode = graph->array[vertex].head;
	while (currentNode) {
		int adjacentVertex = currentNode->data;
		assert(adjacentVertex >= 0 && adjacentVertex < graph->vertices); // Invariant: Adjacency index must be within bounds
		if (!visited[adjacentVertex]) {
			DFS(graph, adjacentVertex, visited);
		}
		currentNode = currentNode->next;
	}
}

void DFSTraversal(struct Graph* graph, int* order, int orderSize) {
	assert(graph != NULL);
	assert(order != NULL);
	assert(orderSize >= 0 && orderSize <= graph->vertices); // Invariant: Valid order size

	bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
	assert(visited != NULL); // Invariant: Memory allocation must succeed

	for (int i = 0; i < graph->vertices; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < orderSize; i++) {
		assert(order[i] >= 0 && order[i] < graph->vertices); // Invariant: Each vertex in order must be valid
		if (!visited[order[i]]) {
			DFS(graph, order[i], visited);
		}
	}

	free(visited);
}

int main() {
	int vertices = 4;
	assert(vertices > 0);

	struct Graph* graph = createGraph(vertices);
	assert(graph != NULL);

	addEdge(graph, 2, 0);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 2);
	addEdge(graph, 0, 1);
	addEdge(graph, 3, 3);
	addEdge(graph, 1, 3);

	int order[] = {2, 0, 1, 3};
	int orderSize = sizeof(order) / sizeof(order[0]);
	assert(orderSize == vertices); // Invariant: Traversal order should match number of vertices

	printf("Following is Depth First Traversal (starting from vertex 2):\n");
	DFSTraversal(graph, order, orderSize);

	return 0;
}
