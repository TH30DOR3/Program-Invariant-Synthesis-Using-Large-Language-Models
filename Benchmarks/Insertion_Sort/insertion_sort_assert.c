#include <stdio.h>
#include <assert.h>

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
        // Invariant: arr[0..i-1] should be sorted
        assert(isSorted(arr, 0, i - 1));

        int key = arr[i];
        int j = i - 1;

        // Ensure index is valid
        assert(j >= 0 && j < n);

        while (j >= 0 && arr[j] > key) {
            // Invariant: arr[j+1] will hold arr[j], so arr[j] > key
            assert(arr[j] > key);

            arr[j + 1] = arr[j];
            j = j - 1;

            // Ensure j is not out of bounds after decrement
            assert(j >= -1);
        }
        arr[j + 1] = key;

        // Postcondition: arr[0..i] should now be sorted
        assert(isSorted(arr, 0, i));
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

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}
