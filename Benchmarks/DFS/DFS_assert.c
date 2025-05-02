#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h> // Added for assertions

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
	assert(newNode != NULL); // Invariant: memory allocation should not fail

	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}

struct Graph* createGraph(int vertices) {
	assert(vertices > 0); // Invariant: graph must have at least one vertex

	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	assert(graph != NULL); // Invariant: memory allocation should not fail

	graph->vertices = vertices;
	graph->array = (struct List*)malloc(vertices * sizeof(struct List));
	assert(graph->array != NULL); // Invariant: list array allocation successful

	for (int i = 0; i < vertices; i++) {
		assert(i >= 0 && i < vertices); // Invariant: i is a valid index
		graph->array[i].head = NULL;
	}

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
	assert(graph != NULL);
	assert(src >= 0 && src < graph->vertices); // Invariant: source index is valid
	assert(dest >= 0 && dest < graph->vertices); // Invariant: destination index is valid

	struct Node* newNode = createNode(dest);
	assert(newNode != NULL); // Invariant: new node creation successful

	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void DFS(struct Graph* graph, int vertex, bool visited[]) {
	assert(graph != NULL);
	assert(visited != NULL);
	assert(vertex >= 0 && vertex < graph->vertices); // Invariant: vertex is within bounds
	assert(!visited[vertex]); // Invariant: vertex must be unvisited before visiting

	visited[vertex] = true;
	printf("%d ", vertex);

	struct Node* currentNode = graph->array[vertex].head;
	while (currentNode) {
		assert(currentNode->data >= 0 && currentNode->data < graph->vertices); // Invariant: valid adjacent vertex
		int adjacentVertex = currentNode->data;

		if (!visited[adjacentVertex]) {
			DFS(graph, adjacentVertex, visited);
		}
		currentNode = currentNode->next;
	}
}

void DFSTraversal(struct Graph* graph, int* order, int orderSize) {
	assert(graph != NULL);
	assert(order != NULL);
	assert(orderSize >= 0 && orderSize <= graph->vertices); // Invariant: orderSize must be valid

	bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
	assert(visited != NULL); // Invariant: memory allocation successful

	for (int i = 0; i < graph->vertices; i++) {
		assert(i >= 0 && i < graph->vertices);
		visited[i] = false;
	}

	for (int i = 0; i < orderSize; i++) {
		assert(order[i] >= 0 && order[i] < graph->vertices); // Invariant: each start vertex is valid
		if (!visited[order[i]]) {
			DFS(graph, order[i], visited);
		}
	}

	free(visited);
}

int main() {
	int vertices = 4;
	assert(vertices > 0); // Invariant: vertices must be positive

	struct Graph* graph = createGraph(vertices);

	addEdge(graph, 2, 0);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 2);
	addEdge(graph, 0, 1);
	addEdge(graph, 3, 3);
	addEdge(graph, 1, 3);

	int order[] = {2, 0, 1, 3};
	int orderSize = sizeof(order) / sizeof(order[0]);
	assert(orderSize == 4); // Invariant: should match array size

	printf("Following is Depth First Traversal (starting from vertex 2):\n");
	DFSTraversal(graph, order, orderSize);

	return 0;
}
