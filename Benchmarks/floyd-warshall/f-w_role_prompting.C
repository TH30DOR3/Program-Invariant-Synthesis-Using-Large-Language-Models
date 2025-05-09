#include <assert.h>

// Outer loop invariant: at start of each iteration of k
for (int k = 0; k < V; k++) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {

            // Invariants BEFORE update
            assert(dist[i][i] == 0);  // No negative self-loop
            assert(dist[i][j] <= dist[i][k] + dist[k][j] || 
                   dist[i][k] == INF || dist[k][j] == INF); // Triangle inequality preserved

            // Core update logic
            if (dist[i][k] != INF && dist[k][j] != INF &&
                dist[i][k] + dist[k][j] < dist[i][j]) {
                dist[i][j] = dist[i][k] + dist[k][j];
            }

            // Invariants AFTER update
            assert(dist[i][j] <= dist[i][k] + dist[k][j] || 
                   dist[i][k] == INF || dist[k][j] == INF); // Triangle inequality preserved post-update
            assert(dist[i][i] == 0); // No self-loop cost should become negative
        }
    }

    // Global invariant after completing k-th phase
    for (int a = 0; a < V; a++) {
        for (int b = 0; b < V; b++) {
            for (int c = 0; c < V; c++) {
                if (dist[a][b] != INF && dist[b][c] != INF) {
                    assert(dist[a][c] <= dist[a][b] + dist[b][c]); // Global triangle inequality
                }
            }
        }
    }
}
