#include <stdio.h>
#include <assert.h>

#define V 5
#define INF 100000000

void floydWarshall(int dist[V][V]) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Invariant: Distance from a node to itself is always 0
                assert(dist[i][i] == 0);

                // Invariant: Triangle inequality should hold if intermediate path is valid
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    assert(dist[i][j] <= dist[i][k] + dist[k][j]);
                }

                // Update if shorter path is found
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Final invariants after Floyd-Warshall completes
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            // Invariant: Distance from a node to itself must be 0
            if (i == j) {
                assert(dist[i][j] == 0);
            }

            // Invariant: Triangle inequality must now hold for all k
            for (int k = 0; k < V; k++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    assert(dist[i][j] <= dist[i][k] + dist[k][j]);
                }
            }

            // Invariant: All distances must be non-negative or INF
            assert(dist[i][j] >= 0 || dist[i][j] == INF);
        }
    }
}

int main() {
    int dist[V][V] = {
        {0, 4, INF, 5, INF},
        {INF, 0, 1, INF, 6},
        {2, INF, 0, 3, INF},
        {INF, INF, 1, 0, 2},
        {1, INF, INF, 4, 0}
    };

    floydWarshall(dist);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}
