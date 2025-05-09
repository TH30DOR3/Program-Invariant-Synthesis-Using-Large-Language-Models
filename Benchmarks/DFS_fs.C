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
	assert(newNode != NULL); // Allocation must succeed
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int vertices) {
	assert(vertices > 0); // Must have at least one vertex
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	assert(graph != NULL); // Allocation must succeed
	graph->vertices = vertices;

	graph->array = (struct List*)malloc(vertices * sizeof(struct List));
	assert(graph->array != NULL); // Allocation must succeed

	for (int i = 0; i < vertices; i++) {
		// Loop invariant: 0 <= i < vertices
		assert(i >= 0 && i < vertices);

		graph->array[i].head = NULL;
	}

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
	// Invariants: src and dest must be valid vertices
	assert(graph != NULL);
	assert(src >= 0 && src < graph->vertices);
	assert(dest >= 0 && dest < graph->vertices);

	struct Node* newNode = createNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void DFS(struct Graph* graph, int vertex, bool visited[]) {
	assert(graph != NULL);
	assert(visited != NULL);
	assert(vertex >= 0 && vertex < graph->vertices);
	assert(visited[vertex] == false); // Precondition for DFS

	visited[vertex] = true;
	printf("%d ", vertex);

	struct Node* currentNode = graph->array[vertex].head;
	while (currentNode) {
		// Loop invariant: currentNode is a valid node in the adjacency list
		assert(currentNode != NULL);

		int adjacentVertex = currentNode->data;

		// Invariant: 0 <= adjacentVertex < graph->vertices
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
	assert(orderSize >= 0 && orderSize <= graph->vertices); // Can't traverse more than all vertices

	bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
	assert(visited != NULL); // Allocation must succeed

	for (int i = 0; i < graph->vertices; i++) {
		// Loop invariant: 0 <= i < graph->vertices
		assert(i >= 0 && i < graph->vertices);
		visited[i] = false;
	}

	for (int i = 0; i < orderSize; i++) {
		// Loop invariant: 0 <= i < orderSize
		assert(i >= 0 && i < orderSize);
		// Invariant: order[i] is a valid vertex
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

	// Invariant: all entries in `order` must be valid vertices
	for (int i = 0; i < orderSize; i++) {
		assert(order[i] >= 0 && order[i] < vertices);
	}

	printf("Following is Depth First Traversal (starting from vertex 2):\n");
	DFSTraversal(graph, order, orderSize);

	return 0;
}
