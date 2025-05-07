#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  // Include for assert()

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
    assert(vertices > 0 && vertices <= MAX_VERTICES);
    assert(edges >= 0 && edges <= MAX_VERTICES);  // Edge count is limited
    assert(source >= 0 && source < vertices);     // Valid source vertex

    int distance[MAX_VERTICES];

    for (int i = 0; i < vertices; ++i) {
        assert(i >= 0 && i < MAX_VERTICES);  // Ensure index within bounds
        distance[i] = INF;
    }
    distance[source] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
        assert(i >= 0 && i < vertices - 1);  // Loop invariant
        for (int j = 0; j < edges; ++j) {
            // Sanity check on graph input
            assert(graph[j][0] >= 0 && graph[j][0] < vertices);
            assert(graph[j][1] >= 0 && graph[j][1] < vertices);

            if (graph[j][0] != -1
                && distance[graph[j][0]] != INF
                && distance[graph[j][1]] > distance[graph[j][0]] + graph[j][2]) {

                // Invariant before relaxation
                assert(distance[graph[j][0]] + graph[j][2] >= INT_MIN); // prevent underflow
                assert(distance[graph[j][0]] + graph[j][2] <= INT_MAX); // prevent overflow

                distance[graph[j][1]] = distance[graph[j][0]] + graph[j][2];

                // Post-condition: updated distance must be less than before
                assert(distance[graph[j][1]] <= distance[graph[j][0]] + graph[j][2]);
            }
        }
    }

    for (int i = 0; i < edges; ++i) {
        assert(graph[i][0] >= 0 && graph[i][0] < vertices);
        assert(graph[i][1] >= 0 && graph[i][1] < vertices);

        if (graph[i][0] != -1
            && distance[graph[i][0]] != INF
            && distance[graph[i][1]] > distance[graph[i][0]] + graph[i][2]) {
            printf("Negative cycle detected\n");
            return;
        }
    }

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; ++i) {
        assert(i >= 0 && i < vertices);
        assert(distance[i] >= 0 || distance[i] == INF);  // Distance is non-negative or INF
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

    // Precondition: all vertex indices must be valid
    for (int i = 0; i < edges; ++i) {
        assert(graph[i][0] >= 0 && graph[i][0] < vertices);
        assert(graph[i][1] >= 0 && graph[i][1] < vertices);
    }

    bellmanFord(graph, vertices, edges, 0);
    return 0;
}
