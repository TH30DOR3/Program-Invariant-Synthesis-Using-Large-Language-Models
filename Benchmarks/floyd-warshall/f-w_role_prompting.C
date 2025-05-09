#include <assert.h>
#include <stdio.h>

#define V 5
#define INF 100000000

void floydWarshall(int dist[V][V]) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                // --- Loop invariants ---
                // Reflexivity: zero distance from a node to itself
                assert(dist[i][i] == 0);

                // Triangle inequality: current dist is no greater than using k as intermediate
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    assert(dist[i][j] <= dist[i][k] + dist[k][j]);
                }

                // Symmetry not assumed (not for directed graphs)

                // No negative cycles: dist[i][i] must remain 0
                assert(dist[i][i] == 0);

                // Valid bounds
                assert(i >= 0 && i < V);
                assert(j >= 0 && j < V);
                assert(k >= 0 && k < V);

                // Optional (non-overflow safety):
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    assert(dist[i][k] + dist[k][j] >= 0); // No integer overflow
                }

                // --- Update step ---
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }

                // --- Post-condition (can also be used as invariant) ---
                // After update, dist[i][j] is at least as small as it was before
                assert(dist[i][j] <= dist[i][k] + dist[k][j] || dist[i][k] == INF || dist[k][j] == INF);
            }
        }
    }
}
