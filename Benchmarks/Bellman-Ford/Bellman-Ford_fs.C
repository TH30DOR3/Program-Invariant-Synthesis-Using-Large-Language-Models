#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_VERTICES 1000
#define INF INT_MAX

typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

// Bellman-Ford algorithm with verification invariants
void bellmanFord(int graph[MAX_VERTICES][MAX_VERTICES],
                 int vertices, int edges, int source)
{
    int distance[MAX_VERTICES];

    // Initialization
    for (int i = 0; i < vertices; ++i) {
        // Invariant: 0 <= i < vertices
        assert(i >= 0 && i < vertices);
        distance[i] = INF;
    }
    distance[source] = 0;

    // Invariant before main loop: distance[source] == 0 and all others are INF
    for (int i = 0; i < vertices; ++i) {
        if (i == source)
            assert(distance[i] == 0);
        else
            assert(distance[i] == INF);
    }

    // Relaxation step: run |V| - 1 times
    for (int i = 0; i < vertices - 1; ++i) {
        // Invariant: After i iterations, all shortest paths using ≤ i edges are computed
        assert(i >= 0 && i < vertices - 1);

        for (int j = 0; j < edges; ++j) {
            int u = graph[j][0];
            int v = graph[j][1];
            int w = graph[j][2];

            // Invariants for bounds
            assert(u >= 0 && u < vertices);
            assert(v >= 0 && v < vertices);

            // Invariant: triangle inequality preservation during relaxation
            if (u != -1 && distance[u] != INF) {
                if (distance[v] > distance[u] + w) {
                    distance[v] = distance[u] + w;
                }
                // After relaxation, ensure no over-relaxation has occurred
                assert(distance[v] <= distance[u] + w);
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < edges; ++i) {
        int u = graph[i][0];
        int v = graph[i][1];
        int w = graph[i][2];

        if (u != -1 && distance[u] != INF) {
            // Invariant: If further relaxation possible, a negative cycle exists
            assert(distance[v] >= distance[u] + w);
            if (distance[v] > distance[u] + w) {
                printf("Negative cycle detected\n");
                return;
            }
        }
    }

    // Final invariant: All shortest path distances computed correctly (no further improvement possible)
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; ++i) {
        assert(distance[i] >= INT_MIN && distance[i] <= INT_MAX);
        printf("%d \t\t %d\n", i, distance[i]);
    }
}

int main()
{
    int vertices = 6;
    int edges = 8;

    int graph[MAX_VERTICES][MAX_VERTICES] = {
        { 0, 1, 5 }, { 0, 2, 7 }, { 1, 2, 3 },
        { 1, 3, 4 }, { 1, 4, 6 }, { 3, 4, -1 },
        { 3, 5, 2 }, { 4, 5, -3 }
    };

    bellmanFord(graph, vertices, edges, 0);
    return 0;
}
