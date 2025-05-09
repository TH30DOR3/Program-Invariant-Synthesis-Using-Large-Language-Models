#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

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

    // Initialization: All distances are INF except source.
    for (int i = 0; i < vertices; ++i) {
        distance[i] = INF;
    }
    distance[source] = 0;

    // Outer loop: relaxation performed vertices - 1 times.
    for (int i = 0; i < vertices - 1; ++i) {
        // Loop invariant: 0 <= i <= vertices - 1
        assert(i >= 0 && i < vertices);

        // Loop invariant: distance[source] == 0
        assert(distance[source] == 0);

        // Loop invariant: for all k in [0, vertices),
        // distance[k] == INF or distance[k] <= shortest path from source to k using ≤ i edges
        for (int k = 0; k < vertices; ++k) {
            assert(distance[k] == INF || distance[k] >= 0);
        }

        for (int j = 0; j < edges; ++j) {
            // Loop invariant: 0 <= j <= edges
            assert(j >= 0 && j <= edges);

            int u = graph[j][0];
            int v = graph[j][1];
            int w = graph[j][2];

            // Invariant: node indices u, v must be within bounds if valid
            assert((u == -1 || (u >= 0 && u < vertices)) &&
                   (v == -1 || (v >= 0 && v < vertices)));

            if (u != -1
                && distance[u] != INF
                && distance[v] > distance[u] + w) {

                // Invariant before update: distance[v] > distance[u] + w
                assert(distance[v] > distance[u] + w);

                // Relax edge (u, v)
                distance[v] = distance[u] + w;

                // Invariant after update: distance[v] == distance[u] + w
                assert(distance[v] == distance[u] + w);
            }
        }
    }

    // Postcondition: No edge can be further relaxed if no negative cycle
    for (int i = 0; i < edges; ++i) {
        int u = graph[i][0];
        int v = graph[i][1];
        int w = graph[i][2];

        if (u != -1
            && distance[u] != INF
            && distance[v] > distance[u] + w) {
            printf("Negative cycle detected\n");
            return;
        }
    }

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; ++i)
        printf("%d \t\t %d\n", i, distance[i]);
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

