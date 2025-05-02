#include <stdio.h>
#include <assert.h>  // Added to enable use of assert
#define V 5
#define INF 100000000

void floydWarshall(int dist[V][V]) {
    // Loop over all intermediate vertices
    for (int k = 0; k < V; k++) {
        assert(k >= 0 && k < V);  // Invariant: k is always a valid index

        for (int i = 0; i < V; i++) {
            assert(i >= 0 && i < V);  // Invariant: i is always a valid index

            for (int j = 0; j < V; j++) {
                assert(j >= 0 && j < V);  // Invariant: j is always a valid index

                // Invariant before update: triangle inequality check preconditions
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    assert(dist[i][k] >= 0);  // path weights are non-negative
                    assert(dist[k][j] >= 0);  // path weights are non-negative

                    // Check if triangle inequality can apply
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        // Invariant: After this assignment, dist[i][j] is shortest known path
                        dist[i][j] = dist[i][k] + dist[k][j];
                        assert(dist[i][j] <= dist[i][k] + dist[k][j]);
                    }
                }

                // General invariant: all distances are either INF or non-negative
                assert(dist[i][j] == INF || dist[i][j] >= 0);
            }
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

    // Invariant: initial distance matrix values
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            assert(dist[i][j] == 0 || dist[i][j] == INF || dist[i][j] > 0);
        }
    }

    floydWarshall(dist);

    // Postcondition: dist[i][j] should be shortest distance or INF if unreachable
    for (int i = 0; i < V; i++) {
        assert(i >= 0 && i < V);

        for (int j = 0; j < V; j++) {
            assert(j >= 0 && j < V);
            assert(dist[i][j] == INF || dist[i][j] >= 0);  // all distances valid
            if (i == j) assert(dist[i][j] == 0);  // diagonal must be 0 after FW
        }
    }

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
