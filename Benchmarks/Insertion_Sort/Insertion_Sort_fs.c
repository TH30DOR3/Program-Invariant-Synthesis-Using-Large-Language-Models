#include <stdio.h>
#include <assert.h>

// Helper to check if a subarray is sorted
int isSorted(int arr[], int start, int end) {
    for (int k = start + 1; k <= end; ++k) {
        if (arr[k] < arr[k - 1])
            return 0;
    }
    return 1;
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        // Invariant: subarray arr[0..i-1] is sorted
        assert(isSorted(arr, 0, i - 1));

        int key = arr[i];
        int j = i - 1;

        // Invariant before inner loop: j in valid bounds
        assert(j >= 0 && j < n);

        while (j >= 0 && arr[j] > key) {
            // Invariant: arr[j+1] will be assigned arr[j], which is greater than key
            assert(arr[j] > key);
            arr[j + 1] = arr[j];
            j = j - 1;

            // Invariant: j remains within bounds after decrement
            assert(j >= -1);
        }

        // Invariant: after inner loop, key belongs at position j+1
        if (j >= 0) {
            assert(arr[j] <= key);
        }

        arr[j + 1] = key;

        // Postcondition after this iteration: arr[0..i] is sorted
        assert(isSorted(arr, 0, i));
    }

    // Final invariant: the entire array is sorted
    assert(isSorted(arr, 0, n - 1));
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
