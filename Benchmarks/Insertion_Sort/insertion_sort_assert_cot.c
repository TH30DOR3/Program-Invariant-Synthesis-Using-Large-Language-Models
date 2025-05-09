#include <stdio.h>
#include <assert.h> // Include assert

void insertionSort(int arr[], int n)
{
    assert(n >= 0); // Array size must be non-negative

    for (int i = 1; i < n; ++i) {
        // Invariant before each outer iteration:
        // Elements 0 through i-1 are sorted
        for (int x = 0; x < i - 1; ++x)
            assert(arr[x] <= arr[x + 1]);

        int key = arr[i];
        int j = i - 1;

        // Invariant before and during each inner loop iteration:
        // Elements arr[j+1] through arr[i-1] are greater than key
        while (j >= 0 && arr[j] > key) {
            assert(j < n - 1); // j + 1 is a valid index
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // After the while loop: arr[j+1] is the correct position for key
        // and arr[0..i] is sorted
        arr[j + 1] = key;

        for (int x = 0; x < i; ++x)
            assert(arr[x] <= arr[x + 1]); // Updated segment is sorted
    }

    // After sorting: the entire array must be sorted
    for (int x = 0; x < n - 1; ++x)
        assert(arr[x] <= arr[x + 1]);
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

    assert(n == 5); // Based on static initialization
    insertionSort(arr, n);

    // Post-condition: arr must be sorted
    for (int i = 0; i < n - 1; ++i)
        assert(arr[i] <= arr[i + 1]);

    printArray(arr, n);

    return 0;
}
