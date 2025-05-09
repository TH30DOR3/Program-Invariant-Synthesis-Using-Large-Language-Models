#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>  // Added for assertions

#define V 5

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        // Invariant: v is in range [0, V)
        assert(v >= 0 && v < V);

        // Invariant: key[v] is an int, can be INT_MAX or a graph weight
        // No direct assertion here since key[v] may be uninitialized before primMST

        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;

            // Invariant: min_index is in range [0, V)
            assert(min_index >= 0 && min_index < V);
        }
    }

    // Postcondition: min_index should be valid if at least one mstSet[v] == false
    return min_index;
}

int printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        // Invariant: parent[i] must be a valid index
        assert(parent[i] >= 0 && parent[i] < V);
        assert(i >= 0 && i < V);
        printf("%d - %d \t%d \n", parent[i], i, graph[parent[i]][i]);
    }
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        // Invariant: i is in range [0, V)
        assert(i >= 0 && i < V);

        key[i] = INT_MAX;
        mstSet[i] = false;

        // Invariant: key[i] is INT_MAX and mstSet[i] is false
        assert(key[i] == INT_MAX);
        assert(mstSet[i] == false);
    }

    key[0] = 0;
    parent[0] = -1;

    // Invariant: First vertex is chosen, key[0] == 0, parent[0] == -1
    assert(key[0] == 0);
    assert(parent[0] == -1);

    for (int count = 0; count < V - 1; count++) {
        // Invariant: count in [0, V-2]
        assert(count >= 0 && count < V - 1);

        int u = minKey(key, mstSet);

        // Invariant: u is a valid vertex index
        assert(u >= 0 && u < V);

        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            // Invariant: v in [0, V)
            assert(v >= 0 && v < V);

            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];

                // Invariant: parent[v] is u and key[v] was updated
                assert(parent[v] == u);
                assert(key[v] == graph[u][v]);
            }
        }
    }

    // At this point: all vertices are in mstSet
    for (int i = 0; i < V; i++) {
        // Invariant: each vertex is either in MST or about to be
        assert(mstSet[i] == true || key[i] == INT_MAX);
    }

    printMST(parent, graph);
}

int main() {
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };

    // Invariant: graph is symmetric and weights are non-negative
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            assert(graph[i][j] == graph[j][i]); // undirected graph
            assert(graph[i][j] >= 0);
        }
    }

    primMST(graph);

    return 0;
}
