#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#define V 5

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        // MAKE ASSERTION HERE
        assert(v >= 0 && v < V);
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    }

    return min_index;
}

int printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[parent[i]][i]);
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        // MAKE ASSERTION HERE
        assert(i >= 0 && i < V);
        key[i] = INT_MAX, mstSet[i] = false;
    }

    // MAKE ASSERTION HERE
    for (int i = 0; i < V; i++) {
        assert(key[i] == INT_MAX);
        assert(mstSet[i] == false);
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        // MAKE ASSERTION HERE
        assert(count >= 0 && count < V - 1);
        int u = minKey(key, mstSet);
        assert(u >= 0 && u < V);
        assert(mstSet[u] == false);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u, key[v] = graph[u][v];
                // MAKE ASSERTION HERE
                assert(parent[v] == u);
                assert(key[v] == graph[u][v]);
            }
        }
    }

    // MAKE ASSERTION HERE
    for (int i = 0; i < V; i++) {
        assert(mstSet[i] == true);
        assert(key[i] != INT_MAX);  // Each key should be finalized
    }

    printMST(parent, graph);
}
