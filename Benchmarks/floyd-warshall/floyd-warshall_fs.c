#include <stdio.h>
#include <assert.h>

#define V 5
#define INF 100000000

void floydWarshall(int dist[V][V]) {
    for (int k = 0; k < V; k++) {
        // Loop invariant: k in valid range
        assert(k >= 0 && k < V);

        for (int i = 0; i < V; i++) {
            // Loop invariant: i in valid range
            assert(i >= 0 && i < V);

            for (int j = 0; j < V; j++) {
                // Loop invariant: j in valid range
                assert(j >= 0 && j < V);

                // Invariant: No self-loop has negative cost
                assert(dist[i][i] == 0);

                // Invariant: Triangle inequality must hold (only if intermediate paths exist)
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    assert(dist[i][j] <= dist[i][k] + dist[k][j]);
                }

                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                }

                // Post-update invariant: dist[i][j] is still minimum so far
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    assert(dist[i][j] <= dist[i][k] + dist[k][j]);
                }

                // Invariant: No distance should be negative
                assert(dist[i][j] >= 0 || dist[i][j] == INF);
            }
        }
    }

    // Final invariants: Check for correctness after algorithm completes
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            // Final invariant: Triangle inequality holds for all pairs
            for (int k = 0; k < V; k++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    assert(dist[i][j] <= dist[i][k] + dist[k][j]);
                }
            }

            // Invariant: No distance from a node to itself should be negative
            if (i == j) {
                assert(dist[i][j] == 0);
            }
        }
    }
}

int main() {
    int dist[V][V] = {
        {0,   4,   INF, 5,   INF},
        {INF, 0,   1,   INF, 6},
        {2,   INF, 0,   3,   INF},
        {INF, INF, 1,   0,   2},
        {1,   INF, INF, 4,   0}
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
