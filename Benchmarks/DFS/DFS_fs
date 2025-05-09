
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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
	assert(newNode != NULL);  // Allocation must succeed
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int vertices) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	assert(graph != NULL);
	graph->vertices = vertices;
	graph->array = (struct List*)malloc(vertices * sizeof(struct List));
	assert(graph->array != NULL);

	for (int i = 0; i < vertices; i++) {
		// Invariant: 0 <= i < vertices
		assert(i >= 0 && i < vertices);
		
		// Before initialization, ensure no head is dangling
		for (int j = 0; j < i; j++) {
			assert(graph->array[j].head == NULL);
		}

		graph->array[i].head = NULL;
	}

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
	assert(src >= 0 && src < graph->vertices);
	assert(dest >= 0 && dest < graph->vertices);

	struct Node* newNode = createNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void DFS(struct Graph* graph, int vertex, bool visited[]) {
	assert(vertex >= 0 && vertex < graph->vertices);
	assert(visited != NULL);

	visited[vertex] = true;
	printf("%d ", vertex);

	struct Node* currentNode = graph->array[vertex].head;
	while (currentNode) {
		// Invariant: currentNode is a node in the adjacency list of vertex
		assert(currentNode != NULL);
		int adjacentVertex = currentNode->data;

		// Invariant: adjacentVertex is within graph bounds
		assert(adjacentVertex >= 0 && adjacentVertex < graph->vertices);

		if (!visited[adjacentVertex]) {
			DFS(graph, adjacentVertex, visited);
		}

		currentNode = currentNode->next;
	}
}

void DFSTraversal(struct Graph* graph, int* order, int orderSize) {
	assert(graph != NULL);
	assert(order != NULL);
	assert(orderSize <= graph->vertices);

	bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
	assert(visited != NULL);

	for (int i = 0; i < graph->vertices; i++) {
		// Invariant: 0 <= i < graph->vertices
		assert(i >= 0 && i < graph->vertices);

		// All visited[j] for j < i are false
		for (int j = 0; j < i; j++) {
			assert(visited[j] == false);
		}

		visited[i] = false;
	}

	for (int i = 0; i < orderSize; i++) {
		// Invariant: 0 <= i < orderSize
		assert(i >= 0 && i < orderSize);

		// Each order[i] is a valid vertex
		assert(order[i] >= 0 && order[i] < graph->vertices);

		if (!visited[order[i]]) {
			DFS(graph, order[i], visited);
		}
	}

	free(visited);
}

int main() {
	int vertices = 4;
	struct Graph* graph = createGraph(vertices);

	addEdge(graph, 2, 0);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 2);
	addEdge(graph, 0, 1);
	addEdge(graph, 3, 3);
	addEdge(graph, 1, 3);

	int order[] = {2, 0, 1, 3};
	int orderSize = sizeof(order) / sizeof(order[0]);

	printf("Following is Depth First Traversal (starting from vertex 2):\n");
	DFSTraversal(graph, order, orderSize);

	return 0;
}
