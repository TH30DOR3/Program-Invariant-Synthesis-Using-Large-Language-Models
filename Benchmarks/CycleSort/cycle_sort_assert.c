#include <stdio.h>
#include <stdlib.h>
#include <assert.h> // Include for using assertions

void display(int *arr, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

void cycleSort(int *arr, int n)
{
    int writes = 0;

    // Invariant: Array size must be non-negative
    assert(n >= 0);

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++)
    {
        int item = arr[cycle_start];
        int pos = cycle_start;

        // Invariant: item must equal arr[cycle_start]
        assert(item == arr[cycle_start]);

        for (int i = cycle_start + 1; i < n; i++) {
            // Invariant: i is always in bounds
            assert(i >= 0 && i < n);
            if (arr[i] < item)
                pos++;
        }

        // Invariant: pos must be within array bounds
        assert(pos >= 0 && pos < n);

        if (pos == cycle_start)
            continue;

        while (item == arr[pos]) {
            pos += 1;
            // Invariant: pos must not go out of bounds
            assert(pos < n);
        }

        if (pos != cycle_start)
        {
            // Invariant: pos must be a valid index
            assert(pos >= 0 && pos < n);
            swap(&item, &arr[pos]);
            writes++;
        }

        while (pos != cycle_start)
        {
            pos = cycle_start;

            for (int i = cycle_start + 1; i < n; i++) {
                assert(i >= 0 && i < n);
                if (arr[i] < item)
                    pos += 1;
            }

            while (item == arr[pos]) {
                pos += 1;
                assert(pos < n);
            }

            if (item != arr[pos])
            {
                assert(pos >= 0 && pos < n);
                swap(&item, &arr[pos]);
                writes++;
            }
        }
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
