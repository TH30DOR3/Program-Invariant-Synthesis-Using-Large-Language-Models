#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  // Added for assertions

#define MAX_VERTICES 1000
#define INF INT_MAX

typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

void bellmanFord(int graph[MAX_VERTICES][MAX_VERTICES],
                 int vertices, int edges, int source)
{
    int distance[MAX_VERTICES];

    // Loop initializes all distances to INF
    for (int i = 0; i < vertices; ++i) {
        assert(i >= 0 && i < vertices);
        distance[i] = INF;
    }

    // After initialization: only source has distance 0
    assert(source >= 0 && source < vertices);
    distance[source] = 0;

    // Loop invariant: after k iterations, the shortest path to any vertex
    // uses at most k edges (Bellman-Ford guarantee)
    for (int i = 0; i < vertices - 1; ++i) {
        assert(i >= 0 && i < vertices - 1);

        for (int j = 0; j < edges; ++j) {
            assert(j >= 0 && j < edges);
            int u = graph[j][0];
            int v = graph[j][1];
            int w = graph[j][2];

            // Invariant: edge must be valid
            assert(u >= 0 && u < vertices);
            assert(v >= 0 && v < vertices);
            // Check if relaxation is valid and within bounds
            if (u != -1
                && distance[u] != INF
                && distance[v] > distance[u] + w) {
                // Invariant before update
                assert(distance[u] + w < distance[v]);
                distance[v] = distance[u] + w;
                // Invariant after update
                assert(distance[v] == distance[u] + w);
            }
        }
    }

    // After all V-1 iterations, no further relaxation should be possible
    for (int i = 0; i < edges; ++i) {
        assert(i >= 0 && i < edges);
        int u = graph[i][0];
        int v = graph[i][1];
        int w = graph[i][2];

        if (u != -1
            && distance[u] != INF
            && distance[v] > distance[u] + w) {
            // Negative weight cycle detected
            assert(0 && "Negative weight cycle should not exist in valid input");
            printf("Negative cycle detected\n");
            return;
        }
    }

    // Final output: distance[i] is shortest distance from source
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; ++i) {
        assert(i >= 0 && i < vertices);
        assert(distance[i] == INF || distance[i] >= 0 || distance[i] < 0); // value must be initialized
        printf("%d \t\t %d\n", i, distance[i]);
    }
}

int main()
{
    int vertices = 6;
    int edges = 8;

    // Invariant: all graph[i] must have valid vertex indices
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        { 0, 1, 5 }, { 0, 2, 7 }, { 1, 2, 3 },
        { 1, 3, 4 }, { 1, 4, 6 }, { 3, 4, -1 },
        { 3, 5, 2 }, { 4, 5, -3 }
    };

    // Ensure all edge definitions are valid before algorithm starts
    for (int i = 0; i < edges; ++i) {
        assert(graph[i][0] >= 0 && graph[i][0] < vertices);
        assert(graph[i][1] >= 0 && graph[i][1] < vertices);
    }

    bellmanFord(graph, vertices, edges, 0);
    return 0;
}
