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

// Cycle sort with loop invariants
void cycleSort(int *arr, int n)
{
    int writes = 0;

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++)
    {
        // Invariant: 0 <= cycle_start < n
        assert(cycle_start >= 0 && cycle_start <= n - 2);

        int item = arr[cycle_start];
        int pos = cycle_start;

        // Count elements less than item to determine its correct position
        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i] < item)
                pos++;

        // Invariant: pos is the number of elements in arr[cycle_start+1..n-1] less than item, plus cycle_start
        int count = 0;
        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i] < item)
                count++;
        assert(pos == cycle_start + count);
        assert(pos >= 0 && pos < n);

        if (pos == cycle_start)
            continue;

        while (item == arr[pos]) {
            assert(pos >= 0 && pos < n); // Ensure pos is within bounds
            pos += 1;
        }

        // Invariant: item != arr[pos] before swap
        if (pos != cycle_start)
        {
            assert(item != arr[pos]);
            swap(&item, &arr[pos]);
            writes++;
        }

        while (pos != cycle_start)
        {
            pos = cycle_start;

            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i] < item)
                    pos++;

            while (item == arr[pos]) {
                assert(pos >= 0 && pos < n);
                pos += 1;
            }

            // Invariant: item is not equal to arr[pos], safe to swap
            if (item != arr[pos])
            {
                swap(&item, &arr[pos]);
                writes++;
            }

            // Invariant: After each internal swap, arr still contains all original values (no loss or duplication)
            // We don’t assert this explicitly as it's complex, but a checksum/assert on permutations could be done post-sort
        }

        // Optional (stronger): After each outer iteration, the current item is placed in its final sorted location
        // Can assert partial order: arr[0..cycle_start] contains the smallest cycle_start+1 items (requires O(n^2) check)
    }

    // Final invariant: array is sorted
    for (int i = 0; i < n - 1; i++) {
        assert(arr[i] <= arr[i + 1]);
    }
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
