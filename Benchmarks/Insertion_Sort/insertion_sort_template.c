#include <stdio.h>

void insertionSort(int arr[], int n)
{
    // MAKE ASSERTION HERE
    for (int i = 1; i < n; ++i) {

        // MAKE ASSERTION HERE
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            // MAKE ASSERTION HERE
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // MAKE ASSERTION HERE
        arr[j + 1] = key;

        // MAKE ASSERTION HERE
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

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}
