#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#define V 5

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        // Invariant: v is within array bounds
        assert(v >= 0 && v < V);

        // Invariant: key[v] is initialized
        assert(key[v] >= 0 || key[v] == INT_MAX);

        // Invariant: mstSet[v] is either true or false
        assert(mstSet[v] == true || mstSet[v] == false);

        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    // Postcondition: returned min_index must be a valid index and not already in mstSet
    assert(min_index >= 0 && min_index < V);
    assert(mstSet[min_index] == false);

    return min_index;
}

int printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        // Invariant: i must be within bounds and parent[i] must be valid
        assert(i >= 1 && i < V);
        assert(parent[i] >= 0 && parent[i] < V);
        printf("%d - %d \t%d \n", parent[i], i, graph[parent[i]][i]);
    }
    return 0;
}

void primMST(int graph[V][V]) {
    int parent[V]; // MST result
    int key[V];    // Key values used to pick minimum weight edge
    bool mstSet[V]; // MST set

    for (int i = 0; i < V; i++) {
        // Invariant: loop initializes arrays
        assert(i >= 0 && i < V);
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;      // First node as starting point
    parent[0] = -1;  // Root of MST has no parent

    for (int count = 0; count < V - 1; count++) {
        // Invariant: exactly count vertices have been added to MST so far
        int includedCount = 0;
        for (int k = 0; k < V; k++) {
            if (mstSet[k]) includedCount++;
        }
        assert(includedCount == count);

        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            // Invariant: v is within bounds
            assert(v >= 0 && v < V);

            // graph[u][v] is a valid edge if non-zero
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                // Ensure we're only updating for non-MST neighbors with a better edge
                assert(mstSet[v] == false);
                assert(graph[u][v] < key[v]);

                parent[v] = u;
                key[v] = graph[u][v];
            }
        }

        // Invariant: u is now marked included
        assert(mstSet[u] == true);
    }

    // Postcondition: All nodes except root must have a parent assigned
    for (int i = 1; i < V; i++) {
        assert(parent[i] >= 0 && parent[i] < V);
    }

    // Invariant: all nodes included in MST
    for (int i = 0; i < V; i++) {
        assert(mstSet[i] == true);
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
