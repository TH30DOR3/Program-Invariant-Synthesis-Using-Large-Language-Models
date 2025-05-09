#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h> // Added to enable use of assert

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
	// Post-condition: newNode is not NULL and properly initialized
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	assert(newNode != NULL); // Memory allocation must succeed
	newNode->data = data;
	newNode->next = NULL;
	assert(newNode->data == data);
	assert(newNode->next == NULL);
	return newNode;
}

struct Graph* createGraph(int vertices) {
	assert(vertices > 0); // Graph must have at least one vertex
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	assert(graph != NULL); // Memory allocation must succeed
	graph->vertices = vertices;
	graph->array = (struct List*)malloc(vertices * sizeof(struct List));
	assert(graph->array != NULL); // Memory allocation must succeed

	for (int i = 0; i < vertices; i++) {
		// Loop invariant: 0 <= i <= vertices
		assert(i >= 0 && i <= vertices);
		graph->array[i].head = NULL;
	}
	// Post-condition: all head pointers are NULL
	for (int i = 0; i < vertices; i++) {
		assert(graph->array[i].head == NULL);
	}

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
	assert(graph != NULL);
	assert(src >= 0 && src < graph->vertices); // src must be a valid vertex
	assert(dest >= 0 && dest < graph->vertices); // dest must be a valid vertex

	struct Node* newNode = createNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// Post-condition: head of list at src is not NULL
	assert(graph->array[src].head != NULL);
	assert(graph->array[src].head->data == dest);
}

void DFS(struct Graph* graph, int vertex, bool visited[]) {
	assert(graph != NULL);
	assert(vertex >= 0 && vertex < graph->vertices);
	assert(visited != NULL);
	assert(!visited[vertex]); // Pre-condition: vertex is not visited before DFS

	visited[vertex] = true;
	printf("%d ", vertex);

	struct Node* currentNode = graph->array[vertex].head;

	while (currentNode) {
		assert(currentNode->data >= 0 && currentNode->data < graph->vertices); // valid adjacent vertex
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
	assert(orderSize >= 0);

	bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
	assert(visited != NULL);

	for (int i = 0; i < graph->vertices; i++) {
		// Loop invariant: 0 <= i <= graph->vertices
		assert(i >= 0 && i <= graph->vertices);
		visited[i] = false;
	}

	for (int i = 0; i < orderSize; i++) {
		// Loop invariant: 0 <= i <= orderSize
		assert(i >= 0 && i <= orderSize);
		assert(order[i] >= 0 && order[i] < graph->vertices); // each vertex in order must be valid
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

	addEdge(graph, 2, 0);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 2);
	addEdge(graph, 0, 1);
	addEdge(graph, 3, 3);
	addEdge(graph, 1, 3);

	int order[] = {2, 0, 1, 3};
	int orderSize = sizeof(order) / sizeof(order[0]);
	assert(orderSize == vertices); // All vertices are covered in order

	printf("Following is Depth First Traversal (starting from vertex 2):\n");
	DFSTraversal(graph, order, orderSize);

	return 0;
}
