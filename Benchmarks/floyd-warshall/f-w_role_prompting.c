#include <stdio.h>
#include <assert.h>

#define V 5
#define INF 100000000

void floydWarshall(int dist[V][V]) {
    for (int k = 0; k < V; k++) {

        // Loop invariant: For all i,j: dist[i][j] == minimum weight of path from i to j using only nodes in {0,...,k-1}
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                // Invariant: dist[i][j] <= dist[i][k] + dist[k][j] (Triangle inequality)
                assert(dist[i][j] <= (dist[i][k] == INF || dist[k][j] == INF ? INF : dist[i][k] + dist[k][j]));

                // Invariant: dist[i][j] >= minimal cost using any path through {0,...,k}
                // This can't be expressed directly in C as a simple assertion but could be modeled as:
                //    assert(dist[i][j] >= optimal_dist[i][j][k]);
                // where optimal_dist is precomputed for formal reasoning

                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                }

                // Post-update invariant: dist[i][j] is the minimum of previous dist[i][j] and new possible path
                assert(dist[i][j] <= (dist[i][k] == INF || dist[k][j] == INF ? INF : dist[i][k] + dist[k][j]));
            }
        }
    }

    // Final invariant after all k: dist[i][j] is shortest distance from i to j over any path
    for (int i = 0; i < V; i++) {
        assert(dist[i][i] == 0); // No negative cycles (required for Floyd-Warshall to be valid)
        for (int j = 0; j < V; j++) {
            assert(dist[i][j] <= INF); // Finite or INF
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
