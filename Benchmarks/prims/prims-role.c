#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#define V 5

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        // Invariant: key[v] holds the minimum edge weight to include v in MST if mstSet[v] == false
        assert(key[v] >= 0 && key[v] <= INT_MAX);

        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    // Invariant: the chosen min_index is not yet in MST
    assert(min_index >= 0 && min_index < V);
    assert(mstSet[min_index] == false);

    return min_index;
}

void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        assert(parent[i] >= 0 && parent[i] < V);
        printf("%d - %d \t%d \n", parent[i], i, graph[parent[i]][i]);
    }
}

void primMST(int graph[V][V]) {
    int parent[V];  // Stores constructed MST
    int key[V];     // Key values used to pick minimum weight edge
    bool mstSet[V]; // To represent set of vertices included in MST

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;

        // Invariant: Initially no vertex is included in MST
        assert(!mstSet[i]);
        assert(key[i] == INT_MAX);
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        // Invariant: After count iterations, count vertices are included in MST
        int included = 0;
        for (int i = 0; i < V; i++)
            if (mstSet[i]) included++;
        assert(included == count);

        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            // Invariant: If graph[u][v] != 0 and v is not in MST and graph[u][v] < key[v],
            // then u becomes parent of v
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];

                assert(parent[v] == u);
                assert(key[v] == graph[u][v]);
            }

            // Safety invariants:
            assert(mstSet[v] == true || parent[v] >= -1);
            assert(key[v] >= 0 && key[v] <= INT_MAX);
        }
    }

    // Final invariant: Exactly V vertices included in MST
    int included = 0;
    for (int i = 0; i < V; i++) {
        assert(mstSet[i] == true);
        included++;
    }
    assert(included == V);

    printMST(parent, graph);
}

int main() {
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };

    primMST(graph);

    return 0;
}
