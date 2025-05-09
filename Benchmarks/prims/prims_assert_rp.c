#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#define V 5

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        // Invariant: 0 <= v <= V
        assert(v >= 0 && v <= V);
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    }

    // Postcondition: min_index must be in range and not yet included in mstSet
    assert(min_index >= 0 && min_index < V);
    assert(mstSet[min_index] == false);
    return min_index;
}

int printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        // Invariant: 1 <= i < V and parent[i] ∈ [0, V)
        assert(i >= 1 && i < V);
        assert(parent[i] >= 0 && parent[i] < V);
        printf("%d - %d \t%d \n", parent[i], i, graph[parent[i]][i]);
    }
    return 0;
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        // Invariant: 0 <= i < V
        assert(i >= 0 && i < V);
        key[i] = INT_MAX, mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        // Invariant: 0 <= count < V - 1
        assert(count >= 0 && count < V - 1);

        int u = minKey(key, mstSet);
        mstSet[u] = true;

        // Postcondition: u is now in mstSet
        assert(mstSet[u] == true);

        for (int v = 0; v < V; v++) {
            // Invariant: 0 <= v < V
            assert(v >= 0 && v < V);
            // If updating, then ensure graph[u][v] is less than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                // Safety: parent and key arrays are updated within bounds
                assert(u >= 0 && u < V);
                assert(v >= 0 && v < V);
                parent[v] = u, key[v] = graph[u][v];
                // Postcondition: key[v] correctly updated
                assert(key[v] == graph[u][v]);
                assert(parent[v] == u);
            }
        }

        // Invariant: At most (count + 1) nodes are in mstSet
        int included = 0;
        for (int i = 0; i < V; i++) {
            assert(i >= 0 && i < V);
            if (mstSet[i]) included++;
        }
        assert(included == count + 1);
    }

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
