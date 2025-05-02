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
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int vertices) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->vertices = vertices;
	graph->array = (struct List*)malloc(vertices * sizeof(struct List));

    // MAKE ASSERTION HERE
	assert(graph != NULL);
	assert(graph->array != NULL);

	for (int i = 0; i < vertices; i++) {
		graph->array[i].head = NULL;
	}

    // MAKE ASSERTION HERE
	for (int i = 0; i < vertices; i++) {
		assert(graph->array[i].head == NULL);
	}

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
	struct Node* newNode = createNode(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void DFS(struct Graph* graph, int vertex, bool visited[]) {
	visited[vertex] = true;
	printf("%d ", vertex);

    // MAKE ASSERTION HERE
	assert(visited[vertex] == true);

	struct Node* currentNode = graph->array[vertex].head;

    // MAKE ASSERTION HERE
	assert(graph->array[vertex].head == NULL || graph->array[vertex].head != NULL);

	while (currentNode) {

		int adjacentVertex = currentNode->data;
        
        // MAKE ASSERTION HERE
		assert(adjacentVertex >= 0 && adjacentVertex < graph->vertices);

		if (!visited[adjacentVertex]) {
			DFS(graph, adjacentVertex, visited);
		}
        
        // MAKE ASSERTION HERE
		assert(visited[vertex] == true);

		currentNode = currentNode->next;

        // MAKE ASSERTION HERE
		assert(currentNode == NULL || currentNode != NULL);
	}

    // MAKE ASSERTION HERE
	assert(visited[vertex] == true);
}

void DFSTraversal(struct Graph* graph, int* order, int orderSize) {
	bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));

    // MAKE ASSERTION HERE
	assert(visited != NULL);

	for (int i = 0; i < graph->vertices; i++) {
		visited[i] = false;
	}

    // MAKE ASSERTION HERE
	for (int i = 0; i < graph->vertices; i++) {
		assert(visited[i] == false);
	}

	for (int i = 0; i < orderSize; i++) {
		if (!visited[order[i]]) {

            // MAKE ASSERTION HERE
			assert(order[i] >= 0 && order[i] < graph->vertices);
			assert(visited[order[i]] == false);

			DFS(graph, order[i], visited);
		}
	}

    // MAKE ASSERTION HERE
	for (int i = 0; i < graph->vertices; i++) {
		assert(visited[i] == true || visited[i] == false);
	}

	free(visited);
}

int main() {
	int vertices = 4;
	struct Graph* graph = createGraph(vertices);

    // MAKE ASSERTION HERE
	assert(graph != NULL);
	assert(graph->vertices == vertices);
	assert(graph->array != NULL);

	addEdge(graph, 2, 0);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 2);
	addEdge(graph, 0, 1);
	addEdge(graph, 3, 3);
	addEdge(graph, 1, 3);

	int order[] = {2, 0, 1, 3};
	int orderSize = sizeof(order) / sizeof(order[0]);

    // MAKE ASSERTION HERE
	assert(orderSize == 4);
	for (int i = 0; i < orderSize; i++) {
		assert(order[i] >= 0 && order[i] < vertices);
	}

	printf("Following is Depth First Traversal (starting from vertex 2):\n");
	DFSTraversal(graph, order, orderSize);

	return 0;
}
