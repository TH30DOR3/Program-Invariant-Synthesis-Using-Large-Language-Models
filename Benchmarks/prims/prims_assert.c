#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>  // Required for assert

#define V 5

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        // Invariant: key[v] should be >= 0 or INT_MAX
        assert(key[v] >= 0 || key[v] == INT_MAX);
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    }

    // Invariant: min_index should be a valid index
    assert(min_index >= 0 && min_index < V);
    return min_index;
}

int printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        // Invariant: parent[i] should be a valid index
        assert(parent[i] >= 0 && parent[i] < V);
        assert(graph[parent[i]][i] > 0); // Only connected edges should be printed
        printf("%d - %d \t%d \n", parent[i], i, graph[parent[i]][i]);
    }
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {

        int u = minKey(key, mstSet);
        // Invariant: u must not be already included in MST
        assert(mstSet[u] == false);

        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            // Invariant: graph[u][v] is non-negative
            assert(graph[u][v] >= 0);
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                // Invariant: parent[v] is updated only if there's a better edge
                assert(graph[u][v] < key[v]);
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }

        // Invariant: Exactly (count + 1) nodes should be in MST
        int inMST = 0;
        for (int i = 0; i < V; i++)
            if (mstSet[i]) inMST++;
        assert(inMST == count + 1);
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
