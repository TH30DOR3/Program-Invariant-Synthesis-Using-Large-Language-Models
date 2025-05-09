#include <stdio.h>
#include <assert.h>

// Helper to check if a subarray is sorted
int is_sorted(int arr[], int start, int end) {
    for (int k = start + 1; k <= end; ++k)
        if (arr[k - 1] > arr[k]) return 0;
    return 1;
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        // Loop invariant: subarray arr[0..i-1] is sorted
        assert(is_sorted(arr, 0, i - 1));

        int key = arr[i];
        int j = i - 1;

        // Loop invariants for the inner while loop
        // 1. Elements in arr[j+1..i] are greater than key
        // 2. Elements in arr[0..j] are ≤ key
        while (j >= 0 && arr[j] > key) {
            // Loop invariant: arr[j+1..i] are greater than key
            for (int k = j + 1; k <= i; ++k) {
                assert(arr[k] > key);
            }
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // At this point, arr[j+1] should be the correct location for key
        arr[j + 1] = key;

        // Assert that the array is sorted up to index i
        assert(is_sorted(arr, 0, i));
    }

    // Final full-array sortedness after the loop
    assert(is_sorted(arr, 0, n - 1));
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}
