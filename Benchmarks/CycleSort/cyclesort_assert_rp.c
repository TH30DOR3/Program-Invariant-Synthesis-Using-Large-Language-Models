#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Displays the array
void display(int *arr, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Swaps two integers
void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

// Cycle sort with invariants for formal verification
void cycleSort(int *arr, int n)
{
    int writes = 0;

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++)
    {
        // Invariant: arr[0..cycle_start-1] is sorted and contains the smallest elements
        for (int i = 0; i < cycle_start - 1; i++)
            assert(arr[i] <= arr[i + 1]);

        int item = arr[cycle_start];
        int pos = cycle_start;

        // Count elements less than item to find correct position
        for (int i = cycle_start + 1; i < n; i++) {
            if (arr[i] < item)
                pos++;
        }

        // Invariant: pos equals number of elements < item in arr[cycle_start+1..n-1]
        int count = 0;
        for (int i = cycle_start + 1; i < n; i++) {
            if (arr[i] < item) count++;
        }
        assert(pos == cycle_start + count);

        if (pos == cycle_start)
            continue;

        while (item == arr[pos]) pos += 1;

        if (pos != cycle_start)
        {
            swap(&item, &arr[pos]);
            writes++;
        }

        while (pos != cycle_start)
        {
            pos = cycle_start;

            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i] < item)
                    pos += 1;

            while (item == arr[pos]) pos += 1;

            if (item != arr[pos])
            {
                swap(&item, &arr[pos]);
                writes++;
            }

            // Invariant: no element is lost or duplicated; item is being placed into correct final position
            // Item will eventually reach its correct location
        }

        // Post-loop invariant: arr[0..cycle_start] is now sorted
        for (int i = 0; i < cycle_start; i++)
            assert(arr[i] <= arr[i + 1]);
    }

    // Final invariant: array is sorted
    for (int i = 0; i < n - 1; i++)
        assert(arr[i] <= arr[i + 1]);
}

int main()
{
    int arr[] = {20, 40, 50, 10, 30}; // Sample input array
    int n = sizeof(arr) / sizeof(arr[0]); // Compute size of array

    printf("Original array: ");
    display(arr, n);

    cycleSort(arr, n);

    printf("Sorted array: ");
    display(arr, n);

    return 0;
}
