#include <stdio.h>
#include <assert.h>

// Helper function to check if arr[0..k] is sorted in non-decreasing order
int isSorted(int arr[], int k) {
    for (int i = 1; i <= k; ++i) {
        if (arr[i - 1] > arr[i]) return 0;
    }
    return 1;
}

void insertionSort(int arr[], int n)
{
    // MAKE ASSERTION HERE
    assert(n >= 0); // The array length should be non-negative

    for (int i = 1; i < n; ++i) {

        // MAKE ASSERTION HERE
        assert(isSorted(arr, i - 1)); // Subarray arr[0..i-1] should be sorted

        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            // MAKE ASSERTION HERE
            assert(j < i && j >= 0); // j is within bounds
            assert(arr[j] > key);    // Invariant of while loop condition
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // MAKE ASSERTION HERE
        assert(j < i && (j == -1 || arr[j] <= key)); // arr[j+1] is the correct position for key

        arr[j + 1] = key;

        // MAKE ASSERTION HERE
        assert(isSorted(arr, i)); // Subarray arr[0..i] should now be sorted
    }
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

    // MAKE ASSERTION HERE
    assert(n == 5); // Specific to this input

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}
